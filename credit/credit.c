#include <stdio.h>
#include <cs50.h>
void print_credit_card_brand(long long ccn);
bool check_validity(long long credit_card_number);
int find_length(long long n);
bool checksum(long long ccn);

int main(void)
{
    long long credit_card_number;
    do
    {
        // Taking card number from user
        credit_card_number = get_long_long("Number: ");
    }
    while (credit_card_number < 0);

    // Checking if it's valid
    if (check_validity(credit_card_number))
    {
        // Prints brand if valid
        print_credit_card_brand(credit_card_number);
    }
    else
    {
        // Prints if not
        printf("INVALID\n");
    }
}


// Checking credit card brand
void print_credit_card_brand(long long ccn)
{
    // 'e' means how many 0's
    if (ccn >= 51e14 && ccn < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((ccn >= 4e12 && ccn < 5e12) || (ccn >= 4e15 && ccn < 5e15))
    {
        printf("VISA\n");
    }
    else if ((ccn >= 34e13 && ccn < 35e13) || (ccn >= 37e13 && ccn < 38e13))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}


bool check_validity(long long credit_card_number)
{
    // Taking lenght of the card number
    int len = find_length(credit_card_number);
    // Returning bool if card is valid by lenght and checksum
    return (len == 13 || len == 15 || len == 16) && checksum(credit_card_number);
}

bool checksum(long long ccn)
{
    // ccn stand for credit card number
    int sum = 0;
    for (int i = 0; ccn != 0; i++, ccn /= 10)
    {
        if (i % 2 == 0)
        {
            sum += ccn % 10;
        }
        else
        {
            int digit = 2 * (ccn % 10);
            // If the sum is more then 9 it is making 2 numbers of the sum
            sum += digit / 10 + digit % 10;
        }
    }
    return (sum % 10) == 0;
}

int find_length(long long n)
{
    // Returning the lenght of card by dividing it by 10 for x times
    int len;
    for (len = 0; n != 0; n /= 10, len++);
    return len;
}
