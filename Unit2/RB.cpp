#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    string name;
    Color color;
    Node *left, *right, *parent;

    Node(string name) {
        this->name = name;
        color = RED;
        left = right = parent = NULL;
    }
};

class RBTree {
private:
    Node* root;

    // Left Rotation
    void rotateLeft(Node* &root, Node* &pt) {
        Node* right_child = pt->right;
        pt->right = right_child->left;

        if (pt->right != NULL)
            pt->right->parent = pt;

        right_child->parent = pt->parent;

        if (pt->parent == NULL)
            root = right_child;
        else if (pt == pt->parent->left)
            pt->parent->left = right_child;
        else
            pt->parent->right = right_child;

        right_child->left = pt;
        pt->parent = right_child;
    }

    // Right Rotation
    void rotateRight(Node* &root, Node* &pt) {
        Node* left_child = pt->left;
        pt->left = left_child->right;

        if (pt->left != NULL)
            pt->left->parent = pt;

        left_child->parent = pt->parent;

        if (pt->parent == NULL)
            root = left_child;
        else if (pt == pt->parent->left)
            pt->parent->left = left_child;
        else
            pt->parent->right = left_child;

        left_child->right = pt;
        pt->parent = left_child;
    }

    // Fix violations after insertion
    void fixInsert(Node* &root, Node* &pt) {
        Node* parent_pt = NULL;
        Node* grand_parent_pt = NULL;

        while ((pt != root) && (pt->color == RED) &&
               (pt->parent->color == RED)) {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            // Parent is left child
            if (parent_pt == grand_parent_pt->left) {
                Node* uncle_pt = grand_parent_pt->right;

                // Case 1: Uncle is RED
                if (uncle_pt != NULL && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else {
                    // Case 2 & 3
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            else {
                Node* uncle_pt = grand_parent_pt->left;

                if (uncle_pt != NULL && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else {
                    if (pt == parent_pt->left) {
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
        root->color = BLACK;
    }

    // BST Insert
    Node* BSTInsert(Node* root, Node* pt) {
        if (root == NULL)
            return pt;

        if (pt->name < root->name) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->name > root->name) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }
        return root;
    }

    // Inorder traversal
    void inorderHelper(Node* root) {
        if (root == NULL) return;
        inorderHelper(root->left);
        cout << root->name << " (" 
             << (root->color == RED ? "R" : "B") << ") ";
        inorderHelper(root->right);
    }

    // Search
    Node* searchHelper(Node* root, string key) {
        if (root == NULL || root->name == key)
            return root;

        if (key < root->name)
            return searchHelper(root->left, key);
        return searchHelper(root->right, key);
    }

public:
    RBTree() {
        root = NULL;
    }

    void insert(string name) {
        Node* pt = new Node(name);
        root = BSTInsert(root, pt);
        fixInsert(root, pt);
    }

    void display() {
        inorderHelper(root);
        cout << endl;
    }

    void search(string name) {
        Node* res = searchHelper(root, name);
        if (res != NULL)
            cout << "Directory Found\n";
        else
            cout << "Directory Not Found\n";
    }
};

int main() {
    RBTree fs;

    fs.insert("Documents");
    fs.insert("Downloads");
    fs.insert("Music");
    fs.insert("Pictures");
    fs.insert("Videos");

    cout << "Directory Structure:\n";
    fs.display();

    fs.search("Music");
    fs.search("Games");

    return 0;
}