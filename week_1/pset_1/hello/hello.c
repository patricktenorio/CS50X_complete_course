#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask user for his/her name
    string name = get_string("What's your name? ");
    // Print heelo + input name
    printf("hello, %s\n", name);
}