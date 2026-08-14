import json
from os import path

def clear_screen():
    print("\033[H\033[2J", end="")

def input_handler(user_input):
    if user_input == "y" or user_input == "Y":
        return True
    elif user_input == "n" or user_input == "N":
        return False
    else:
        print(" [ Please either type y or n ]")
        print(" [ Press any key to try again ]")
        input()
        clear_screen()
        return None

class BstNode:
    def __init__(self,text,question=True):
        self.text = text
        self.question = question
        self.yes = None
        self.no = None

    def save_tree(self):
        file_name = "tree.json"
        try:
            with open(file_name, "w") as file:
                json.dump(self.to_dict(), file, indent=4)
                print("Tree saved")
        except Exception as e:
            print("Something went wrong" + e)

    def to_dict(self):
        """Recursively converts the node and its children into a dictionary."""
        if not self.question:
            return {
                "text": self.text,
                "is_question": False
            }
        return {
            "text": self.text,
            "is_question": True,
            "yes_child": self.yes.to_dict() if self.yes else None,
            "no_child": self.no.to_dict() if self.no else None
        }


    def add_question(self,curr,animal):
        new_question = input(" What would be a good question for this animal: ")

        while True:
            yes_or_no = input(f" Would a {animal} be a yes or no to your question: ")
            decision = input_handler(yes_or_no)
            if decision == None:
                continue
            break

        old_ans_text = curr.text
        old_ans = BstNode(old_ans_text, False)
        new_ans = BstNode(animal,False)
        curr.text = new_question
        curr.question = True
        
        if decision == True:
            curr.yes = new_ans
            curr.no = old_ans
        elif decision == False:
            curr.yes = old_ans
            curr.no = new_ans

    def play(self):
        curr = self

        while curr and curr.question:
            user_input = None
            print(f" {curr.text}, y/n")
            user_input = input(": ")
            user_input_valid = input_handler(user_input)

            if user_input_valid == True:
                curr = curr.yes
                # was_yes = True
            elif user_input_valid == False:
                curr = curr.no
                # was_yes = False
            else:
                continue
            
        while True:
            print(f" is your animal a {curr.text}, y/n")
            user_input = input(": ")

            if input_handler(user_input):
                print(" GGs, easy dubs")
                break
            elif not input_handler(user_input):
                print(" GGs, what was your animal", end="\n")
                animal = input(": ")
                self.add_question(curr, animal)
                print(" Preciate it, I got you next time")
                break
            else:
                continue     

def from_dict(data):
    """Recursively builds a tree of QuestionNodes from a nested dictionary."""
    if data is None:
        return None
    
    node = BstNode(data["text"], data["is_question"])
    if node.question:
        node.yes = from_dict(data.get("yes_child"))
        node.no = from_dict(data.get("no_child"))
    return node     

def load_game():
        """Loads tree from JSON file, or creates a default one if file doesn't exist."""
        file_name = "animal_guessing_tree.json"
        if path.exists(file_name):
            try:
                with open(file_name, 'r') as f:
                    data = json.load(f)
                    print("💾 Game loaded successfully!")
                    return from_dict(data)
            except Exception as e:
                print(f"⚠️ Error loading save file, starting fresh. Details: {e}")
        
        # Default fallback starter tree
        root = BstNode("Is it a mammal?")
        root.yes = BstNode("Dog", False)
        root.no = BstNode("Snake", False)  
        return root

def display_tree(root, level=0):
    if root is None:
        return
    
    if root.no:
        display_tree(root.no, level + 1)
    print(" " * level + " -> " + root.text)
    if root.yes:
        display_tree(root.yes, level + 1)

def main():
    root = load_game()

    print("")
    print(" Think of an animal and press a key when you think of one")
    input(": ")
    root.play()
    root.save_tree()
    # display_tree(root)

    return 0

if __name__ == "__main__":
    main()
        