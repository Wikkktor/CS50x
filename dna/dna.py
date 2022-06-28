import csv
from sys import argv, exit


def main():

     # Check for command-line usage
    if len(argv) != 3:
        print("Usage: python dna.py csv_file txt_file")
        exit()

    # Read database file into a variable
    database = []
    with open(argv[1], 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable
    with open(argv[2], 'r') as f:
        sequence = f.read()

    # Listing DNA sequances that are in database only first row because every row sequances are the same
    subsequences = list(database[0].keys())[1:]

    # Find longest match of each dna sequance
    result = {}
    for subsequence in subsequences:
        result[subsequence] = longest_match(sequence, subsequence)

    # print(result)

    # Check database for match characters
    for character in database:
        matches = 0
        for subsequence in subsequences:
            if int(character[subsequence]) == result[subsequence]:
                matches += 1

        # If matches has the same value as len of list database , we have a character
        if matches == len(subsequences):
            print(character["name"])
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
