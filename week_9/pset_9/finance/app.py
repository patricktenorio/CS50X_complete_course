import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    owns = own_shares()
    total = 0
    for symbol, shares in owns.items():
        result = lookup(symbol)
        name, price = result["name"], result["price"]
        stock_value = shares * price
        total += stock_value
        owns[symbol] = (name, shares, usd(price), usd(stock_value))
    cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]['cash']
    total += cash
    return render_template("index.html", owns=owns, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Symbol Check
        if not symbol:
            return apology("Stock symbol not found")

        # Stock Check
        stock = lookup(symbol.upper())
        if stock == None:
            return apology("Symbol Doesn't Exist")

        # Shares Check
        if shares < 1:
            return apology("Minimum amount is 1")

        # Transactions Table
        transaction_price = shares * stock["price"]
        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        user_cash = user_cash_db[0]["cash"]

        # Cash Check
        if user_cash < transaction_price:
            return apology("Insufficient Cash. Purchase Failed.")

        # Update Users Table
        update_cash = user_cash - transaction_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_cash, user_id)

        # Update Transactions Table
        today = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], shares, stock["price"], today)

        flash("Successfully bought shares!")

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions_db = db.execute("SELECT * FROM transactions WHERE user_id = :id", id=user_id)
    return render_template("history.html", transactions=transactions_db)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")

        # Symbol Check
        if not symbol:
            return apology("Incorrect Symbol")

        # Stock Check
        result = lookup(symbol.upper())
        if result == None:
            return apology("Symbol Doesn't Exist")

        return render_template("quoted.html", name=result["name"], price=usd(result["price"]), symbol=result["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("registration.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # UsernameCheck
        if username == "":
            return apology("Please enter a username")
        elif not username:
            return apology("Incorrect username or password")

        # Password Check
        if password == "":
            return apology("Please enter a password")
        elif not password:
            return apology("Incorrect username or password")

        # Confirm Password Check
        if confirmation == "":
            return apology("Please confirm your password")
        elif confirmation != password:
            return apology("Password did not match")

        # Insert Data Into Users Table
        password_hash = generate_password_hash(password)
        try:
            user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)
        except:
            return apology("Username already exist")

        # Check Log-in Session
        session["user_id"] = user
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        symbols_user = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = :id GROUP BY symbol HAVING SUM(shares) > 0", id=user_id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols_user])
    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        # Symbol Check
        if not symbol:
            return apology("Incorrect Symbol")

        # Stock Check
        stock = lookup(symbol.upper())
        if stock == None:
            return apology("Symbol Doesn't Exist")

        # Shares Check
        if shares < 0:
            return apology("Shares not found")

        # Transactions Table
        transaction_price = shares * stock["price"]
        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        user_cash = user_cash_db[0]["cash"]

        user_shares = db.execute(
            "SELECT SUM(shares) AS shares FROM transactions WHERE user_id=:id AND symbol = :symbol", id=user_id, symbol=symbol)
        user_shares_real = user_shares[0]["shares"]

        if shares > user_shares_real:
            return apology("Amount of shares exceeded")

        # Update Users Table
        update_cash = user_cash + transaction_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_cash, user_id)

        # Update Transactions Table
        today = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], (-1)*shares, stock["price"], today)

        flash("Successfully sold shares!")

        return redirect("/")


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add Cash Function"""
    if request.method == "GET":
        return render_template("add-cash.html")
    else:
        added_cash = int(request.form.get("added_cash"))

        if not added_cash:
            return apology("Insuficient funds")

        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        user_cash = user_cash_db[0]["cash"]

        # Update Users Table
        update_cash = user_cash + added_cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_cash, user_id)

        return redirect("/")


def own_shares():
    """Helper function: Which stocks the user owns, and numbers of shares owned. Return: dictionary {symbol: qty}"""
    user_id = session["user_id"]
    owns = {}
    query = db.execute("SELECT symbol, shares FROM transactions WHERE user_id = ?", user_id)
    for q in query:
        symbol, shares = q["symbol"], q["shares"]
        owns[symbol] = owns.setdefault(symbol, 0) + shares
    # filter zero-share stocks
    owns = {k: v for k, v in owns.items() if v != 0}
    return owns