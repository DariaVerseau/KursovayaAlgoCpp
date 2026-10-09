#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;
const long MaxNumber = 1024000;
long Size; // кол-во элементов vector
int nado = 1;

void initarray(vector<int> &BaseArray, int t)
{ // заполнение массива
    srand(time(0));
    switch (t)
    {
    case 1:
        BaseArray[0] = MaxNumber;

        for (int i = 1; i < Size; i++)
        {
            BaseArray[i] = BaseArray[i - 1] - rand() % (MaxNumber / Size) - 1;
        }

        break;
    case 2:
        BaseArray[0] = 1;

        for (int i = 1; i < Size; i++)
        {
            BaseArray[i] = BaseArray[i - 1] + rand() % (MaxNumber / Size) - 1;
        }

        break;
    case 3:
        for (int i = 0; i < Size; i++)
        {
            BaseArray[i] = rand() % 12 + 1;
        }

        break;
    case 4:
        for (int i = 0; i < Size; i++)
        {
            BaseArray[i] = rand() % MaxNumber + 1;
        }

        break;

    case 5:
        break;
    case 6:
        break;
    case 7:
        break;

    default:
        cout << "Такого варианта заполнения нет" << endl;
        break;
    }
}

class Node
{
public:
    int data;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int data)
    {
        this->data = data;
    }
};

vector<int> inorder(Node *root)
{
    stack<Node *> st;
    Node *node = root;
    vector<int> inorderV;
    while (true)
    {
        if (node != nullptr)
        {
            st.push(node);
            node = node->left;
        }
        else
        {
            if (st.empty() == true)
                break;
            node = st.top();
            st.pop();
            inorderV.push_back(node->data);
            node = node->right;
        }
    }

    return inorderV;
}

