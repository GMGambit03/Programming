from sys import argv 
from sys import stderr
from sys import exit

def main():
    if len(argv) != 3:
        print(f"Usage: {argv[0]} <input_file> <output_file>", file=stderr)
        exit(1)

    in_file = argv[1]
    out_file = argv[2]

    new_file = open(out_file, "w")

    with open(in_file, "r") as file:
        for line in file:
            new_file.writelines(line.upper())

    new_file.close
if __name__ == "__main__":
    main()