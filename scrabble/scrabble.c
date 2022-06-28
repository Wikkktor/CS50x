#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // Checking if player 1 is the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    // Checking if player 2 is the winner
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    // If the amount of points is the same
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Computing and returning the amount of score per word
    // TODO: Compute and return score for string
    int points = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        // Checking if the word is alphabetical
        if (isalpha(word[i]))
        {
            // Adding points to the int points
            points += POINTS[toupper(word[i]) - 'A'];
        }
    }
    // returning the amount of poins
    return points;
}
