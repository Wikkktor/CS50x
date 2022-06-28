#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int height;
    while (true)
    {
        height = get_int("Width: ");
        // Validation to user prompt
        if (height > 0 && height < 9)
        {
            break;
        }
    }
    // For each row
    for (int row = 0; row < height; row++)
    {
        // For each column
        // Creating Space's
        for (int space = 0; space < height - row - 1; space++)
        {
            // Print a space
            printf(" ");
        }
        // Creating bricks
        for (int brick = 0; brick <= row; brick++)
        {
            // Print a brick
            printf("#");
        }


        //Breakpoint
        printf("  ");


        // Creating a brick
        for (int j = 0; j <= row; j++)
        {
            // Print a brick
            printf("#");
        }
        // Endpoint of the row
        printf("\n");
    }

}
