/**
 * @file
 * @author The CS2 TA Team
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief Example of a linked list class and usage.
 *
 */

/**
 * This is the fixed version of linkedlist.cpp, and it also has a new method:
 * hasLoop(), which determines if the list has a loop
 */

#include <iostream>
#include "stdlib.h"

using namespace std;

/**
 * A class defining the shell of a linked list data structure.
 */
class List
{

/**
 * Public methods accessible by external code.
 */
public:
    List();
    ~List();
    void insert(int item);
    void printList();
    int hasLoop();

/**
 * Private data, including structure definition and class variables.
 */
private:
    struct Node
    {
        int data;
        Node *next;

        /**
         * Constructor for a node structure.
         */
        Node(int data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };
    Node *head;
    int num_elements;
};

/**
 * List constructor.
 */
List::List()
{
    head = nullptr;
    num_elements = 0;
}

/**
 * List destructor.
 */
List::~List()
{
    // TODO: Write the destructor so that this code does not leak memory!
    Node *it = head;
    Node *prev = head;
    for(int i = 1; i < num_elements; i++){
        it = it->next;
        delete prev;
        prev = it;
    }
    delete prev;
}

/**
 * insert   Insert an integer at the end of the list.
 * @param   item integer to be inserted at the end of the list
 */
void List::insert(int item)
{
    // If we have elements...
    if (num_elements > 0)
    {
        // Set up a pointer to get to end of current list
        Node *temp = head;
        for (int i = 0; i < num_elements - 1; ++i)
        {
            temp = temp->next;
        }
        // temp now points to node at end of list

        // Construct our new node, it doesn't point to anything yet
        Node *new_node = new Node(item, nullptr);

        // Make the old tail point to the new tail
        temp->next = new_node;

        // and update the number of elements in the list
        num_elements++;
    }
    else
    {
        head = new Node(item, nullptr);
        num_elements++;
    }
    return;
}

/**
 * printList    Prints the contents of our list out, one integer per line.
 */
void List::printList()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data << std::endl;
        temp = temp->next;
    }
    return;
}

/**
 * hasLoop   determines if the linked list has a loop
 */

int List::hasLoop(){
    int count = 0;
    Node *temp = head;
    while (temp != nullptr){
        if(count >= num_elements){
            return 1;
        }
        temp = temp->next;
        count++;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    List lst;
    for (int i = 0; i < 10; ++i)
    {
        lst.insert(i);
    }
    lst.printList();
    std::cout << lst.hasLoop() << endl;
    return 0;
}
