#include <iostream>
#include <stack>
using namespace std;

int getMax(int a, int b)
{
    return (a > b) ? a : b;
}

struct Node
{
    Node *left;
    Node *right;
    int data;
    Node(int d)
    {
        data = d;
        left = right = nullptr;
    }
};

class BT
{

public:
    Node *root;
    BT()
    {
        root = nullptr;
    }
    void insertnode(int d)
    {
        Node *nn = new Node(d);

        if (root == nullptr)
        {
            root = nn;
            return;
        }

        Node *curr = root;

        while (true)
        {
            if (d > curr->data)
            {
                if (curr->right == nullptr)
                {
                    curr->right = nn;
                    return;
                }
                curr = curr->right;
            }
            else if (d < curr->data)
            {
                if (curr->left == nullptr)
                {
                    curr->left = nn;
                    return;
                }
                curr = curr->left;
            }
            else
            {
                cout << "Duplicates not allowed" << endl;
                return;
            }
        }
    }
    void display()
    {
        Node *curr = root;
        stack<Node *> st;
        while (curr != nullptr || !st.empty())
        {
            while (curr != nullptr)
            {
                st.push(curr);
                curr = curr->left;
            }

            curr = st.top();
            st.pop();
            cout << curr->data << endl;

            curr = curr->right;
        }
    }
    void preorder()
    {
        stack<Node *> sp;
        sp.push(root);
        Node *curr = root;

        while (!sp.empty())
        {
            curr = sp.top();
            sp.pop();
            cout << curr->data << endl;

            if (curr->right != nullptr)
                sp.push(curr->right);
            if (curr->left != nullptr)
                sp.push(curr->left);
        }
    }
    // void postorder()
    // {
    // }
    Node *reinsert(Node *root, int d)
    {
        // Node *nn = new Node(d);
        // if (root == nullptr)
        // {
        //     root = nn;
        //     return;
        // }
        // Node *curr = root;
        // if (d < curr->data)
        // {
        //     curr = reinsert(curr->left, d);
        // }
        // else if (d > curr->data)
        // {
        //     curr = reinsert(curr->right, d);
        // }
        // else
        // {
        //     cout << "Duplicate not allowed " << endl;
        //     return curr;
        // }
        // return curr;
        {
            if (root == nullptr)
            {
                return new Node(d);
            }

            if (d < root->data)
            {
                root->left = reinsert(root->left, d);
            }
            else if (d > root->data)
            {
                root->right = reinsert(root->right, d);
            }
            else
            {
                cout << "Duplicate not allowed" << endl;
            }

            return root;
        }
    }
    void redisplay(Node *root)
    {
        Node *curr = root;
        if (curr != nullptr)
        {
            redisplay(curr->left);
            cout << curr->data << endl;
            redisplay(curr->right);
        }
    }
    // Node *search(Node *root, int target)
    // {
    // Node *parr;
    // if (root == nullptr)
    // {
    //     cout << target << "not there" << endl;
    // }
    // else if (target < root->data)
    // {
    //     parr = root;
    //     search(root->left, target);
    // }
    // else if (target > root->data)
    // {
    //     parr = root;
    //     search(root->right, target);
    // }
    // else if (root->data == target)
    // {
    //     cout << target << " found!" << endl;
    //     return root, parr;
    // }
    Node *search(Node *root, int target, Node *&parent)
    {
        if (root == nullptr)
            return nullptr;

        if (root->data == target)
            return root;

        parent = root;

        if (target < root->data)
            return search(root->left, target, parent);
        else
            return search(root->right, target, parent);
    }

    void nodedelete(Node *root, int del)
    {
        Node *temp;
        Node *parr;
        temp, parr = search(root, del);
        if (temp->left == NULL && temp->right == NULL)
        {
            delete (temp);
            parr->left;
        }
    }
};

//

int main()
{
    int d;
    BT b;
    b.insertnode(10);
    b.insertnode(5);
    b.insertnode(7);
    b.insertnode(3);
    b.insertnode(2);
    b.insertnode(11);
    // b.search(b.root, 11);
    // b.search(b.root, 121);
    // b.display();
    // b.preorder();
    // b.postorder();
    // b.redisplay(b.root);

    return 0;
}