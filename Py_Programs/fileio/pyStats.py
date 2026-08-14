import sys

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input_file> <output_file>", file=sys.stderr)
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    new_file = open(output_file, "w")

    stats = [0,0,0,0]

    with open(input_file, "r") as file:
        for line in file:
            stats[2] += 1
            for char in range(len(line) - 1):
                if not line[char].isalpha():
                    continue
                stats[0] += 1
                if char == 0 or line[char - 1].isspace():
                    stats[1] += 1
    
    for i in range(len(stats)):
        curr = stats[i]

        if i == 0:
            new_file.write(f"chars: {curr}\n")
        elif i == 1:
            new_file.write(f"words: {curr}\n")
        else:
            new_file.write(f"Lines: {curr}\n")

    new_file.close()

if __name__ == "__main__":
    main()