#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


float count_letters(string text);
float count_words(string text);
float count_sentences(string text);
int grade(float words, float letters, float sentences);


int main(void)
{
    string text = get_string("Your text: \n");
    int g = grade(count_words(text), count_letters(text), count_sentences(text));
    // Checking if the value is greater then 16
    if (g >= 16)
    {
        printf("Grade 16+\n");
    }
    // Checking if value is lower then 1
    else if (g < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", g);
    }
}


float count_letters(string text)
{
    // Counting alphabetical letters in text
    float letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // Checking if value is alphabetical
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    // Returns the amount of letters in text
    return letters;
}

float count_words(string text)
{
    // Counting words by finding space in text
    float words = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    // Returns the amount of words in text
    return words;
}

float count_sentences(string text)
{
    // Counting sentences by finding . ! ? in text
    float sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // Looking for . ? !
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            sentences++;
        }
    }
    // Returning the float value
    return sentences;
}

// Function that is taking all floats and doing math
int grade(float words, float letters, float sentences)
{
    // Doing math to round the grade
    float l = (letters / words * 100);
    float s = (sentences / words * 100);
    // Returning the rounded int value
    return round(0.0588 * l - 0.296 * s - 15.8);
}