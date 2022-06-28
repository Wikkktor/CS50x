#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Getting name from user
    string name = get_string("What is your name?\n");
    // Displaying his name with a greeting
    printf("Nice to meet you %s\n", name);
}