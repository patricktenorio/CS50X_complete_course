# TODO
from cs50 import get_int

# loop until true
while True:
    # prompt user for height
    height = get_int("Height: ")

    # check if input is between 1 to 8
    if height >= 1 and height <= 8:
        # iterate thru height range
        for i in range(height):
            # add white space and remove new line
            print((height - 1 - i) * " ", end="")
            # multiple iteration to hash
            print((i + 1) * "#")
        # break out the loop
        break