void insertIterative(Node *&root, int key)
{
    Node *current = root;
    Node *parent = nullptr;

    if (root == nullptr)
    {
        root = new Node(key);
        return;
    }

    while (current != nullptr)
    {
        parent = current;

        if (key < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (key < parent->data)
    {
        parent->left = new Node(key);
    }
    else
    {
        parent->right = new Node(key);
    }
}

Node *constructBST(vector<int> &keys, int Size)
{
    Node *root = nullptr;
    int key;
    for (int i = 0; i < Size; i++)
    {
        key = keys[i];
        insertIterative(root, key);
    }
    return root;
}

int massivesort(vector<int> &arr, int Size)
{
    int i, j, l, k, m;
    int MaxNumber = arr[0], MinNumber = arr[0];
    for (int i = 1; i < Size; i++)
    { // поиск максимального и минимального значения массива для хеш функции
        if (MaxNumber < arr[i])
            MaxNumber = arr[i];
        if (MinNumber > arr[i])
            MinNumber = arr[i];
    }
    if (MaxNumber == MinNumber)
        return 0;

    int Ubound = 1.4 * Size; // размер вспомогательного массива
    vector<int> AuxArray(Ubound);
    vector<bool> UsedArray(Ubound); // error
    for (i = 0; i < Size; i++)
    {
        j = (long double)(arr[i] - MinNumber) * (Ubound - 1) / (MaxNumber - MinNumber); // хэш функция
        if (!UsedArray[j])                                                              // сдвигает элементы вспомогательного массива
            AuxArray[j] = arr[i], UsedArray[j] = true;
        else
        {
            if (AuxArray[j] > arr[i])
            {
                while (j > 0)
                    if (UsedArray[j - 1] && AuxArray[j - 1] > arr[i])
                        j--;
                    else
                        break;
                m = -1;
            }
            else
            {
                while (j + 1 < Ubound)
                    if (UsedArray[j + 1] && AuxArray[j + 1] < arr[i])
                        j++;
                    else
                        break;
                m = 1;
            }
            k = 0;
            for (;;)
            {
                if (k + j >= 0 && k + j < Ubound && !UsedArray[k + j])
                    break;
                if (k > 0)
                    k = -k;
                else
                    k = 1 - k;
            }
            l = j + k;
            if (k > 0)
                k = 1;
            else
                k = -1;
            j += (m + k) / 2;
            while (l != j)
            {
                swap(AuxArray[l], AuxArray[l - k]);
                UsedArray[l] = true;
                l -= k;
            }
            AuxArray[j] = arr[i];
            UsedArray[j] = true;
        }
    }
    for (i = j = 0; i < Size; j++) // выгружаем отсортированные значения из вспомогательного массива
        if (UsedArray[j])
            arr[i++] = AuxArray[j];
    return 0;
}

void displayArray(vector<int> &array)
{
    for (int i = 0; i < Size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl
         << endl;
}

int check(vector<int> &array, long Size)
{

    for (int i = 1; i < Size - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            system("pause");
            return 0;
        };
        return 1;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int a, b, nenado;
    vector<int> n_keys = {};

    cout << "Выберите режим работы программы" << endl;
    cout << "1 - Исследование эффективности сортировки на основе 1 конкретного массива" << endl;
    cout << "2 - Исследование эффективности сортировки поледовательностью массивов разной длины - таблица" << endl;
    cin >> b;

    switch (b)
    {
    case 1:
    {
        do
        {
            nenado = 1;
            cout << "Введите размер массива" << endl;
            cin >> Size;
            vector<int> BaseArray(Size);
            vector<int> BaseArrayCopy(Size);

            while (nenado == 1)
            {
                cout << "Как вы хотите заполнить массив?" << endl;
                cout << "1 - В обратном порядке. 2 - Упорядоченно. 3 - Вырожденно. 4 - Случайно " << endl;
                cout << "5 - Вывести получившийся массив. 6 - Сохранить получившийся массив. 7 - выйти из программы" << endl;
                cin >> a;
                initarray(BaseArray, a);

                cout << endl;
                if (a == 5)
                    displayArray(BaseArray);
                if (a == 6)
                    nenado = 0;
                if (a == 7)
                {
                    nenado = 0;
                    nado = 0;
                }
            }

            for (int i = 0; i < Size; i++)
            {
                BaseArrayCopy[i] = BaseArray[i];
            }

            if (nado == 1)
                nenado = 1;

            while (nenado == 1)
            {
                cout << "Что делаем с массивом?" << endl;
                cout << "1 - Вывести. 2 - Отсортировать по 1 алгоритму (BST) и посчитать время сортировки " << endl;
                cout << "3 - Отсортировать по 2 алгоритму (Massive sort) и посчитать время сортировки" << endl;
                cout << "4 - Вернутся в начало для инициализации нового массива другого размера" << endl;
                cout << "5 - Выйти из программы" << endl;
                cin >> a;
                switch (a)
                {
                case 1:
                {
                    displayArray(BaseArray);
                    break;
                }
                case 2:
                {
                    auto begin3 = chrono::steady_clock::now();
                    Node *root = constructBST(BaseArray, Size);
                    BaseArray = inorder(root);
                    auto end3 = chrono::steady_clock::now();
                    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end3 - begin3);
                    if (check(BaseArray, Size) == 0)
                        cout << "Ошибка" << endl;
                    else
                    {
                        cout << "Отсортированный массив" << endl;
                        displayArray(BaseArray);
                        cout << "Время сортировки " << elapsed_ms.count() << " наносекунд\n"
                             << endl;
                    }
                    break;
                }
                case 3:
                {
                    auto begin3 = chrono::steady_clock::now();
                    massivesort(BaseArrayCopy, Size);
                    auto end3 = chrono::steady_clock::now();
                    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end3 - begin3);
                    if (check(BaseArrayCopy, Size) == 0)
                        cout << "Ошибка" << endl;
                    else
                    {
                        cout << "Отсортированный массив" << endl;
                        displayArray(BaseArrayCopy);
                        cout << "Время сортировки " << elapsed_ms.count() << " наносекунд\n"
                             << endl;
                    }
                    break;
                }
                case 4:
                {
                    nenado = 0;
                    break;
                }
                case 5:
                {
                    nenado = 0;
                    nado = 0;
                    break;
                }
                default:
                {
                    cout << "Используй цифры от 1 до 5!" << endl
                         << endl;
                    break;
                }
                }
            }
        } while (nado == 1);
        break;
    }
    case 2:
    {

        cout << setiosflags(ios::left);
        cout << setw(12) << "Размер" << setw(24) << "Обратный порядок" << setw(24) << "Упорядоченно" << setw(24) << "Вырожденно" << setw(24) << "Случайно" << endl;
        float table[10][9];
        Size = 1000;
        int l = 1;

        for (int i = 0; i < 10; i++)
        {
            vector<int> BaseArray(Size);
            vector<int> BaseArrayCopy(Size);
            for (int j = 1; j < 9; j += 2)
            {
                initarray(BaseArray, l);
                for (int i = 0; i < Size; i++)
                {
                    BaseArrayCopy[i] = BaseArray[i];
                }

                auto begin3 = chrono::steady_clock::now();
                Node *root = constructBST(BaseArray, Size);
                BaseArray = inorder(root);
                auto end3 = chrono::steady_clock::now();
                auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end3 - begin3);

                auto begin4 = chrono::steady_clock::now();
                massivesort(BaseArrayCopy, Size);
                auto end4 = chrono::steady_clock::now();
                auto elapsed_ms1 = chrono::duration_cast<chrono::nanoseconds>(end4 - begin4);

                table[i][j] = floor((elapsed_ms.count() / 1000000.0) * 100) / 100;
                table[i][j + 1] = floor((elapsed_ms1.count() / 1000000.0) * 100) / 100;

                l++;
            }
            Size *= 2;
            l = 1;
        }

        Size = 1000;

        for (int i = 0; i < 10; i++)
        {
            table[i][0] = Size;
            Size *= 2;
        }

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {

                cout << setw(12) << table[i][j];
            }
            cout << endl;
        }
    }
    }

    return 0;
}
