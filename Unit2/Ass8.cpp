#include <iostream>
using namespace std;

struct Node
{
    string dir;
    bool color; // true = RED, false = BLACK
    Node *left, *right, *parent;

    Node(string d)
    {
        dir = d;
        color = true; // RED
        left = right = parent = NULL;
    }
};

class RBTree
{
    Node *root;

    void rotateLeft(Node *&root, Node *&pt)
    {
        Node *pt_right = pt->right;

        pt->right = pt_right->left;

        if (pt->right != NULL)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == NULL)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(Node *&root, Node *&pt)
    {
        Node *pt_left = pt->left;

        pt->left = pt_left->right;

        if (pt->left != NULL)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == NULL)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixInsert(Node *&root, Node *&pt)
    {
        Node *parent_pt = NULL;
        Node *grand_parent_pt = NULL;

        while ((pt != root) && (pt->color == true) &&
               (pt->parent->color == true))
        {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left)
            {
                Node *uncle_pt = grand_parent_pt->right;

                if (uncle_pt != NULL && uncle_pt->color == true)
                {
                    grand_parent_pt->color = true;
                    parent_pt->color = false;
                    uncle_pt->color = false;
                    pt = grand_parent_pt;
                }
                else
                {
                    if (pt == parent_pt->right)
                    {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            else
            {
                Node *uncle_pt = grand_parent_pt->left;

                if (uncle_pt != NULL && uncle_pt->color == true)
                {
                    grand_parent_pt->color = true;
                    parent_pt->color = false;
                    uncle_pt->color = false;
                    pt = grand_parent_pt;
                }
                else
                {
                    if (pt == parent_pt->left)
                    {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = false; // BLACK
    }

public:
    RBTree()
    {
        root = NULL;
    }

    Node *BSTInsert(Node *root, Node *pt)
    {
        if (root == NULL)
            return pt;

        if (pt->dir < root->dir)
        {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->dir > root->dir)
        {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void insert(string dir)
    {
        Node *pt = new Node(dir);
        root = BSTInsert(root, pt);
        fixInsert(root, pt);
    }

    void inorder(Node *root)
    {
        if (root == NULL)
            return;

        inorder(root->left);
        cout << root->dir << " (" << (root->color ? "R" : "B") << ") ";
        inorder(root->right);
    }

    void display()
    {
        inorder(root);
    }
};

int main()
{
    RBTree fs;

    fs.insert("Home");
    fs.insert("Documents");
    fs.insert("Downloads");
    fs.insert("Pictures");
    fs.insert("Videos");

    cout << "Directory Structure (Inorder):\n";
    fs.display();

    return 0;
}