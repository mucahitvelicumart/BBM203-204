public class LinkedList {
    Node head; // head of list

    // Linked list Node.
    // This inner class is made static
    // so that main() can access it
    static class Node {
        int key;
        Employee newEmp;
        Node next;

        // Constructor
        Node(Employee emp)
        {
            key=emp.phone;
            newEmp=emp;
            next = null;
        }
    }

    // Method to insert a new node
    public static LinkedList insert(LinkedList list, Employee emp)
    {
        // Create a new node with given data
        Node new_node = new Node(emp);
        new_node.next = null;

        // If the Linked List is empty,
        // then make the new node as head
        if (list.head == null) {
            list.head = new_node;
        }
        else {
            // Else traverse till the last node
            // and insert the new_node there
            Node last = list.head;
            while (last.next != null) {
                last = last.next;
            }
            // Insert the new_node at last node
            last.next = new_node;
        }
        // Return the list by head
        return list;
    }
    // Method to print the LinkedList.
    public static void printList(LinkedList list)
    {
        Node currNode = list.head;

        // Traverse through the LinkedList
        while (currNode != null) {
            // Print the data at current node
            System.out.print(currNode.newEmp.phone + " ");

            // Go to next node
            currNode = currNode.next;
        }
    }
}
