#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;
    int Lth, Rth; // 0 = thread, 1 = child

    Node(int val)
    {
        data = val;
        left = right = NULL;
        Lth = Rth = 0;
    }
};

class TBT
{
    Node *root;

public:
    TBT()
    {
        root = NULL;
    }

    // INSERT
    void insert(int key)
    {
        Node *ptr = root;
        Node *par = NULL;

        while (ptr != NULL)
        {
            if (key == ptr->data)
            {
                cout << "Duplicate key!\n";
                return;
            }

            par = ptr;

            if (key < ptr->data)
            {
                if (ptr->Lth == 1)
                    ptr = ptr->left;
                else
                    break;
            }
            else
            {
                if (ptr->Rth == 1)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        Node *newNode = new Node(key);

        if (par == NULL)
        {
            root = newNode;
            return;
        }

        if (key < par->data)
        {
            newNode->left = par->left; // predecessor
            newNode->right = par;      // successor
            par->Lth = 1;
            par->left = newNode;
        }
        else
        {
            newNode->left = par;         // predecessor
            newNode->right = par->right; // successor
            par->Rth = 1;
            par->right = newNode;
        }
    }

    // INORDER TRAVERSAL
    void inorder()
    {
        Node *ptr = root;

        if (ptr == NULL)
            return;

        // Go to leftmost node
        while (ptr->Lth == 1)
            ptr = ptr->left;

        while (ptr != NULL)
        {
            cout << ptr->data << " ";

            // If thread, go to successor directly
            if (ptr->Rth == 0)
                ptr = ptr->right;
            else
            {
                ptr = ptr->right;
                while (ptr != NULL && ptr->Lth == 1)
                    ptr = ptr->left;
            }
        }
    }
};

int main()
{
    TBT tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder Traversal: ";
    tree.inorder();

    return 0;
}