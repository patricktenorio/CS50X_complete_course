# TODO

# loop until true
while True:
    # ask for name / convert to titlecase / strip all whitespace
    name = input("What is your name? ").title().strip()

    # check if input is all alpha
    if name.isalpha():
        # if yes, print output
        print(f"hello, {name}")
        # break out the loop
        break