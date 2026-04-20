#include <iostream>
using namespace std;

#define MAX 100

class Heap
{
    int arr[MAX];
    int size;
    bool isMinHeap; // true = MinHeap, false = MaxHeap

public:
    Heap(bool type)
    {
        size = 0;
        isMinHeap = type;
    }

    // Comparison helper
    bool compare(int parent, int child)
    {
        if (isMinHeap)
            return parent > child; // MinHeap
        else
            return parent < child; // MaxHeap
    }

    // INSERT
    void insert(int value)
    {
        if (size == MAX)
        {
            cout << "Heap Overflow\n";
            return;
        }

        int i = size;
        arr[i] = value;
        size++;

        // Heapify UP
        while (i > 0 && compare(arr[(i - 1) / 2], arr[i]))
        {
            swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // HEAPIFY DOWN
    void heapify(int i)
    {
        int target = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && compare(arr[target], arr[left]))
            target = left;

        if (right < size && compare(arr[target], arr[right]))
            target = right;

        if (target != i)
        {
            swap(arr[i], arr[target]);
            heapify(target);
        }
    }

    // DELETE ROOT
    void deleteRoot()
    {
        if (size <= 0)
        {
            cout << "Heap Underflow\n";
            return;
        }

        cout << "Deleted root: " << arr[0] << endl;

        arr[0] = arr[size - 1];
        size--;

        heapify(0);
    }

    // DISPLAY
    void printHeap()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main()
{
    Heap maxH(false); // Max Heap
    Heap minH(true);  // Min Heap

    // Max Heap Test
    maxH.insert(50);
    maxH.insert(30);
    maxH.insert(40);
    maxH.insert(10);
    maxH.insert(5);
    maxH.insert(20);
    maxH.insert(60);

    cout << "Max Heap: ";
    maxH.printHeap();

    maxH.deleteRoot();
    cout << "After deletion: ";
    maxH.printHeap();

    // Min Heap Test
    minH.insert(40);
    minH.insert(20);
    minH.insert(30);
    minH.insert(10);
    minH.insert(15);

    cout << "\nMin Heap: ";
    minH.printHeap();

    minH.deleteRoot();
    cout << "After deletion: ";
    minH.printHeap();

    return 0;
}