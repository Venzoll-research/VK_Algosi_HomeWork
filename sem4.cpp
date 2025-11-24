
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Определение структуры узла дерева
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// Рекурсивная функция построения дерева из массива
TreeNode* buildTree(const vector<int>& arr, int i) {
    if (i >= arr.size() || arr[i] == -1) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(arr[i]);
    root->left = buildTree(arr, 2 * i + 1);
    root->right = buildTree(arr, 2 * i + 2);

    return root;
}

// Вспомогательная функция для печати дерева (обход в ширину)
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

bool isSymmetric(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        vector<TreeNode*> currentLevel;

        // Собираем все узлы текущего уровня
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            currentLevel.push_back(node);

            if (node != nullptr) {
                q.push(node->left);
                q.push(node->right);
            }
        }

        // Проверяем симметричность текущего уровня
        for (int i = 0; i < levelSize / 2; i++) {
            TreeNode* leftNode = currentLevel[i];
            TreeNode* rightNode = currentLevel[levelSize - 1 - i];

            // Оба узла nullptr - симметрично
            if (leftNode == nullptr && rightNode == nullptr) {
                continue;
            }

            // Один из узлов nullptr - несимметрично
            if (leftNode == nullptr || rightNode == nullptr) {
                return false;
            }

            // Значения не совпадают - несимметрично
            if (leftNode->val != rightNode->val) {
                return false;
            }
        }
    }

    return true;
}

// Функция обхода в глубину 
void depthSearch(TreeNode* root, vector<int>& res) {
    if (root == nullptr) {
        return;
    }

    depthSearch(root->left, res);
    res.push_back(root->val);
    depthSearch(root->right, res);
}

// Проверка симметричности через обход в глубину и проверку палиндрома
bool isSymmetricDFS(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }

    vector<int> data;
    depthSearch(root, data);

    int j = data.size() - 1;
    for (int i = 0; i < data.size() / 2; i++) {
        if (data[i] != data[j]) {
            return false;
        }
        j--;
    }

    return true;
}

// Рекурсивное решение (DFS)
int minDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    // Если узел - лист
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }

    // Если есть оба потомка
    if (root->left != nullptr && root->right != nullptr) {
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }

    // Если есть только левый потомок
    if (root->left != nullptr) {
        return 1 + minDepth(root->left);
    }

    // Если есть только правый потомок
    return 1 + minDepth(root->right);
}

// 
int maxMinMultiplication(const vector<int>& data) {
    if (data.size() < 3) {
        return -1;
    }

    int min_index = 1;
    int max_index = 2;

    // Находим самый левый узел в левом поддереве
    for (int i = 1; i < data.size(); i = 2 * i + 1) {
        min_index = i;
    }

    // Находим самый правый узел в правом поддереве
    for (int i = 2; i < data.size(); i = 2 * i + 2) {
        max_index = i;
    }

    // Проверяем, что индексы не выходят за границы массива
    if (min_index >= data.size() || max_index >= data.size()) {
        return -1;
    }

    int result = data[min_index] * data[max_index];
    return result;
}

//рекурсивный подход
bool isSameTree(TreeNode* a, TreeNode* b) {
    if (a == nullptr && b == nullptr) {
        return true;
    }
    if (a == nullptr || b == nullptr) {
        return false;
    }
    if (a->val != b->val) {
        return false;
    }

    return isSameTree(a->left, b->left) && isSameTree(a->right, b->right);
}

int main() {
    // Пример массива для построения дерева
    vector<int> arr = {1, 2, 3, -1, -1, 4, 5};

    // Построение дерева
    TreeNode* root = buildTree(arr, 0);

    cout << "Построенное дерево (обход в ширину): ";
    printTree(root);

    // Симметричное дерево
    vector<int> symmetricTree = {1, 2, 2, 3, 4, 4, 3};
    TreeNode* root1 = buildTree(symmetricTree, 0);
    cout << "Симметричное дерево: " << (isSymmetric(root1) ? "true" : "false") << endl;

    // Несимметричное дерево
    vector<int> asymmetricTree = {1, 2, 2, -1, 3, -1, 3};
    TreeNode* root2 = buildTree(asymmetricTree, 0);
    cout << "Несимметричное дерево: " << (isSymmetric(root2) ? "true" : "false") << endl;

    // Симметричное дерево
    vector<int> symmetricTree2 = {1, 2, 2, 3, 4, 4, 3};
    TreeNode* root12 = buildTree(symmetricTree, 0);
    cout << "Симметричное дерево (палиндром): " << (isSymmetricDFS(root1) ? "true" : "false") << endl;

    // Несимметричное дерево
    vector<int> asymmetricTree2 = {1, 2, 3};
    TreeNode* root22 = buildTree(symmetricTree, 0);
    cout << "Несимметричное дерево (палиндром): " << (isSymmetricDFS(root2) ? "true" : "false") << endl;

    // Пример1: Сбалансированное дерево
    vector<int> tree1 = {3, 9, 20, -1, -1, 15, 7};
    TreeNode* root31 = buildTree(tree1, 0);
    cout << "Пример 1: " << minDepth(root1) << endl;

    // Пример 2: Несбалансированное дерево
    vector<int> tree2 = {2, -1, 3, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, 5};
    TreeNode* root32 = buildTree(tree2, 0);
    cout << "Пример 2: " << minDepth(root2) << endl;

    // Пример 1: Полное бинарное дерево
    vector<int> tree14 = {1, 2, 3, 4, 5, 6, 7};
    cout << "Пример 1: " << maxMinMultiplication(tree14) << endl;

    // Пример 2: Неполное дерево
    vector<int> tree24 = {1, 2, 3, 4, -1, 6, 7};
    cout << "Пример 2: " << maxMinMultiplication(tree24) << endl;

    // Пример 3: Маленькое дерево
    vector<int> tree34 = {1, 2, 3};
    cout << "Пример 3: " << maxMinMultiplication(tree34) << endl;

    // Два одинаковых дерева
    vector<int> tree15 = {1, 2, 3};
    TreeNode* root15 = buildTree(tree15, 0);
    TreeNode* root25 = buildTree(tree15, 0);
    cout << "Одинаковые деревья: " << (isSameTree(root15, root25) ? "true" : "false") << endl;

    // Разные деревья
    vector<int> tree25 = {1, 2, 3};
    vector<int> tree35 = {1, 2, 4};
    TreeNode* root35 = buildTree(tree25, 0);
    TreeNode* root45 = buildTree(tree35, 0);
    cout << "Разные деревья: " << (isSameTree(root35, root45) ? "true" : "false") << endl;

    return 0;
}