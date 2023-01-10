#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    float number_of_letters = 0;
    float number_of_words = 1;
    float number_of_sentences = 0;

    string text = get_string("Input your text: ");

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            number_of_letters++;
        }

        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
        {
            number_of_words++;
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            number_of_sentences++;
        }
    }
    /* Formula:
    Avg. letters per 100 words (aL) = number_of_letters / number_of_words * 100
    Avg. sentences per 100 words (aS) = number_of_sentences / number_of_words * 100
    Coleman-Liau formula (clf) = 0.0588 * aL - 0.296 * aS - 15.8
    */
    float avg_letters = number_of_letters / number_of_words * 100;
    float avg_sentence = number_of_sentences / number_of_words * 100;
    float readability_score = 0.0588 * avg_letters - 0.296 * avg_sentence - 15.8;

    // printf("\nTotal number of letters in your text: %.0f\n", number_of_letters);
    // printf("Total number of words in your text: %.0f\n", number_of_words);
    // printf("Total number of sentences in your text: %.0f\n", number_of_sentences);
    // printf("\nAverage letters per 100 words: %.2f\n", avg_letters);
    // printf("Average sentence per 100 words: %.2f\n", avg_sentence);

    if (readability_score < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (readability_score > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(readability_score));
    }

    return 0;
}