#include <iostream>
using namespace std;

struct Node
{
    int player_id, score, height;
    Node *left, *right;

    Node(int id, int s)
    {
        player_id = id;
        score = s;
        height = 1;
        left = right = NULL;
    }
};

// Get height
int getHeight(Node *n)
{
    return (n == NULL) ? 0 : n->height;
}

// Balance Factor
int getBalance(Node *n)
{
    return (n == NULL) ? 0 : getHeight(n->left) - getHeight(n->right);
}

// Right Rotation (LL)
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left Rotation (RR)
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert player
Node *insert(Node *root, int id, int score)
{
    if (!root)
        return new Node(id, score);

    if (id < root->player_id)
        root->left = insert(root->left, id, score);
    else if (id > root->player_id)
        root->right = insert(root->right, id, score);
    else
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // LL
    if (balance > 1 && id < root->left->player_id)
        return rightRotate(root);

    // RR
    if (balance < -1 && id > root->right->player_id)
        return leftRotate(root);

    // LR
    if (balance > 1 && id > root->left->player_id)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (balance < -1 && id < root->right->player_id)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find minimum node
Node *minValueNode(Node *node)
{
    Node *current = node;
    while (current->left)
        current = current->left;
    return current;
}

// Delete player
Node *deleteNode(Node *root, int id)
{
    if (!root)
        return root;

    if (id < root->player_id)
        root->left = deleteNode(root->left, id);
    else if (id > root->player_id)
        root->right = deleteNode(root->right, id);
    else
    {
        if (!root->left || !root->right)
        {
            Node *temp = root->left ? root->left : root->right;
            if (!temp)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            delete temp;
        }
        else
        {
            Node *temp = minValueNode(root->right);
            root->player_id = temp->player_id;
            root->score = temp->score;
            root->right = deleteNode(root->right, temp->player_id);
        }
    }

    if (!root)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Balancing
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Display leaderboard (inorder)
void display(Node *root)
{
    if (root)
    {
        display(root->left);
        cout << "Player ID: " << root->player_id
             << " Score: " << root->score << endl;
        display(root->right);
    }
}

int main()
{
    Node *root = NULL;

    root = insert(root, 101, 200);
    root = insert(root, 102, 150);
    root = insert(root, 103, 300);

    cout << "Leaderboard:\n";
    display(root);

    root = deleteNode(root, 102);

    cout << "\nAfter Deletion:\n";
    display(root);

    return 0;
}