#include <iostream>
#include <stdlib.h>

#define TEST_SIZE 10
#define TEST_SPACE 50


/* The segfault was caused because the root was never initialized.
It was simply initialized to nullptr and we never gave it a value.
Fixed this by initializing a root node.
Memory leak occurred because we never freed the nodes.
Fixed this by writing a destructor. (recursive)
*/


using namespace std;

struct Node
{
    int value;
    Node * left;
    Node * right;
    Node(int v)
    {
        value = v;
        left = nullptr;
        right = nullptr;
    }

    /** @brief Inserts an integer into the subtree rooted at this node.

    Does not allow duplicate entries.

    @return whether or not the entry was successfully inserted.

    */
    bool insert(int val)
    {
        if(val == value)
        {
            return false;
        }
        else if(val < value)
        {
            if(left == nullptr)
            {
                left = new Node(val);
                return true;
            }
            else
            {
                return left->insert(val);
            }
        }
        else
        {
            if(right == nullptr)
            {
                right = new Node(val);
                return true;
            }
            else
            {
                return right->insert(val);
            }
        }
    }

    /** @brief Finds an integer in the subtree rooted at this node.

    @return whether or not the entry exists in this subtree.

    */
    bool find(int val)
    {
        if(val == value)
        {
            return true;
        }
        else if(val < value)
        {
            if(left == nullptr)
            {
                left = new Node(val);
                return false;
            }
            else
            {
                return left->find(val);
            }
        }
        else
        {
            if(right == nullptr)
            {
                return false;
            }
            else
            {
                return right->find(val);
            }
        }
    }
};

class BinarySearchTree
{
private:
    Node * root;
public:
    BinarySearchTree(int val)
    {
        root = new Node(val);
    }

    ~BinarySearchTree(){
        deleteRec(root);
    }

    void deleteRec(Node * root){
        if(root != nullptr){
            deleteRec(root->left);
            deleteRec(root->right);
            delete root;
        }
    }

    /** @brief Inserts an integer into this tree.

    Does not allow duplicate entries.

    @return whether or not the entry was successfully inserted.

    */
    bool insert(int val)
    {
        return root->insert(val);
    }

     /** @brief Finds an integer in this tree.

    @return whether or not the entry exists in this tree.

    */
    bool find(int val)
    {
        return root->find(val);
    }
};

int main(int argc, char ** argv)
{
    BinarySearchTree b(8);
    srand(42);

    // first insert some test numbers
    cout << endl << endl
         << "adding " << TEST_SIZE << " numbers" << endl << endl;
    for(int i = 0; i < TEST_SIZE; i++)
    {
        int k = rand() % TEST_SPACE;
        cout << "Inserting " << k << "... ";
        bool s = b.insert(k);
        if(s)
        {
            cout << "OK" << endl;
        }
        else
        {
            cout << "already in" << endl;
        }
    }

    // now print out all the numbers in the tree
    // (by finding all possible numbers, not by traversing the tree)
    cout << endl << endl
         << "ok, now printing contents (the slow way)" << endl << endl;
    for(int j = 0; j < TEST_SPACE; j++)
    {
        if(b.find(j))
        {
            cout << j;
        }
    }

    cout << endl << endl << "all done" << endl << endl;
    return 0;
}
