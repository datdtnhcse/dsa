using namespace std;
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    
    //Helping functions go here
    static void sink(T* start, T* end, int pos, int size) {
    while (2 * pos + 1 < size) {
        int j = 2 * pos + 1;
        if (j < size - 1 && start[j] < start[j + 1]) j++;
        if (start[pos] >= start[j]) break;
        T temp = start[pos];
        start[pos] = start[j];
        start[j] = temp;
        
        pos = j;
    }
    }

    static void exchange(T* start, T* end, int pos, int j) {
        T temp = start[pos];
        start[pos] = start[j];
        start[j] = temp;
    }

    static void heapSort(T* start, T* end) {
        int N = end - start;
        for (int k = (N - 1) / 2; k >= 0; --k) {
            sink(start, end, k, N);
        }
        while (N > 0) {
            exchange(start, end, 0, N - 1);
            --N;
            sink(start, end, 0, N);
        }
        Sorting<T>::printArray(start,end);
    }
    
};