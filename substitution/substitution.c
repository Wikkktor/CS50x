#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


void substitution(char z, string key);
void Do_substitute(string key);



int main(int argc, string argv[])
{
    // Checking if user provided 1 key
    if (argc == 2)
    {
        // Checking if key is 26 char long
        if (strlen(argv[1]) == 26)
        {
            string key = argv[1];
            // For each element in key
            for (int i = 0; i < strlen(key) ; i++)
            {
                // Checking if char is alphabetical
                if (! isalpha(key[i]))
                {
                    // If is not returning error
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }
                // Checking if the char is different then every other char
                for (int j = i + 1 ; j < strlen(key) ; j++)
                {
                    // Lowering both chars and comparing them
                    if (tolower(key[i]) == tolower(key[j]))
                    {
                        // If they are the same printing error
                        printf("Key must not contain repeated alphabets.\n");
                        return 1;
                    }
                }
            }
            // If everything is fine
            Do_substitute(argv[1]);
        }
        else
        {
            // If key doesn't have certain lenght
            printf("Key must contain 26 characters.\n");
            return 1;
        }

    }
    else
    {
        // If there is no key or more then 1
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // The end of the function
    return 0;
}


void Do_substitute(string key)
{
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char x = plaintext[i];
        // If char is alphabetical it will encrypt it
        if (isalpha(x))
        {
            substitution(x, key);
        }
        // If char is not it will just print it
        else
        {
            printf("%c", x);
        }
    }
    // At the end of 'for'
    printf("\n");
}

void substitution(char z, string key)
{
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < strlen(alphabet); i++)
    {
        // Checking what char from alphabet is equal to given char while increasing i
        if (islower(z))
        {
            if (z == tolower(alphabet[i]))
            {
                // Printing specific char from provided key by 'i'
                printf("%c", tolower(key[i]));
            }
        }
        else
        {
            if (z == toupper(alphabet[i]))
            {
                printf("%c", toupper(key[i]));
            }
        }
    }
}
