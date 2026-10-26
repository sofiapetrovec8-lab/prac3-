#include <iostream>
#include <string>
using namespace std;

struct Stats {
    int comparisons = 0;
    int moves = 0;
};

// Звичайне сортування вставками
Stats insertionSort(int a[], int n) {
    Stats s;

    for (int i = 1; i < n; i++) {
        int x = a[i];
        int j = i - 1;

        while (j >= 0) {
            s.comparisons++;

            if (a[j] > x) {
                a[j + 1] = a[j];
                s.moves++;
                j--;
            }
            else {
                break;
            }
        }

        a[j + 1] = x;
        s.moves++;
    }

    return s;
}

// Сортування бінарними вставками
Stats binaryInsertionSort(int a[], int n) {
    Stats s;

    for (int i = 1; i < n; i++) {
        int x = a[i];
        int left = 0;
        int right = i;

        // Пошук місця для вставки
        while (left < right) {
            int mid = (left + right) / 2;
            s.comparisons++;

            if (a[mid] <= x) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }

        // Звільнення місця для елемента
        int j = i;

        while (j > left) {
            a[j] = a[j - 1];
            s.moves++;
            j--;
        }

        a[left] = x;
        s.moves++;
    }

    return s;
}

// Звичайне бульбашкове сортування
Stats bubbleSort(int a[], int n) {
    Stats s;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            s.comparisons++;

            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                s.moves += 3;
            }
        }
    }

    return s;
}

// Шейкерне сортування
Stats shakerSort(int a[], int n) {
    Stats s;
    int left = 0;
    int right = n - 1;

    while (left < right) {
        bool swapped = false;

        // Рух зліва направо
        for (int i = left; i < right; i++) {
            s.comparisons++;

            if (a[i] > a[i + 1]) {
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;

                s.moves += 3;
                swapped = true;
            }
        }

        right--;

        if (!swapped) {
            break;
        }

        swapped = false;

        // Рух справа наліво
        for (int i = right; i > left; i--) {
            s.comparisons++;

            if (a[i - 1] > a[i]) {
                int temp = a[i - 1];
                a[i - 1] = a[i];
                a[i] = temp;

                s.moves += 3;
                swapped = true;
            }
        }

        left++;

        if (!swapped) {
            break;
        }

    }

    return s;
}

// Перевірка правильності сортування
bool isSorted(int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            return false;
        }
    }

    return true;
}

// Виведення масиву
void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    cout << endl;
}

