#include <iostream>
#include <algorithm>

using namespace std;

// Prototipos de funciones de ordenamiento
void bubbleSort(int arr[], int size, bool ascending, int &cycles);
void insertionSort(int arr[], int size, bool ascending, int &cycles);
void selectionSort(int arr[], int size, bool ascending, int &cycles);
void countingSort(int arr[], int size, bool ascending, int &cycles);
void quickSort(int arr[], int low, int high, bool ascending, int &cycles);
void mergeSort(int arr[], int low, int high, bool ascending, int &cycles);

// Función para imprimir el array
void printArray(int arr[], int size)
{
    cout << "Array ordenado: ";
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Función principal
int main()
{
    // Tamaño del array
    int size;

    cout << "Ingrese el tamaño del array: ";
    cin >> size;

    if (size <= 0)
    {
        cout << "Tamaño no válido. Saliendo del programa.\n";
        return 1;
    }

    // Crear y llenar el array con números ingresados por el usuario
    int arr[size];
    cout << "Ingrese los números separados por espacios:\n";
    for (int i = 0; i < size; ++i)
    {
        cin >> arr[i];
    }

    // Menú de selección
    int choice;
    bool ascending;
    cout << "Seleccione el método de ordenamiento:\n";
    cout << "1. Burbuja\n2. Inserción\n3. Selección\n4. Counting Sort\n5. Quick Sort\n6. Merge Sort\n";
    cout << "Ingrese el número correspondiente al método: ";
    cin >> choice;

    cout << "Seleccione el orden:\n";
    cout << "1. Ascendente\n2. Descendente\n";
    cout << "Ingrese el número correspondiente al orden: ";
    int orderChoice;
    cin >> orderChoice;
    ascending = (orderChoice == 1);

    // Contador de ciclos
    int cycles = 0;

    switch (choice)
    {
        case 1:
            bubbleSort(arr, size, ascending, cycles);
            break;
        case 2:
            insertionSort(arr, size, ascending, cycles);
            break;
        case 3:
            selectionSort(arr, size, ascending, cycles);
            break;
        case 4:
            countingSort(arr, size, ascending, cycles);
            break;
        case 5:
            quickSort(arr, 0, size - 1, ascending, cycles);
            break;
        case 6:
            mergeSort(arr, 0, size - 1, ascending, cycles);
            break;
        default:
            cout << "Selección no válida. Saliendo del programa.\n";
            return 1;
    }

    // Imprimir array ordenado y opción de revertir
    printArray(arr, size);

    cout << "¿Desea revertir el orden? (1. Sí / 2. No): ";
    int reverseChoice;
    cin >> reverseChoice;

    if (reverseChoice == 1)
    {
        reverse(arr, arr + size);
        printArray(arr, size);
    }

    cout << "Ciclos realizados: " << cycles << endl;

    return 0;
}

// Implementación de funciones de ordenamiento
void bubbleSort(int arr[], int size, bool ascending, int &cycles)
{
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if ((ascending && arr[j] > arr[j + 1]) || (!ascending && arr[j] < arr[j + 1]))
            {
                swap(arr[j], arr[j + 1]);
            }
            cycles++;
        }
    }
}

void insertionSort(int arr[], int size, bool ascending, int &cycles)
{
    for (int i = 1; i < size; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        while ((j >= 0) && ((ascending && arr[j] > key) || (!ascending && arr[j] < key)))
        {
            arr[j + 1] = arr[j];
            --j;
            cycles++;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int size, bool ascending, int &cycles)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j)
        {
            if ((ascending && arr[j] < arr[minIndex]) || (!ascending && arr[j] > arr[minIndex]))
            {
                minIndex = j;
            }
            cycles++;
        }
        swap(arr[minIndex], arr[i]);
    }
}

void countingSort(int arr[], int size, bool ascending, int &cycles)
{
    int maxElement = *max_element(arr, arr + size);
    int minElement = *min_element(arr, arr + size);

    int range = maxElement - minElement + 1;
    int count[range] = {0};

    for (int i = 0; i < size; ++i)
    {
        count[arr[i] - minElement]++;
        cycles++;
    }

    int outputIndex = 0;
    for (int i = 0; i < range; ++i)
    {
        while (count[i] > 0)
        {
            arr[outputIndex++] = i + minElement;
            count[i]--;
            cycles++;
        }
    }
}

int partition(int arr[], int low, int high, bool ascending, int &cycles)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j)
    {
        if ((ascending && arr[j] < pivot) || (!ascending && arr[j] > pivot))
        {
            ++i;
            swap(arr[i], arr[j]);
        }
        cycles++;
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high, bool ascending, int &cycles)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, ascending, cycles);

        quickSort(arr, low, pi - 1, ascending, cycles);
        quickSort(arr, pi + 1, high, ascending, cycles);
    }
}

void merge(int arr[], int low, int middle, int high, bool ascending, int &cycles)
{
    int n1 = middle - low + 1;
    int n2 = high - middle;

    int left[n1], right[n2];

    for (int i = 0; i < n1; ++i)
    {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < n2; ++j)
    {
        right[j] = arr[middle + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = low;

    while (i < n1 && j < n2)
    {
        if ((ascending && left[i] <= right[j]) || (!ascending && left[i] >= right[j]))
        {
            arr[k] = left[i];
            ++i;
        }
        else
        {
            arr[k] = right[j];
            ++j;
        }
        ++k;
        cycles++;
    }

    while (i < n1)
    {
        arr[k] = left[i];
        ++i;
        ++k;
        cycles++;
    }

    while (j < n2)
    {
        arr[k] = right[j];
        ++j;
        ++k;
        cycles++;
    }
}
void mergeSort(int arr[], int low, int high, bool ascending, int &cycles)
{
    if (low < high)
    {
        int middle = low + (high - low) / 2;

        mergeSort(arr, low, middle, ascending, cycles);
        mergeSort(arr, middle + 1, high, ascending, cycles);

        merge(arr, low, middle, high, ascending, cycles);
    }
}
