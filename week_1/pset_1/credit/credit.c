#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card;
    do
    {
        card = get_long("Please input your card number: ");
    }
    // Card number should not be less than 0
    while (card < 0);

    int card1, card2, card3, card4, card5, card6, card7, card8;
    card1 = ((card % 100) / 10) * 2;
    card2 = ((card % 10000) / 1000 * 2);
    card3 = ((card % 1000000) / 100000 * 2);
    card4 = ((card % 100000000) / 10000000 * 2);
    card5 = ((card % 10000000000) / 1000000000 * 2);
    card6 = ((card % 1000000000000) / 100000000000 * 2);
    card7 = ((card % 100000000000000) / 10000000000000 * 2);
    card8 = ((card % 10000000000000000) / 1000000000000000 * 2);

    card1 = (card1 % 100 / 10) + (card1 % 10);
    card2 = (card2 % 100 / 10) + (card2 % 10);
    card3 = (card3 % 100 / 10) + (card3 % 10);
    card4 = (card4 % 100 / 10) + (card4 % 10);
    card5 = (card5 % 100 / 10) + (card5 % 10);
    card6 = (card6 % 100 / 10) + (card6 % 10);
    card7 = (card7 % 100 / 10) + (card7 % 10);
    card8 = (card8 % 100 / 10) + (card8 % 10);

    int sum1 = card1 + card2 + card3 + card4 + card5 + card6 + card7 + card8;

    // Find the digits that were not multiplied by 2
    int card9, card10, card11, card12, card13, card14, card15, card16;

    card9 = (card % 10);
    card10 = ((card % 1000) / 100);
    card11 = ((card % 100000) / 10000);
    card12 = ((card % 10000000) / 1000000);
    card13 = ((card % 1000000000) / 100000000);
    card14 = ((card % 100000000000) / 10000000000);
    card15 = ((card % 10000000000000) / 1000000000000);
    card16 = ((card % 1000000000000000) / 100000000000000);

    int sum2 = card9 + card10 + card11 + card12 + card13 + card14 + card15 + card16;
    int sum3 = sum1 + sum2;

    int lenght = 0;
    long visa = card;
    long amex = card;
    long master = card;

    if ((sum3 % 10) != 0)
    {
        printf("%s\n", "INVALID");
        return 0;
    }

    // Differentiate between VISA, MasterCard, and AMEX
    while (card > 0)
    {
        card = card / 10;
        lenght++;
    }

    // Check if the card is a VISA Card
    while (visa >= 10)
    {
        visa /= 10;
    }
    if (visa == 4 && (lenght == 13 || lenght == 16))
    {
        printf("%s\n", "VISA");
        return 0;
    }

    // Check if the card is an AMEX Card
    while (amex >= 10000000000000)
    {
        amex /= 10000000000000;
    }
    if (lenght == 15 && (amex == 34 || amex == 37))
    {
        printf("%s\n", "AMEX");
        return 0;
    }

    // Check if the card i a MasterCard
    while (master >= 100000000000000)
    {
        master /= 100000000000000;
    }
    if (lenght == 16 && (master == 51 || master == 52 || master == 53 || master == 54 || master == 55))
    {
        printf("%s\n", "MASTERCARD");
        return 0;
    }
    else
    {
        printf("%s\n", "INVALID");
    }
    return 0;
}


