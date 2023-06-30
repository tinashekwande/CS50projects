import csv
import sys


def main():

    bases = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("incorrect usage")
        sys.exit(1)

    # TODO: Read database file into a variable
    data = []
    with open(sys.argv[1]) as csvfile:
        csvreader = csv.DictReader(csvfile)
        for row in csvreader:
            person = {"name": row["name"]}
            for base in bases:
                person[base] = int(row.get(base, 0))
            data.append(person)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as dna:
        dnasequence = dna.read()

    # TODO: Find longest match of each STR in DNA sequence
    counts = {}
    for base in bases:
        counts[base] = longest_match(dnasequence, base)

    # TODO: Check database for matching profiles
    for person in data:
        if all(person.get(base, 0) == counts[base] for base in bases):
            print(person["name"])
            sys.exit(0)
    print("No match")


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

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
