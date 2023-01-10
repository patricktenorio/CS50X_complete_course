# TODO
from cs50 import get_float

# set counter variable
counter = 0

# loop until true
while True:
    # prompt the user for amount
    amount = get_float("Change owed: ")

    # if input is greater than or equal to 0
    if amount >= 0:
        # cents variable to round amount
        cents = round(amount * 100)
        # list for quarters, dimes, nickels, pennies,
        denominator_list = [25, 10, 5, 1]

        # iterate thru the list
        for i in denominator_list:
            # count and use floor division to get exact amount
            counter += cents // i
            # modulus to i
            cents %= i

        # print output
        print(counter)
        # break out the loop
        break
