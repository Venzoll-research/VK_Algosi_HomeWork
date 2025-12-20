#include <iostream>
#include <vector>

long long countSequences(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1; // пустая последовательность
    if (n == 1) return 2; // "0" и "1"

    std::vector<long long> dp(n + 1);
    dp[0] = 1;
    dp[1] = 2;

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}


long long countSequences_2(int n) {
    if (n < 0) return 0;
    
    std::vector<long long> dp(n + 1);
    
    // Базовые случаи
    dp[0] = 1; // пустая последовательность
    if (n >= 1) dp[1] = 2; // "0", "1"
    if (n >= 2) dp[2] = 4; // "00", "01", "10", "11"
    
    // Заполняем массив
    for (int i = 3; i <= n; ++i) {
        dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
    }
    
    return dp[n];
}

int findLIS(const std::vector<int>& nums) {
    // Обрабатываем пустой массив
    if (nums.empty()) {
        return 0;
    }
    
    // Обрабатываем массив из одного элемента
    if (nums.size() == 1) {
        return 1;
    }
    
    // Создаем массив dp такой же длины, как nums, и заполняем единицами
    std::vector<int> dp(nums.size(), 1);
    
    // Заполняем массив dp
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i - 1] < nums[i]) {
            dp[i] = dp[i - 1] + 1;
        }
        // Иначе dp[i] остается 1
    }
    
    // Находим максимальное значение в dp
    return *std::max_element(dp.begin(), dp.end());
}

void printPascalTriangle(int n) {
    if (n <= 0) {
        std::cout << "Количество строк должно быть положительным числом!" << std::endl;
        return;
    }
    
    // Создаем двумерный массив для хранения треугольника Паскаля
    std::vector<std::vector<int>> dp(n, std::vector<int>());
    
    // Инициализируем массив: каждая строка имеет i+1 элементов, заполненных 1
    for (int i = 0; i < n; i++) {
        dp[i].resize(i + 1, 1);
    }
    
    // Заполняем массив значениями (кроме крайних элементов, которые уже равны 1)
    for (int row = 2; row < n; row++) {
        for (int col = 1; col < row; col++) {
            dp[row][col] = dp[row-1][col-1] + dp[row-1][col];
        }
    }
    
    // Выводим треугольник Паскаля
    std::cout << "Треугольник Паскаля для n = " << n << ":\n";
    for (int i = 0; i < n; i++) {
        // Добавляем отступ для центрирования
        for (int space = 0; space < n - i - 1; space++) {
            std::cout << "  ";
        }
        
        // Выводим элементы строки
        for (int j = 0; j <= i; j++) {
            std::cout << dp[i][j];
            if (j < i) {
                std::cout << "   ";
            }
        }
        std::cout << std::endl;
    }
}


int maxProfit(const std::vector<int>& prices) {
    if (prices.empty() || prices.size() < 2) {
        return 0; // Нельзя купить и продать
    }
    
    int minPrice = INT_MAX;  // Минимальная цена на текущий момент
    int maxProfit = 0;       // Максимальная прибыль на текущий момент
    
    for (int price : prices) {
        // Обновляем минимальную цену
        if (price < minPrice) {
            minPrice = price;
        }
        // Пробуем продать по текущей цене и обновляем максимальную прибыль
        else if (price - minPrice > maxProfit) {
            maxProfit = price - minPrice;
        }
    }
    
    return maxProfit;
}

