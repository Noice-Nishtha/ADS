#include <iostream>
using namespace std;

class ArrayTree
{
    int tree[100];
    int size;

public:
    ArrayTree()
    {
        size = 0;
    }

    // INSERT (level order)
    void insert(int val)
    {
        if (size >= 100)
        {
            cout << "Tree is full\n";
            return;
        }

        tree[size] = val;
        size++;
    }

    // SEARCH
    int search(int key)
    {
        for (int i = 0; i < size; i++)
        {
            if (tree[i] == key)
                return i;
        }
        return -1;
    }

    // DELETE (replace with last element)
    void deleteNode(int key)
    {
        int index = search(key);

        if (index == -1)
        {
            cout << "Element not found\n";
            return;
        }

        tree[index] = tree[size - 1];
        size--;

        cout << "Deleted successfully\n";
    }

    // GET PARENT
    int getParent(int index)
    {
        if (index == 0)
        {
            cout << "Root has no parent\n";
            return -1;
        }

        return tree[(index - 1) / 2];
    }

    // GET LEFT CHILD
    int getLeft(int index)
    {
        int leftIndex = 2 * index + 1;

        if (leftIndex >= size)
        {
            cout << "No left child\n";
            return -1;
        }

        return tree[leftIndex];
    }

    // GET RIGHT CHILD
    int getRight(int index)
    {
        int rightIndex = 2 * index + 2;

        if (rightIndex >= size)
        {
            cout << "No right child\n";
            return -1;
        }

        return tree[rightIndex];
    }

    // DISPLAY
    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << tree[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    ArrayTree t;

    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(2);
    t.insert(7);

    cout << "Tree: ";
    t.display();

    int idx = t.search(7);

    if (idx != -1)
    {
        cout << "Parent: " << t.getParent(idx) << endl;
        cout << "Left Child: " << t.getLeft(idx) << endl;
        cout << "Right Child: " << t.getRight(idx) << endl;
    }

    t.deleteNode(5);

    cout << "After deletion: ";
    t.display();

    return 0;
}