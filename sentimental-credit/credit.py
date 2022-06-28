from cs50 import get_string
from sys import exit

# Get card number as string
cardnumber = get_string("Number: ")
# Identify number of digits in card number
cardlength = len(cardnumber)

# Validate number of digits in card number
if cardlength != 13 and cardlength != 15 and cardlength != 16:
    print("INVALID")
    exit()

# Validate checksum
sum1, sum2 = 0, 0
x = cardnumber
y = cardlength

if y % 2 == 0:
    for i in range(y):
        num = int(x[i])
        if i % 2 == 0:
            multiple = num * 2
            if multiple >= 10:
                sum1 += multiple // 10
                sum1 += multiple % 10
            else:
                sum1 += multiple
        else:
            sum2 += num
else:
    for i in range(y):
        num = int(x[i])
        if i % 2 != 0:
            multiple = num * 2
            if multiple >= 10:
                sum1 += multiple // 10
                sum1 += multiple % 10
            else:
                sum1 += multiple
        else:
            sum2 += num

checksum = (sum1 + sum2) % 10

# Identify card type
if checksum == 0:
    # Get first and second digits
    first = int(cardnumber[0])
    second = int(cardnumber[1])
    # AMEX
    if first == 3 and (second == 4 or second == 7):
        print("AMEX")
    # VISA
    elif first == 4:
        print("VISA")
    # MASTERCARD
    elif first == 5 and second > 0 and second < 6:
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")