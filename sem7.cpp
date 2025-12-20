#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>

using namespace std;

// Функция DFS для обхода компоненты связности, обход в глубину
void dfs(const vector<vector<int>>& graph, int v, vector<int>& visited, int color) {
    visited[v] = color; // Красим вершину в цвет компоненты
    for (int neighbor : graph[v]) { // Перебираем всех соседей
        if (visited[neighbor] == 0) { // Если сосед не посещён
            dfs(graph, neighbor, visited, color); // Рекурсивно обходим
        }
    }
}

// Функция для нахождения количества компонент связности
int findConnectedComponents(const vector<vector<int>>& graph, int n) {
    vector<int> visited(n + 1, 0); // Массив посещённых вершин (0 - не посещена)
    int color = 0; // счётчик компонент связности
    
    for (int i = 1; i <= n; i++) {  //  индексация с 1!
        if (visited[i] == 0) { // нашли новую компоненту
            color++;
            dfs(graph, i, visited, color);
        }
    }
    
    return color; // количество компонент связности
}

// Рекурсивная функция DFS для поиска цикла
bool dfs(const vector<vector<int>>& graph, int vertex, int parent, vector<bool>& visited) {
    visited[vertex] = true;  // Помечаем вершину как посещённую
    
    // Проверяем всех соседей текущей вершины
    for (int neighbor : graph[vertex]) {
        // Пропускаем родительскую вершину (ребро, по которому пришли)
        if (neighbor != parent) {
            // Если сосед уже посещён - найден цикл
            if (visited[neighbor]) {
                return true;
            }
            // Иначе рекурсивно проверяем соседа
            else if (dfs(graph, neighbor, vertex, visited)) {
                return true;
            }
        }
    }
    
    return false;  // Цикл не найден
}

// Основная функция для проверки наличия цикла в графе
bool hasCycle(const vector<vector<int>>& graph) {
    int n = graph.size();  // Количество вершин
    vector<bool> visited(n, false);  // Массив для отслеживания посещённых вершин
    
    // Проверяем каждую вершину графа
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {  // Если вершина не посещена
            // Запускаем DFS из этой вершины (родитель = -1, так как это корень)
            if (dfs(graph, i, -1, visited)) {
                return true;  // Найден цикл
            }
        }
    }
    
    return false;  // Цикл не найден
}

bool isTree(const vector<vector<int>>& graph, int start) {
    int n = graph.size();  // Количество вершин в графе
    if (n == 0) return true;  // Пустой граф считается деревом
    
    vector<bool> visited(n, false);  // Массив посещённых вершин
    queue<int> q;  // Очередь для BFS
    unordered_map<int, int> parent;  // Словарь для хранения родительских вершин
    
    // Инициализация начальной вершины
    q.push(start);
    visited[start] = true;
    parent[start] = -1;  // У начальной вершины нет родителя
    
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        
        // Обходим всех соседей текущей вершины
        for (int neighbor : graph[vertex]) {
            // Если сосед ещё не посещён
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
                parent[neighbor] = vertex;
            } 
            // Если сосед уже посещён и не является родителем текущей вершины
            else if (parent[vertex] != neighbor) {
                return false;  // Найден цикл - граф не дерево
            }
        }
    }
    
    // Проверяем, что все вершины были посещены
    for (bool v : visited) {
        if (!v) return false;  // Есть непосещённые вершины - граф несвязный
    }
    
    return true; 
}

// Функция алгоритма Дейкстры для поиска кратчайших путей
unordered_map<int, long long> dijkstra(const unordered_map<int, unordered_map<int, int>>& graph, int start) {
    // Создаем структуру данных для хранения кратчайших расстояний
    unordered_map<int, long long> distances;
    
    // Инициализируем все расстояния как бесконечность
    for (const auto& vertex_pair : graph) {
        int vertex = vertex_pair.first;
        distances[vertex] = numeric_limits<long long>::max();
    }
    
    // Расстояние до стартовой вершины равно 0
    distances[start] = 0;
    
    // Приоритетная очередь для хранения вершин и их расстояний
    // Используем пару (расстояние, вершина), приоритет по минимальному расстоянию
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> priority_queue;
    
    priority_queue.push({0, start});
    
    while (!priority_queue.empty()) {
        // Извлекаем вершину с минимальным расстоянием
        auto [current_distance, current_vertex] = priority_queue.top();
        priority_queue.pop();
        
        // Если текущее расстояние больше сохраненного, пропускаем
        if (current_distance > distances[current_vertex]) {
            continue;
        }
        
        // Обновляем расстояния до соседей
        for (const auto& neighbor_pair : graph.at(current_vertex)) {
            int neighbor = neighbor_pair.first;
            int weight = neighbor_pair.second;
            
            long long distance = current_distance + weight;
            
            // Если нашли более короткий путь
            if (distance < distances[neighbor]) {
                distances[neighbor] = distance;
                priority_queue.push({distance, neighbor});
            }
        }
    }
    
    return distances;
}

