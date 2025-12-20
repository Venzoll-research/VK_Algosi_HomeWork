#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>
#include <string>


using namespace std;

long long maxSubarraySum(const vector<int>& arr, int k) {
    int n = arr.size();
    
    // Если длина массива меньше k, возвращаем минимальное значение (аналог null)
    if (n < k) {
        return LLONG_MIN; // или можно бросить исключение
    }
    
    long long currentSum = 0;
    
    // Вычисляем сумму первого окна
    for (int i = 0; i < k; i++) {
        currentSum += arr[i];
    }
    
    long long maxSum = currentSum;
    
    // Скользящее окно: перемещаем окно на одну позицию вправо
    for (int i = k; i < n; i++) {
        currentSum = currentSum - arr[i - k] + arr[i];
        maxSum = max(maxSum, currentSum);
    }
    
    return maxSum;
}

int subarraySum(vector<int>& nums, int k) {
    int prefixSum = 0;
    // Инициализация: префиксная сумма 0 встречается 1 раз
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;
    int count = 0;

    for (int num : nums) {
        prefixSum += num;
        // Проверяем, есть ли в prefixCount значение prefixSum - k
        if (prefixCount.find(prefixSum - k) != prefixCount.end()) {
            count += prefixCount[prefixSum - k];
        }
        // Обновляем словарь для текущей префиксной суммы
        prefixCount[prefixSum]++;
    }

    return count;
}

int findMaxLength(vector<int>& nums) {
    int prefixSum = 0;
    int maxLen = 0;
    // Инициализация: сумма 0 встречается на позиции -1
    unordered_map<int, int> indexMap;
    indexMap[0] = -1;

    for (int i = 0; i < nums.size(); i++) {
        // Заменяем 0 на -1, 1 оставляем как +1
        prefixSum += (nums[i] == 0) ? -1 : 1;

        // Проверяем, встречалась ли такая префиксная сумма раньше
        if (indexMap.find(prefixSum) != indexMap.end()) {
            // Если сумма уже встречалась, обновляем maxLen
            maxLen = max(maxLen, i - indexMap[prefixSum]);
        } else {
            // Иначе сохраняем первую позицию для этой суммы
            indexMap[prefixSum] = i;
        }
    }

    return maxLen;
}

int pivotIndex(vector<int>& nums) {
    int totalSum = 0;
    int leftSum = 0;
    
    // Вычисляем общую сумму элементов массива
    for (int i = 0; i < nums.size(); i++) {
        totalSum += nums[i];
    }
    
    // Проверяем каждый индекс, чтобы найти пивот
    for (int i = 0; i < nums.size(); i++) {
        // Проверяем, является ли текущий индекс пивотом
        if (leftSum == totalSum - leftSum - nums[i]) {
            return i; // Возвращаем индекс, если нашли пивот
        }
        
        // Обновляем leftSum для следующего индекса
        leftSum += nums[i];
    }
    
    return -1; // Если пивот не найден, возвращаем -1
}

bool canMakeValidWithDeletions(string s, int k) {
    int balance = 0;
    int extra_closed_balance = 0;

    // Проходим по всем символам строки
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            balance += 1;
        } else { // s[i] == ')'
            if (balance > 0) {
                balance -= 1; // Закрываем открытую скобку
            } else {
                extra_closed_balance += 1; // Лишняя закрывающая скобка
            }
        }
    }

    // Общее количество скобок, которые нужно удалить
    int total_needed = balance + extra_closed_balance;

    // Можно ли сделать строку валидной, удалив не более k символов?
    return total_needed <= k;
}

int main() {
    // Пример использования
    vector<int> arr = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int k = 4;
    
    long long result = maxSubarraySum(arr, k);
    
    cout << "Maximum sum of subarray of length " << k << " is: " << result << endl;

    vector<int> nums = {1, 1, 1};
    int k_2 = 2;
    
    int result_2 = subarraySum(nums, k_2);
    cout << "Number of subarrays with sum " << k_2 << ": " << result_2 << endl;

    vector<int> nums_3 = {0, 1, 0, 0, 1, 1, 0};
    
    int result_3 = findMaxLength(nums_3);
    cout << "Maximum length of subarray with equal number of 0s and 1s: " << result_3 << endl;

    vector<int> nums_4 = {9, 4, 8, 7, 1, 11, 2, 6, 1};
    
    int result_4 = pivotIndex(nums_4);
    cout << "Pivot index: " << result_4 << endl;

    string s1 = "()())()";
    int k1 = 2;
    cout << "Can make valid: " << (canMakeValidWithDeletions(s1, k1) ? "true" : "false") << endl;
    cout << endl;    
    
    return 0;
}