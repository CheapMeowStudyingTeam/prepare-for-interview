#include <iostream>
using namespace std;

size_t get_size_1(int* arr) { return sizeof(arr); }
size_t get_size_2(int arr[]) { return sizeof(arr); }
size_t get_size_3(int (&arr)[10]) { return sizeof(arr); }

int main()
{
    int array[10];
    cout << (sizeof(array) == get_size_1(array) ? 1 : 0);
    cout << (sizeof(array) == get_size_2(array) ? 1 : 0);
    cout << (sizeof(array) == get_size_3(array) ? 1 : 0);
}