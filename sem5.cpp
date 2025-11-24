#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* createTree(const vector<int>& nodes, int index = 0) {
    if (index >= nodes.size() || nodes[index] == -1) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(nodes[index]);
    root->left = createTree(nodes, 2 * index + 1);
    root->right = createTree(nodes, 2 * index + 2);

    return root;
}

void printTree(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (current) {
            cout << current->val << " ";
            q.push(current->left);
            q.push(current->right);
        } else {
            cout << "null ";
        }
    }
    cout << endl;
}


// Функция проверки max-кучи
bool isMaxHeap(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[i] < arr[left]) {
            return false;
        }
        if (right < n && arr[i] < arr[right]) {
            return false;
        }
    }
    return true;
}

bool isMaxHeapBFS(const vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) {
        return true;
    }

    // Используем очередь для BFS обхода
    queue<int> q;
    q.push(0);  // начинаем с корня

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Проверяем левого потомка
        if (left < n) {
            if (arr[i] < arr[left]) {
                return false;
            }
            q.push(left);
        }

        // Проверяем правого потомка
        if (right < n) {
            if (arr[i] < arr[right]) {
                return false;
            }
            q.push(right);
        }
    }
    return true;
}

bool isCompleteTree(TreeNode* root) {
    if (!root) {
        return true;
    }

    queue<TreeNode*> q;
    q.push(root);
    bool shouldBeLeaf = false;

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (!node) {
            shouldBeLeaf = true;
        } else {
            // Если мы уже встретили пустой узел, но текущий узел не пустой,
            // значит дерево не является полным
            if (shouldBeLeaf) {
                return false;
            }
            // Добавляем потомков в очередь (даже если они nullptr)
            q.push(node->left);
            q.push(node->right);
        }
    }
    return true;
}

vector<int> mergeKSortedArraysSimple(const vector<vector<int>>& sortedArrays) {
    vector<int> mergedArray;
    priority_queue<int, vector<int>, greater<int>> minHeap;  // min-heap

    // Добавляем все элементы в min-heap
    for (const auto& arr : sortedArrays) {
        for (int num : arr) {
            minHeap.push(num);
        }
    }

    // Извлекаем элементы из кучи (они будут в отсортированном порядке)
    while (!minHeap.empty()) {
        mergedArray.push_back(minHeap.top());
        minHeap.pop();
    }

    return mergedArray;
}

int kthSmallestIterative(TreeNode* root, int k) {
    stack<TreeNode*> st;
    TreeNode* current = root;
    int counter = 0;

    while (!st.empty() || current != nullptr) {
        // Спускаемся влево, добавляя узлы в стек
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        // Извлекаем узел из стека
        current = st.top();
        st.pop();
        counter++;

        // Если это k-й элемент, возвращаем его значение
        if (counter == k) {
            return current->val;
        }

        // Переходим к правому поддереву
        current = current->right;
    }

    return -1;  // Если k превышает количество узлов
}

// Итеративная функция зеркального отражения (BFS)
TreeNode* mirrorTreeIterative(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }

    // Очередь для обхода в ширину (BFS)
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        // Меняем местами левого и правого потомка
        TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;

        // Добавляем в очередь дочерние узлы
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
    return root;
}

// Рекурсивная функция зеркального отражения (DFS)
TreeNode* mirrorTreeRecursive(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }

    // Рекурсивно отражаем левое и правое поддеревья
    TreeNode* left = mirrorTreeRecursive(root->left);
    TreeNode* right = mirrorTreeRecursive(root->right);

    // Меняем местами поддеревья
    root->left = right;
    root->right = left;

    return root;
}

int main() {
    // Тестовые примеры

    // Корректная max-куча
    vector<int> maxHeap = {90, 15, 10, 7, 12, 2};
    cout << "Корректная max-куча: " << (isMaxHeap(maxHeap) ? "true" : "false") << endl;

    // Некорректная max-куча
    vector<int> notMaxHeap = {10, 15, 5, 7, 12, 2};
    cout << "Некорректная max-куча: " << (isMaxHeap(notMaxHeap) ? "true" : "false") << endl;

    // Корректная max-куча
    vector<int> maxHeap2 = {90, 15, 10, 7, 12, 2};
    cout << "Корректная max-куча (BFS): " << (isMaxHeapBFS(maxHeap2) ? "true" : "false") << endl;

    // Некорректная max-куча
    vector<int> notMaxHeap2 = {10, 15, 5, 7, 12, 2};
    cout << "Некорректная max-куча (BFS): " << (isMaxHeapBFS(notMaxHeap2) ? "true" : "false") << endl;

    // Полное дерево
    vector<int> completeTree = {1, 2, 3, 4, 5, 6};
    TreeNode* root1 = createTree(completeTree);
    cout << "Полное дерево: " << (isCompleteTree(root1) ? "true" : "false") << endl;

    // Неполное дерево (пропуск в середине)
    vector<int> incompleteTree = {1, 2, 3, 4, -1, 6};
    TreeNode* root2 = createTree(incompleteTree);
    cout << "Неполное дерево: " << (isCompleteTree(root2) ? "true" : "false") << endl;

    // Тестовые примеры
    vector<vector<int>> sortedArrays = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}};

    vector<int> result1 = mergeKSortedArraysSimple(sortedArrays);

    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> values = {5, 3, 6, 1, 2, 7};
    TreeNode* root = createTree(values);

    cout << "Итеративная реализация:" << endl;
    for (int k = 1; k <= 6; k++) {
        cout << k << "-й наименьший элемент: " << kthSmallestIterative(root, k) << endl;
    }

    cout << endl;

    vector<int> treeNodes = {1, 2, 3, 4, 5, 6, 7};
    TreeNode* root5 = createTree(treeNodes);

    // Создаем копию для рекурсивного метода
    TreeNode* rootRecursive = createTree(treeNodes);

    // Применяем итеративное зеркальное отражение
    TreeNode* mirroredIterative = mirrorTreeIterative(root);

    // Применяем рекурсивное зеркальное отражение
    TreeNode* mirroredRecursive = mirrorTreeRecursive(rootRecursive);

    return 0;
}