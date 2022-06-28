# Main function
def main():
    # Get text
    text = input("Text: ")
    # Declare variables
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    L = 100 * (letters / words)
    S = 100 * (sentences / words)
    grade = round(0.0588 * L - 0.296 * S - 15.8)
    # Print grade
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


# Count number of letters in text
def count_letters(text):
    # Set counter
    countletter = 0
    for c in text:
        # checking if character is alphabetical
        if (c.isalpha()) == True:
            # Add 1 to counter
            countletter += 1
    return countletter


# Count number of words in text
def count_words(text):
    # Set counter
    countword = 1
    for c in text:
        space = ' '
        # counting words by counting spaces
        if c == space:
            # Add 1 to counter
            countword += 1
    return countword


# Count number of sentences in text
def count_sentences(text):
    # Set counter
    countsen = 0
    for c in text:
        exclamation = '!'
        period = '.'
        questionmark = '?'
        # If character in text is an exclamation mark, question mark or period
        if c == exclamation or c == period or c == questionmark:
            # Add 1 to counter
            countsen += 1
    return countsen


main()