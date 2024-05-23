#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
using namespace std;

class OrderedVecInt {
private:
    int capacity = 0, size = 0;
    int* arr = nullptr;

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        int* newArr = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

public:
    OrderedVecInt() = default;

    ~OrderedVecInt() {
        delete[] arr;
    }

    int getSize() const {
        return size;
    }

    int& operator[](int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw out_of_range("Index out of range");
    }

    int operator[](int index) const {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        throw out_of_range("Index out of range");
    }

    bool insert(int value) {
        if (size == capacity) {
            resize();
        }

        int pos = 0;
        while (pos < size && arr[pos] < value) {
            pos++;
        }

        for (int i = size; i > pos; i--) {
            arr[i] = arr[i - 1];
        }

        arr[pos] = value;
        size++;
        return true;
    }

    bool remove_by_val(int value) {
        int pos = -1;
        for (int i = 0; i < size; i++) {
            if (arr[i] == value) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            return false;
        }

        for (int i = pos; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }

        size--;
        return true;
    }

    bool remove_by_index(int index) {
        if (index < 0 || index >= size) {
            return false;
        }

        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }

        size--;
        return true;
    }
};

int main() {
    srand((unsigned int)time(NULL));
    int n, k;
    OrderedVecInt vec;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int k = rand() % 1000;
        vec.insert(k);
    }

    for (int i = 0; i < vec.getSize(); i++)
        cout << vec[i] << " ";
    cout << endl;

    if (vec.getSize() > 2 && vec.remove_by_val(vec[2]))
        cout << "Remove done" << endl;
    else
        cout << "Remove failed" << endl;

    if (vec.getSize() > 4 && vec.remove_by_index(4))
        cout << "RemoveIndex done" << endl;
    else
        cout << "RemoveIndex failed" << endl;

    for (int i = 0; i < vec.getSize(); i++)
        vec[i] -= 10;

    for (int i = 0; i < vec.getSize(); i++)
        cout << vec[i] << " ";
    cout << endl;

    return 0;
}
