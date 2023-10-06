#include <iostream>
#include <queue>
#include <stack>
using namespace std;
struct NodeTree // Структура, представляющая собой элемент в дереве
{
    char symbol; // По заданию требуется использовать символьную переменную
    NodeTree* left; // Указатель на левое поддерево
    NodeTree* right; // Указатель на правое поддерево
    NodeTree(char symbol) : symbol(symbol), left(nullptr), right(nullptr) {} // Конструктор, инициализирующий поля класса
};
class Tree
{
private:
    NodeTree* head; // Указатель на корень дерева
public:
    Tree() : head(nullptr) // Конструктор, инициализирующий поле head
    {}
    NodeTree* getHead() // Метод для получения указателя на корень дерева
    { return head; }
    bool insert(char symbol) // Метод добавления узла в дерево по специальным правилам для БДП
    {
        if (!symbol || symbol < 0 || symbol > 128) // Проверка символа на выход из ASCII
            return false;
        if (head == nullptr) // Если элементов еще нет
            head = new NodeTree(symbol); // То создаём корень дерева
        else // Иначе добавляем элемент по специальным правилам
        {
            NodeTree* current = head; // Текущий элемент
            NodeTree* parent = nullptr; // Вспомогательный элемент для отслеживания связей между узлами
            while (current != nullptr)
            {
                parent = current; // Указатель parent на уровень выше, чем current
                if (current->symbol > symbol) // Правила по какому поддереву идти для вставки элемента
                    current = current->left;
                else if (current->symbol < symbol)
                    current = current->right;
                else // Если такой символ уже есть в дереве, вставка невозможна
                    return false;
            }
            if (parent->symbol > symbol) // Условия, к какому именно листу добавить ребенка
                parent->left = new NodeTree(symbol);
            else
                parent->right = new NodeTree(symbol);
        }
        return true;
    }
    //NodeTree* searchItem(NodeTree* node) // Поиск производится путём обхода дерева в ширину
    //{
    //    queue<NodeTree*> que;
    //    que.push(node);
    //    NodeTree* current;
    //    while (!que.empty())
    //    {
    //        current = que.front();
    //        que.pop();
    //        if (current->symbol == node->symbol)
    //            return current;
    //        if (current->left != nullptr)
    //            que.push(current->left);
    //        else if (current->right != nullptr)
    //            que.push(current->right);
    //        else
    //            return nullptr;
    //    }
    //    return nullptr;
    //}
    void symmetricalPassageTree(NodeTree* node) // Метод для симметричного обхода дерева с элемента node
    {
        if (node == nullptr) // Если узла нет, обход невозможен
            return;
        stack<NodeTree*> stack; // Структура данных, необходимая для итеративного симметричного обхода дерева
        NodeTree* current = node; // Текущий элемент
        while (current != nullptr || !stack.empty()) // Если current есть и стек не пустой
        {
            while (current != nullptr) // Для добавления в стек поддеревьев слева
            {
                stack.push(current); // Добавление в стек
                current = current->left; // Движение по левому поддереву
            }
            current = stack.top(); // Получение последнего добавленного элемента
            stack.pop(); // Удаление из стека последнего добавленного элемента
            cout << current->symbol << " "; // Вывод на экран узлов дерева в порядке увеличения
            current = current->right; // Движение уже по правым поддеревьям
        }
    }
    // Метод для обратного обхода данного дерева с целью получения суммы (в ASCII) со всех узлов дерева
    // Начиная с node, используя рекурсивный алгоритм
    int reversePassageTree(NodeTree* node) // node - начальный узел
    {
        if (node == nullptr) // У пустого узла нет данных
            return 0;
        int counter = node->symbol; // Присвоение суммы, начиная с node
        counter += reversePassageTree(node->left); // Рекурсивно проходимся по левому поддереву
        counter += reversePassageTree(node->right); // Аналогично для правого поддерева
        return counter;
    }
    int leavesSumm() // Метод, позволяющий получить сумму элементов только у листьев
    {
        int leafSumm = 0;
        stack<NodeTree*> stack; // Необходимая структура данных для итеративного алгоритма
        stack.push(head); // Начинаем с корня
        NodeTree* current; // Текущий элемент
        while (!stack.empty()) // Пока в стеке есть элементы
        {
            current = stack.top(); // Достаём последний положенный элемент
            stack.pop(); // удаляем его из стека
            if (current->left == nullptr && current->right == nullptr) // Если это лист
                leafSumm += current->symbol; // Если узел - лист, добавляем его значение к сумме
            // Иначе продолжаем добираться до листьев, путём добавления в стек правого и левого поддеревьев
            if (current->right != nullptr)
                stack.push(current->right);
            if (current->left != nullptr)
                stack.push(current->left);
        }
        return leafSumm;
    }
    int heighTree(NodeTree* node) // Метод, позволяющий получить высоту БДП
    {
        if (node == nullptr) // У пустого дерева высота = -1
            return -1;
        // Высота дерева равна максимальной высоте из левого и правого поддеревьев плюс 1 (для текущего узла)
        return max(heighTree(node->left), heighTree(node->right)) + 1;
    }
    ~Tree() // Деструктор для освобождения памяти, используя оптимальный для данной цели вариант обхода.
        // При таком обходе удаляются сначала листья, а потом уже и родители, ставшие тоже листьями.
        // Т.е не будет утечки памяти.
    {
        stack<NodeTree*> stack;
        NodeTree* current = head;
        while (current != nullptr || !stack.empty())
        {
            while (current != nullptr)
            {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            stack.pop();
            NodeTree* temp = current;
            current = current->right;
            delete temp;
        }
    }
};
int main()
{
    setlocale(0, "");
    Tree tree;
    short stop;
    cout << "Программа представляет собой бинарное дерево поиска. Данное дерево позволяет не задумываясь " << endl <<
        "правильно вставлять элементы и иметь быструю логарифмическую сложность "
        "при поиске и удалении элементов," << endl << "т.к всегда отбрасывается половина от исходного дерева." << endl << endl;
    char symbol;
    cout << "Введите символ, который хотите записать в бинарное дерево ((ctrl + Z)  - остановка): ";
    while (cin >> symbol)
    {
        cout << "Введите символ, который хотите записать в бинарное дерево ((ctrl + Z)  - остановка): ";
        cin.clear(); // метод clear() сбрасывает флаги ошибок ввода
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Позволяет игнорировать все символы до символа новой строки включительно
        tree.insert(symbol);
    }
    cout << "Что следует сделать?" << endl;
    cout << "1. Выполнить симметричный обход дерева. (для БДП узлы будут выведены в порядке возрастания)." << endl <<
        "2. Вычислить сумму узлов дерева (в кодировке ASCII с использованием обратного обхода дерева)." << endl <<
        "3. Вычислить сумму только листьев дерева." << endl <<
        "4. Вычислить высоту дерева (самый длинный путь от заданной точки до листа)." << endl;
    cin.clear();
    cin >> stop;
    switch (stop)
    {
    case 1:
        cout << "Элементы узлов дерева, используя симметричный обход дерева: ";
        tree.symmetricalPassageTree(tree.getHead());
        cout << "\n";
        break;
    case 2:
        cout << "Сумма узлов всего дерева: " << tree.reversePassageTree(tree.getHead()) << endl;
        break;
    case 3:
        cout << "Сумма элементов листьев дерева в кодировке ASCII: " << tree.leavesSumm() << endl;
        break;
    case 4:
        cout << "Высота дерева, начиная с корня: " << tree.heighTree(tree.getHead()) << endl;
        break;
    default:
        cout << "Неверно введён номер команды!" << endl;
        break;
    }
}