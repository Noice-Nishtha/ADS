// Consider the Dictionary Implementations which allow for efficient storage and retrieval of
// key-value pairs using binary search trees. Each node in the tree store (key, value) pair. The
// dictionary should support the following operations efficiently:
// 1. Insert word (Handle insertion of duplicate entry)
// 2. Delete word
// 3. Search specific word
// 4. Display dictionary (Traversal)
// 5. Mirror image of dictionary
// 6. Create a copy of dictionary
// 7. Display dictionary level wise

#include <iostream>
#include <string>

using namespace std;

struct Node
{
    string word;
    string meaning;
    Node *left, *right;
    Node(string k, string v)
    {
        word = k;
        meaning = v;
        left = right = nullptr;
    }
};

class Dictionary
{
    Node *root;

public:
    Dictionary()
    {
        root = nullptr;
    }

    void insert(string word, string meaning)
    {
        Node *N = new Node(word, meaning);
        if (root == NULL)
        {
            root = N;
            return;
        }
        Node *curr = root;
        Node *parent = NULL;
        while (curr != NULL)
        {
            parent = curr;
            if (word < curr->word)
            {
                curr = curr->left;
            }
            else if (word > curr->word)
            {
                curr = curr->right;
            }
            else
            {
                cout << "Duplicate words not allowed!" << endl;
                delete N;
                return;
            }
        }
        if (word < parent->word)
        {
            parent->left = N;
        }

        else
        {
            parent->right = N;
        }
    }

    Node *search(Node *root, string word, Node *&parent)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->word == word)
        {
            return root;
        }
        parent = root;

        if (word < root->word)
            return search(root->left, word, parent);
        else
            return search(root->right, word, parent);
    }
    void deletenode(string word)
    {
        Node *curr = root;
        Node *parr = nullptr;

        // Find node
        while (curr != NULL && curr->word != word)
        {
            parr = curr;
            if (word < curr->word)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (curr == NULL)
        {
            cout << "Word not found!" << endl;
            return;
        }

        // Case 1 & 2: 0 or 1 child
        if (curr->left == nullptr || curr->right == nullptr)
        {
            Node *child = (curr->left != nullptr) ? curr->left : curr->right;

            if (parr == nullptr)
                root = child;
            else if (parr->left == curr)
                parr->left = child;
            else
                parr->right = child;

            delete curr;
        }
        // Case 3: 2 children
        else
        {
            Node *succParent = curr;
            Node *succ = curr->right;

            while (succ->left != nullptr)
            {
                succParent = succ;
                succ = succ->left;
            }

            // Copy BOTH key and value
            curr->word = succ->word;
            curr->meaning = succ->meaning;

            if (succParent->left == succ)
                succParent->left = succ->right;
            else
                succParent->right = succ->right;

            delete succ;
        }
    }
};