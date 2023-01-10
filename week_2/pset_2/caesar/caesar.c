#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char rotate(char plaintext, int secret_key);
bool only_digits(string digits);

int main(int argc, string argv[])
{
    int secret_key;
    int text_length;
    string text;

    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    secret_key = atoi(argv[1]);

    // Prompt user for plaintext
    text = get_string("ciphertext: ");
    text_length = strlen(text);
    char cipher[text_length + 1];

    for (int i = 0; i < text_length; i++)
    {
        cipher[i] = rotate(text[i], secret_key);
    }
    // null terminator
    cipher[text_length] = '\0';

    printf("ciphertext: %s\n", cipher);
}

// Make sure every character in argv[1] is a digit
bool only_digits(string digits)
{
    int text_length = strlen(digits);

    for (int i = 0; i < text_length; i++)
    {
        if (!isdigit(digits[i]))
        {
            return false;
        }

    }
    return true;
}

// Rotate the character if it's a letter
char rotate(char plaintext, int secret_key)
{
    // Caesar’s algorithm
    // ciphertext = (plaintext + secret_key) % 26
    // %26 means “remainder when dividing by 26.”
    char ciphertext;

    if (isupper(plaintext))
    {
        ciphertext = (plaintext - 'A' + secret_key) % 26 + 'A';
    }
    else if (islower(plaintext))
    {
        ciphertext = (plaintext - 'a' + secret_key) % 26 + 'a';
    }
    else
    {
        ciphertext = plaintext;
    }
    return ciphertext;
}