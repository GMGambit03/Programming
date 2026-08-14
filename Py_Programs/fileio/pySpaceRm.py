import sys

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input_file> <output_file>", file=sys.stderr)
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    new_file = open(output_file, "w")

    with open(input_file, "r") as file:
        for line in file:
            for char in line:
                if char == " " or char == "\n":
                    char = ""
                    continue
                new_file.write(char)

if __name__ == "__main__":
    main()