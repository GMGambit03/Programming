class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
    
class LinkedList:
    def __init__(self):
        self.head = None

    def add_node(self, node):

        current = self.head

        if current == None:
            self.head = node
            return

        while current.next is not None:
            current = current.next
        current.next = node

    def delete_node(self, node):

        prev_node = self.head
        next_node = prev_node.next

        if prev_node.data == node:
            self.head = next_node
            return

        while next_node is not None:
            
            if next_node.data == node:
                prev_node.next = next_node.next
                return
            prev_node = prev_node.next
            next_node = next_node.next

    def reverser(self):

        prev = self.head
        curr = prev.next
        nxt = curr.next

        prev.next = None
        while True:
            curr.next = prev

            if nxt.next == None:
                nxt.next = curr
                self.head = nxt
                break

            prev = curr
            curr = nxt
            nxt = nxt.next


    def search_node(self, target):

        current = self.head

        while current is not None:
            if current.data == target:
                print("Found it")
                return
            current = current.next
        print(f"List doesnt contain {target}")

    def display(self):

        current = self.head

        while current is not None:
            print(current.data, end=" -> ")
            current = current.next

def main():
    my_l_list = LinkedList()
    node_a = Node("Hello")
    node_b = Node("How")
    node_c = Node("Are")
    node_d = Node("You")
    node_e = Node("Doing")

    my_l_list.add_node(node_a)
    my_l_list.add_node(node_b)
    my_l_list.add_node(node_c)
    my_l_list.add_node(node_d)
    my_l_list.add_node(node_e)

    my_l_list.display()
    print()
    my_l_list.reverser()
    my_l_list.display()

    return 0

if __name__ == "__main__":
    main()