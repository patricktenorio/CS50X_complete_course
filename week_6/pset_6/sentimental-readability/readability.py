# CS50 Library to get the user’s input
from cs50 import get_string

#  asks the user to type in some text
string = get_string("Text: ")

# counter for letters, sentences, and words
letters = sentences = words = 0

# iterate on users input
for char in string:
    # check if input is alphabet
    if char.isalpha():
        # add 1 to letters counter
        letters += 1
    # check for spaces
    if char.isspace():
        # add 1 to words counter
        words += 1
    # check for punctuations
    if char in ['?', '.', '!']:
        # add 1 to sentences counter
        sentences += 1

# Coleman-Liau formula
words += 1
avg_letters = (letters * 100.0) / words
avg_sentences = (sentences * 100.0) / words
total = int((0.0588 * avg_letters - 0.296 * avg_sentences - 15.8) + 0.5)

# outputs the grade level for the text
if total < 1:
    print('Before Grade 1')
elif total >= 16:
    print('Grade 16+')
else:
    print(f'Grade {total}')