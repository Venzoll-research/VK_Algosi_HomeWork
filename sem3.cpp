#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int binarySearchSqrt(int target) {
    if (target < 2) return target;  // Обработка случаев 0 и 1

    int left = 1;
    int right = target / 2;  // Корень не может превышать target/2 при target > 1

    while (left <= right) {
        int mid = left + (right - left) / 2;
        long long square = mid * mid;

        if (square == target) {
            return mid;
        } else if (square < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return right;
}

long long copyTime(int n, int x, int y) {
    if (n == 0) return 0;
    if (x > y) std::swap(x, y);

    long long l = -1;
    long long r = (long long)n * y;

    while (l < r - 1) {
        long long mid = l + (r - l) / 2;
        long long copies = mid / x + mid / y;

        if (copies < n - 1) {
            l = mid;
        } else {
            r = mid;
        }
    }

    return r + x;
}

int feedAnimals(std::vector<int>& needs, std::vector<int>& foods) {
    if (needs.empty() || foods.empty()) {
        return 0;
    }

    sort(needs.begin(), needs.end());
    sort(foods.begin(), foods.end());

    int count = 0;
    int i = 0;  // потребность
    int j = 0;  // еда

    while (i < needs.size() && j < foods.size()) {
        if (foods[j] >= needs[i]) {
            count++;
            i++; 
            j++;  
        } else {
            j++;
        }
    }

    return count;
}

std::string extraLetter(const std::string& a, const std::string& b) {
    std::unordered_map<char, int> charCount;

    for (char c : b) {
        charCount[c]++;
    }

    for (char c : a) {
        charCount[c]--;
    }

    for (const auto& pair : charCount) {
        if (pair.second > 0) {
            return std::string(1, pair.first);
        }
    }

    return "";
}

std::vector<int> twoSum(const std::vector<int>& data, int target) {
    std::unordered_map<int, int> cache; 

    for (int i = 0; i < data.size(); i++) {
        int diff = target - data[i];

        if (cache.find(diff) != cache.end()) {
            return {cache[diff], i};
        }
        cache[data[i]] = i;
    }
    return {};
}

std::vector<int> shell_sort(std::vector<int> arr) {
    int n = arr.size();
    int gap = n / 2;

    while (gap > 0) {
        for (int current_position = gap; current_position < n; current_position++) {
            int m_gap = current_position;

            while (m_gap >= gap && arr[m_gap] < arr[m_gap - gap]) {
                std::swap(arr[m_gap], arr[m_gap - gap]);
                m_gap -= gap;
            }
        }
        gap = gap / 2; 
    }

    return arr;
}

std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    std::unordered_map<std::string, std::vector<std::string>> anagramGroups;
    
    for (const std::string& str : strs) {
        std::string sortedStr = str;
        std::sort(sortedStr.begin(), sortedStr.end());
        anagramGroups[sortedStr].push_back(str);
    }
    
    std::vector<std::vector<std::string>> result;
    for (auto& group : anagramGroups) {
        result.push_back(group.second);
    }
    
    return result;
}

int main() {
    int number = 2000;
    int result = binarySearchSqrt(number);
    std::cout << result << std::endl;

    std::cout << copyTime(5, 1, 2) << std::endl;

    std::vector<int> needs1 = {8, 1};
    std::vector<int> foods1 = {1, 8};
    std::cout << feedAnimals(needs1, foods1) << std::endl; 

    std::vector<int> needs2 = {8, 2, 3, 2};
    std::vector<int> foods2 = {1, 4, 3, 8};
    std::cout << feedAnimals(needs2, foods2) << std::endl;
    std::cout << "Альтернативное решение:" << std::endl;
    std::cout << "Добавленная буква: '" << extraLetter("abc", "cab") << "'" << std::endl;
    std::cout << "Добавленная буква: '" << extraLetter("aab", "aaab") << "'" << std::endl;

    std::vector<int> test4 = {1, 2, 3, 4};
    int target4 = 8;
    std::vector<int> result4 = twoSum(test4, target4);
    std::cout << "Результат: ";
    if (result4.empty()) {
        std::cout << "Пара не найдена";
    } else {
        for (int idx : result4) {
            std::cout << idx << " ";
        }
    }
    std::cout << std::endl;

    std::vector<int> arr = {12, 34, 54, 2, 3, 1, 8, 23, 5, 21};
    std::cout << "Исходный массив: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::vector<int> sorted = shell_sort(arr);
    std::cout << "Отсортированный массив: ";
    for (int num : sorted) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    
    std::vector<std::string> strs2 = {"won", "now", "aaa", "ooo", "ooo", "eat", "tea", "tan", "ate", "nat", "bat"};
    std::vector<std::vector<std::string>> result2 = groupAnagrams(strs2);
    
    std::cout << "\nТест 2:" << std::endl;
    for (const auto& group : result2) {
        std::cout << "[";
        for (int i = 0; i < group.size(); i++) {
            std::cout << "\"" << group[i] << "\"";
            if (i < group.size() - 1) std::cout << ",";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}