bool bfs_1(int start, const vector<vector<int>>& graph, vector<int>& colors) {
    queue<int> q;
    q.push(start);
    colors[start] = 1; // Красим начальную вершину в первый цвет
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        // Обходим всех соседей текущей вершины
        for (int neighbor : graph[node]) {
            if (colors[neighbor] == 0) { // Если сосед ещё не раскрашен
                colors[neighbor] = -colors[node]; // Красим в противоположный цвет
                q.push(neighbor);
            } else if (colors[neighbor] == colors[node]) { // Если сосед имеет тот же цвет
                return false; // Граф не двухдольный
            }
        }
    }
    
    return true;
}

// Основная функция для проверки графа на двудольность
bool isBipartite(const vector<vector<int>>& graph) {
    int n = graph.size(); // Количество вершин в графе
    
    // Массив для хранения цветов вершин
    // 0 - не раскрашена, 1 - первый цвет, -1 - второй цвет
    vector<int> colors(n, 0);
    
    // Проверяем все вершины (на случай несвязного графа)
    for (int i = 0; i < n; i++) {
        if (colors[i] == 0) { // Если вершина ещё не посещена
            if (!bfs_1(i, graph, colors)) { // Запускаем BFS и проверяем
                return false; // Граф не двухдольный
            }
        }
    }
    
    return true; // Граф двухдольный
}

int main() {
    int n = 6; // 6 вершин 
    vector<vector<int>> graph(n + 1); // индексация с 1, поэтому размер n+1
    
    graph[1].push_back(2);
    graph[2].push_back(1);
    graph[2].push_back(3);
    graph[3].push_back(2);
    
    graph[4].push_back(5);
    graph[5].push_back(4);
    graph[5].push_back(6);
    graph[6].push_back(5);
    
    int components = findConnectedComponents(graph, n);
    cout << "Граф имеет " << components << " компонент(ы) связности" << endl;

    int n1 = 5;
    vector<vector<int>> graph1(n1);
    
    // граф с циклом: 0-1-2-3-4-0
    graph1[0] = {1, 4};
    graph1[1] = {0, 2};
    graph1[2] = {1, 3};
    graph1[3] = {2, 4};
    graph1[4] = {3, 0};

    cout << "Граф 1: ";
    if (hasCycle(graph1)) {
        cout << "содержит цикл" << endl;
    } else {
        cout << "не содержит цикл" << endl;
    }

        int n2 = 4;
    vector<vector<int>> graph2(n2);
    
    // дерево: 0-1, 0-2, 1-3
    graph2[0] = {1, 2};
    graph2[1] = {0, 3};
    graph2[2] = {0};
    graph2[3] = {1};
    
    cout << "Граф 2: ";
    if (hasCycle(graph2)) {
        cout << "содержит цикл" << endl;
    } else {
        cout << "не содержит цикл" << endl;
    }

    cout << "Граф 1: ";
    if (isTree(graph1, 0)) {
        cout << "является деревом" << endl;
    } else {
        cout << "не является деревом" << endl;
    }

        cout << "Граф 2: ";
    if (isTree(graph2, 0)) {
        cout << "является деревом" << endl;
    } else {
        cout << "не является деревом" << endl;
    }

    unordered_map<int, unordered_map<int, int>> graph5;
    
    // Добавляем вершины и рёбра
    graph5[0] = {{1, 4}, {2, 1}};
    graph5[1] = {{3, 1}};
    graph5[2] = {{1, 2}, {3, 5}};
    graph5[3] = {};
    
    int start1 = 0;
    auto distances1 = dijkstra(graph5, start1);
    
    cout << "Пример 1: Кратчайшие расстояния от вершины " << start1 << ":\n";
    for (const auto& d : distances1) {
        cout << "До вершины " << d.first << ": ";
        if (d.second == numeric_limits<long long>::max()) {
            cout << "нет пути\n";
        } else {
            cout << d.second << "\n";
        }
    }

    // Пример 1: Двудольный граф
    int n6 = 4;
    vector<vector<int>> graph6(n1);
    
    // Создаём двудольный граф:
    // Доли: {0, 1} и {2, 3}
    // Рёбра: 0-2, 0-3, 1-2, 1-3
    graph6[0] = {1, 3};
    graph6[1] = {0, 2};
    graph6[2] = {1, 3};
    graph6[3] = {0, 2};
    
    cout << "Граф 6: ";
    if (isBipartite(graph6)) {
        cout << "является двудольным" << endl;
    } else {
        cout << "не является двудольным" << endl;
    }
    
    return 0;
}