// Перевірка двох масивів
bool equalArrays(int a[], int n, int b[], int m) {
    if (n != m) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

// Виведення результату алгоритму
void showResult(string name, int original[], int n,
    Stats(*sortFunction)(int[], int)) {

    int a[100];

    for (int i = 0; i < n; i++) {
        a[i] = original[i];
    }

    Stats s = sortFunction(a, n);

    cout << name << ": ";
    printArray(a, n);

    cout << "Comparisons: " << s.comparisons
        << ", Moves: " << s.moves << endl;

    cout << "Check: "
        << (isSorted(a, n) ? "OK" : "ERROR") << endl;

    cout << endl;
}

// Автоматичний тест
void runTest(int input[], int n, int expected[], int m,
    string name, int& passed) {

    int a[100];
    int b[100];
    int c[100];
    int d[100];

    for (int i = 0; i < n; i++) {
        a[i] = input[i];
        b[i] = input[i];
        c[i] = input[i];
        d[i] = input[i];
    }

    insertionSort(a, n);
    binaryInsertionSort(b, n);
    bubbleSort(c, n);
    shakerSort(d, n);

    bool ok = equalArrays(a, n, expected, m)
        && equalArrays(b, n, expected, m)
        && equalArrays(c, n, expected, m)
        && equalArrays(d, n, expected, m)
        && isSorted(a, n)
        && isSorted(b, n)
        && isSorted(c, n)
        && isSorted(d, n);

    cout << name << ": " << (ok ? "OK" : "ERROR") << endl;

    if (ok) {
        passed++;
    }
}

// Порівняльний експеримент
void compareSet(string name, int original[], int n) {
    int a[100];
    int b[100];
    int c[100];
    int d[100];

    for (int i = 0; i < n; i++) {
        a[i] = original[i];
        b[i] = original[i];
        c[i] = original[i];
        d[i] = original[i];
    }

    Stats s1 = insertionSort(a, n);
    Stats s2 = binaryInsertionSort(b, n);
    Stats s3 = bubbleSort(c, n);
    Stats s4 = shakerSort(d, n);

    cout << name << "\t"
        << s1.comparisons << "\t" << s1.moves << "\t"
        << s2.comparisons << "\t" << s2.moves << "\t"
        << s3.comparisons << "\t" << s3.moves << "\t"
        << s4.comparisons << "\t" << s4.moves << endl;
}

int main() {
    // Індивідуальний варіант №18
    int a[] = { 23, 36, 10, 29, 14, 20, 41, 16, 8, 32 };
    int n = 10;

    cout << "INDIVIDUAL VARIANT NO. 18" << endl;
    cout << "Original array: ";
    printArray(a, n);
    cout << endl;

    showResult("Insertion Sort", a, n, insertionSort);
    showResult("Binary Insertion Sort", a, n, binaryInsertionSort);
    showResult("Bubble Sort", a, n, bubbleSort);
    showResult("Shaker Sort", a, n, shakerSort);

    // Автоматизовані тести
    cout << "AUTOMATED TESTS" << endl;

    int passed = 0;
    int total = 12;

    runTest(nullptr, 0, nullptr, 0,
        "1. Empty array", passed);

    int t2[] = { 7 };
    int e2[] = { 7 };
    runTest(t2, 1, e2, 1, "2. One element", passed);

    int t3[] = { 1, 2, 3, 4, 5 };
    int e3[] = { 1, 2, 3, 4, 5 };
    runTest(t3, 5, e3, 5, "3. Already sorted", passed);

    int t4[] = { 5, 4, 3, 2, 1 };
    int e4[] = { 1, 2, 3, 4, 5 };
    runTest(t4, 5, e4, 5, "4. Reverse order", passed);

    int t5[] = { 4, 1, 5, 2, 3 };
    int e5[] = { 1, 2, 3, 4, 5 };
    runTest(t5, 5, e5, 5, "5. Mixed array", passed);

    int t6[] = { 3, 1, 3, 2, 1 };
    int e6[] = { 1, 1, 2, 3, 3 };
    runTest(t6, 5, e6, 5, "6. Duplicate elements", passed);

    int t7[] = { 0, -5, 8, -2, 4 };
    int e7[] = { -5, -2, 0, 4, 8 };
    runTest(t7, 5, e7, 5, "7. Negative numbers", passed);

    int t8[] = { 6, 6, 6, 6 };
    int e8[] = { 6, 6, 6, 6 };
    runTest(t8, 4, e8, 4, "8. Equal numbers", passed);

    int t9[] = { 2, 1 };
    int e9[] = { 1, 2 };
    runTest(t9, 2, e9, 2, "9. Two elements", passed);

    int t10[] = { 9, -1, 9, 0, -1, 5 };
    int e10[] = { -1, -1, 0, 5, 9, 9 };
    runTest(t10, 6, e10, 6,
        "10. Negative and duplicate numbers", passed);

    int t11[] = { 10, 3, 7, 1, 6 };
    int e11[] = { 1, 3, 6, 7, 10 };
    runTest(t11, 5, e11, 5, "11. Custom test", passed);

    int t12[] = { -3, 5, 0, -8, 2 };
    int e12[] = { -8, -3, 0, 2, 5 };
    runTest(t12, 5, e12, 5, "12. Custom test", passed);

    cout << "Passed tests: " << passed
        << " out of " << total << endl;

    cout << endl;

    // Приклад із завдання
    int example[] = { 7, 3, 9, 1, 5 };
    int exampleN = 5;

    cout << "EXAMPLE [7, 3, 9, 1, 5]" << endl;

    showResult("Insertion Sort", example, exampleN, insertionSort);
    showResult("Binary Insertion Sort", example, exampleN, binaryInsertionSort);
    showResult("Bubble Sort", example, exampleN, bubbleSort);
    showResult("Shaker Sort", example, exampleN, shakerSort);

    // Експеримент на чотирьох наборах даних
    int sorted[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int reversed[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    int mixed[] = { 4, 1, 7, 3, 9, 2, 6, 0, 5, 8 };

    cout << "COMPARISON EXPERIMENT" << endl;

    cout << "Dataset\tIns.comp.\tIns.moves"
        << "\tBin.comp.\tBin.moves"
        << "\tBub.comp.\tBub.moves"
        << "\tSh.comp.\tSh.moves" << endl;

    compareSet("Sorted", sorted, 10);
    compareSet("Reverse", reversed, 10);
    compareSet("Mixed", mixed, 10);
    compareSet("Variant No. 18", a, n);

    return 0;
}