int coinChange(std::vector<int>& coins, int amount) {
    if (amount < 0) return -1;
    if (amount == 0) return 0;
    
    // Изначально заполняем значением amount + 1 (как "бесконечность")
    std::vector<int> dp(amount + 1, amount + 1);
    
    // Базовый случай: для суммы 0 нужно 0 монет
    dp[0] = 0;
    
    // Перебираем все суммы от 1 до amount
    for (int i = 1; i <= amount; ++i) {
        // Проверяем каждую монету
        for (int coin : coins) {
            // Если монета может быть использована для текущей суммы
            if (coin <= i) {
                // Обновляем минимальное количество монет
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[amount] > amount ? -1 : dp[amount];
}

std::string longestPalindromeDP(const std::string& s) {
    int n = s.length();
    if (n <= 1) return s;
    
    // Создаем двумерный массив dp, где dp[i][j] = true, если подстрока s[i..j] - палиндром
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
    
    int start = 0;      // Начало самой длинной палиндромной подстроки
    int maxLength = 1;  // Длина самой длинной палиндромной подстроки
    
    // Все подстроки длины 1 - палиндромы
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }
    
    // Проверяем подстроки длины 2
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }
    
    // Проверяем подстроки длины 3 и больше
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;  // Конечный индекс подстроки
            
            // Подстрока s[i..j] - палиндром, если:
            // 1. s[i] == s[j]
            // 2. Подстрока s[i+1..j-1] - палиндром
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                
                if (len > maxLength) {
                    start = i;
                    maxLength = len;
                }
            }
        }
    }
    
    // Возвращаем найденную подстроку
    return s.substr(start, maxLength);
}

int main() {

    int n = 10;
    long long result = countSequences(n);
    std::cout << result << std::endl;

    long long result_2 = countSequences_2(n);
    std::cout << result_2 << std::endl;

    std::vector<std::vector<int>> testCases = {
        {3, 2, 8, 9, 5, 10},  
        {1, 2, 7, 9, 0, 10},  
        {8, 8, 8, 8},         
        {},                   
    };
    
    for (size_t i = 0; i < testCases.size(); ++i) {
        int result = findLIS(testCases[i]);
        std::cout << "Тест " << i + 1 << ": ";
        
        // Выводим массив
        std::cout << "[";
        for (size_t j = 0; j < testCases[i].size(); ++j) {
            std::cout << testCases[i][j];
            if (j < testCases[i].size() - 1) std::cout << ", ";
        }
        std::cout << "] -> " << result << std::endl;
    }

    printPascalTriangle(n);

    // Тестовые случаи
    std::vector<std::vector<int>> testCases_2 = {
        {8, 9, 3, 7, 4, 16, 12},  
        {1, 2, 3, 4, 5, 6, 7},    
        {8, 7, 6, 5, 4, 3, 2}     
    };

    for (size_t i = 0; i < testCases_2.size(); ++i) {
        int profit = maxProfit(testCases_2[i]);
        std::cout << "Тест " << i + 1 << ": [";
        for (size_t j = 0; j < testCases_2[i].size(); ++j) {
            std::cout << testCases_2[i][j];
            if (j < testCases_2[i].size() - 1) std::cout << ", ";
        }
        std::cout << "] -> Максимальная прибыль: " << profit << std::endl;
    }

    // Тестовые случаи
    std::vector<std::pair<std::vector<int>, int>> testCases_3 = {
        {{1, 2, 5}, 11},       
        {{1}, 0},                
        {{1}, 1},                
        {{1}, 2},              
        {{2, 5, 10, 1}, 27},    
    };
    
    for (size_t i = 0; i < testCases_3.size(); ++i) {
        std::vector<int> coins = testCases_3[i].first;
        int amount = testCases_3[i].second;
        
        int result = coinChange(coins, amount);
        
        std::cout << "Тест " << i + 1 << ":\n";
        std::cout << "  Монеты: [";
        for (size_t j = 0; j < coins.size(); ++j) {
            std::cout << coins[j];
            if (j < coins.size() - 1) std::cout << ", ";
        }
        std::cout << "]\n";
        std::cout << "  Сумма: " << amount << "\n";
        std::cout << "  Минимальное количество монет: " << result << "\n\n";
    }

    // Тестовые случаи
    std::vector<std::string> testCases_4 = {
        "babad",    
        "cbbd",      
        "a",       
        "accs",       
        "racecar",  
        "forgeeksskeegfor", 
        "abacdfgdcaba", 
        "aaa",      
        "abcd",      
        "",          
    };
    
    for (size_t i = 0; i < testCases_4.size(); ++i) {
        std::string result = longestPalindromeDP(testCases_4[i]);
        std::cout << "Тест " << i + 1 << ": \"" << testCases_4[i] 
                  << "\" -> \"" << result << "\"" << std::endl;
    }

    return 0;
}