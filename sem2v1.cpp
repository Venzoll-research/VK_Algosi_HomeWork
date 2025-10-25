#include <iostream>
#include <string>


template <typename T>
class LinkedList {
   private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t list_size;

   public:
    // Конструктор по умолчанию
    LinkedList() : head(nullptr), list_size(0) {}

    // Деструктор
    ~LinkedList() {
        clear();
    }

    // Добавление в конец
    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!head) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
        list_size++;
    }

    void push_front(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        list_size++;
    }

    void pop_front() {
        if (!head) return;

        Node* temp = head;
        head = head->next;
        delete temp;
        list_size--;
    }

    T& front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    const T& front() const {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    T& back() {
        if (!head) throw std::runtime_error("List is empty");

        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        return current->data;
    }

    const T& back() const {
        if (!head) throw std::runtime_error("List is empty");

        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        return current->data;
    }

    // Получение размера списка
    size_t size() const {
        return list_size;
    }

    // Проверка на пустоту
    bool empty() const {
        return list_size == 0;
    }

    // Очистка списка
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        list_size = 0;
    }

    // Вывод списка
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    bool hasCycle() const {
        // Если список пустой или содержит один элемент без цикла
        if (!head || !head->next) {
            return false;
        }

        Node* slow = head;        // Медленный указатель (двигается на 1 узел)
        Node* fast = head->next;  // Быстрый указатель (двигается на 2 узла)

        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            slow = slow->next;        // Медленный идет на 1 шаг
            fast = fast->next->next;  // Быстрый идет на 2 шага
        }
        return true;
    }

    void reverseLinkedList() {
        Node* prev = nullptr;  // Предыдущий узел
        Node* current = head;  // Текущий узел
        Node* next = nullptr;

        while (current) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    T middleNode() const {
        if (!head) {
            throw std::runtime_error("List is empty");
        }

        Node* slow = head; 
        Node* fast = head;  //двигается на 2 элемента

        // Пока быстрый указатель не достиг конца списка
        while (fast && fast->next) {
            slow = slow->next;        
            fast = fast->next->next; 
        }

        return slow->data;
    }

    void removeElement(const T& value) {
        Node* dummy = new Node(T()); 
        dummy->next = head;

        Node* prev = dummy;
        Node* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                prev->next = current->next;
                list_size--;
            } else {
                prev = current;
            }
            current = current->next;
        }

        head = dummy->next;
        delete dummy;
    }
};

template <typename T>
class Stack {
   private:
    LinkedList<T> list;

   public:
    void push(const T& value) {
        list.push_front(value); 
    }

    T pop() {
        if (list.empty()) {
            throw std::runtime_error("Stack is empty");
        }

        T value = list.front();  
        list.pop_front();        
        return value;
    }

    T& top() {
        return list.front();
    }

    const T& top() const {
        return list.front();
    }

    // Проверка на пустоту
    bool empty() const {
        return list.empty();
    }

    // Получение размера стека
    size_t size() const {
        return list.size();
    }

    // Очистка стека
    void clear() {
        list.clear();
    }

    // Вывод стека
    void print() const {
        list.print();
    }
};

template <typename T>
class Queue {
   private:
    LinkedList<T> list;

   public:
    // Добавление элемента в конец очереди
    void enqueue(const T& value) {
        list.push_back(value);
    }

    // Удаление элемента из начала очереди и возврат значения
    T dequeue() {
        if (list.empty()) {
            throw std::runtime_error("Queue is empty");
        }

        T value = list.front();
        list.pop_front();        
        return value;
    }

    // Получение элемента из начала очереди без удаления
    T& front() {
        return list.front();
    }

    const T& front() const {
        return list.front();
    }

    // Получение элемента из конца очереди
    T& back() {
        return list.back();
    }

    const T& back() const {
        return list.back();
    }

    // Проверка на пустоту
    bool empty() const {
        return list.empty();
    }

    // Получение размера очереди
    size_t size() const {
        return list.size();
    }

    // Очистка очереди
    void clear() {
        list.clear();
    }

    // Вывод очереди
    void print() const {
        list.print();
    }
};

bool isSubsequence(const std::string& a, const std::string& b) {
    Queue<char> q;

    for (char c : a) {
        q.enqueue(c);
    }

    for (char c : b) {
        if (!q.empty() && q.front() == c) {
            q.dequeue(); 
        }
    }

    return q.empty();
}

bool isSubsequenceTwoPointers(const std::string& a, const std::string& b) {
    int i = 0, j = 0;

    while (i < a.length() && j < b.length()) {
        if (a[i] == b[j]) {
            i++;
        }
        j++;
    }
    return i == a.length();
}

bool isPalindrome(const std::string& word) {
    Stack<char> stack;

    for (char c : word) {
        stack.push(std::tolower(c));
    }

    for (char c : word) {
        if (std::tolower(c) != stack.pop()) {
            return false;
        }
    }

    return true;
}

bool isPalindromeTwoPointers(const std::string& s) {
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}


int main() {
    LinkedList<int> list;
    bool cycle;

    list.push_back(1);
    list.push_back(2);
    list.push_back(0);
    list.push_back(5);
    list.push_back(3);
    list.push_back(4);
    list.push_back(9);

    cycle = list.hasCycle();
    std::cout << cycle << std::endl;

    list.print();
    list.reverseLinkedList();
    list.print();
    std::cout << list.middleNode() << std::endl;

    list.removeElement(9);
    list.print();

    //~~~~~~~~~~~~~~~~~~~~~~~~СТЭК~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << "Stack: ";
    stack.print();  // 3 2 1

    std::cout << "Top: " << stack.top() << std::endl;  // 3

    int popped = stack.pop();
    std::cout << "Popped value: " << popped << std::endl;  // 3
    std::cout << "After pop: ";
    stack.print();  // 2 1

    //~~~~~~~~~~~~~~~~~~~~~~~ОЧЕРЕДЬ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << "Queue: ";
    queue.print();  // 1 2 3

    std::cout << "Front: " << queue.front() << std::endl;  // 1
    std::cout << "Back: " << queue.back() << std::endl;    // 3

    int dequeued = queue.dequeue();
    std::cout << "Dequeued value: " << dequeued << std::endl;  // 1
    std::cout << "After dequeue: ";
    queue.print();  // 2 3

    //~~~~~~~~~~~~~~~~~~ДАЛЬШЕ ПО ЗАДАНИЮ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

    std::string a = "abc";
    std::string b = "ahbgdc";
    std::string c = "axc";
    std::string d = "ahbha";

    std::cout << isSubsequence(a, b) << std::endl;  // true
    std::cout << isSubsequence(c, b) << std::endl;  // false

    std::cout << isSubsequenceTwoPointers(a, b) << std::endl;  // true
    std::cout << isSubsequenceTwoPointers(c, b) << std::endl;  // false

    std::cout << isPalindromeTwoPointers(d) << std::endl;
    std::cout << isPalindrome(d) << std::endl;

    return 0;
}