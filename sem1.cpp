#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T> // шаблолнный чтобы класс не зависил от тирпа данных
class MyVector {
 private:
  T* data;           // Указатель на массив элементов
  size_t size_;      // Текущее количество элементов
  size_t capacity_;  // Текущая ёмкость массива

  // Увеличивает ёмкость массива, вызывается в других методах при необходимости
  void reallocate(size_t new_capacity) {
    T* new_data = new T[new_capacity];

    // Копируем существующие элементы
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = std::move(data[i]);
    }

    delete[] data;
    data = new_data;
    capacity_ = new_capacity;
  }

 public:
  // Конструкторы

  // по умолчанию
  MyVector() : data(nullptr), size_(0), capacity_(0) {}

  // заполнить данными по умолчанию указанного типа данных
  explicit MyVector(size_t n) : data(new T[n]), size_(n), capacity_(n) {
    for (size_t i = 0; i < n; ++i) {
      data[i] = T();
    }
  }
  // заполнить одним и тем же значением
  MyVector(size_t n, const T& value) : data(new T[n]), size_(n), capacity_(n) {
    for (size_t i = 0; i < n; ++i) {
      data[i] = value;
    }
  }

  //Позволяет инициализировать массив списком значений в фигурных скобках.
  MyVector(std::initializer_list<T> init)
      : data(new T[init.size()]),
        size_(init.size()),
        capacity_(init.size()) {
    size_t i = 0;
    for (const T& value : init) {
      data[i++] = value;
    }
  }

  // Конструктор копирования
  MyVector(const MyVector& other)
      : data(new T[other.capacity_]),
        size_(other.size_),
        capacity_(other.capacity_) {
    for (size_t i = 0; i < size_; ++i) {
      data[i] = other.data[i];
    }
  }

  // Конструктор перемещения
  MyVector(MyVector&& other) noexcept
      : data(other.data),
        size_(other.size_),
        capacity_(other.capacity_) {
    other.data = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  // Оператор присваивания копированием
  MyVector& operator=(const MyVector& other) {
    if (this != &other) {
      delete[] data;

      size_ = other.size_;
      capacity_ = other.capacity_;
      data = new T[capacity_];

      for (size_t i = 0; i < size_; ++i) {
        data[i] = other.data[i];
      }
    }
    return *this;
  }

  // Оператор присваивания перемещением
  MyVector& operator=(MyVector&& other) noexcept {
    if (this != &other) {
      delete[] data;

      data = other.data;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.data = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    return *this;
  }

  // Оператор присваивания с initializer_list
  MyVector& operator=(std::initializer_list<T> init) {
    // Удаляем старые данные
    delete[] data;

    // Создаем новые
    size_ = init.size();
    capacity_ = init.size();
    data = new T[capacity_];

    // Копируем элементы
    size_t i = 0;
    for (const T& value : init) {
      data[i++] = value;
    }

    return *this;
  }

  // Деструктор
  ~MyVector() {
    delete[] data;
  }

  // Доступ к элементам (не проверяет выход за пределы массива, используется если есть уверреность в указателе)
  T& operator[](size_t index) {
    return data[index];
  }

  const T& operator[](size_t index) const {
    return data[index];
  }

  // доступ к элементам (проверяет выхоод за пределы массива)
  T& at(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data[index];
  }

  const T& at(size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data[index];
  }

  T& front() {
    return data[0];
  }

  const T& front() const {
    return data[0];
  }

  T& back() {
    return data[size_ - 1];
  }

  const T& back() const {
    return data[size_ - 1];
  }

  T* get_data() {
    return data;
  }

  const T* get_data() const {
    return data;
  }

  // Итераторы (простая реализация)
  T* begin() {
    return data;
  }

  const T* begin() const {
    return data;
  }

  T* end() {
    return data + size_;
  }

  const T* end() const {
    return data + size_;
  }

  // Проверяет пусто в массиве или нет (возвращает true или false)
  bool empty() const {
    return size_ == 0;
  }

  size_t size() const {
    return size_;
  }

  size_t capacity() const {
    return capacity_;
  }

  void reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
      reallocate(new_capacity);
    }
  }

  void shrink_to_fit() {
    if (size_ < capacity_) {
      reallocate(size_);
    }
  }

  // Модификаторы
  void clear() {
    size_ = 0;
  }

  // реаллокация памяти, работает за O(n)
  void push_back(const T& value) {
    if (size_ >= capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data[size_++] = value;
  }

  void push_back(T&& value) {
    if (size_ >= capacity_) {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data[size_++] = std::move(value);
  }

  void pop_back() {
    if (size_ > 0) {
      --size_;
    }
  }

  void resize(size_t new_size) {
    if (new_size > capacity_) {
      reserve(new_size);
    }
    size_ = new_size;
  }

  void resize(size_t new_size, const T& value) {
    if (new_size > capacity_) {
      reserve(new_size);
    }

    if (new_size > size_) {
      for (size_t i = size_; i < new_size; ++i) {
        data[i] = value;
      }
    }
    size_ = new_size;
  }

  // выводит в стандартный поток элементы массива

  void show() {
    for (size_t i = 0; i < size_; ++i) {
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
  }

  // меняет элементы масссива по указанным индексам
  void swap(size_t i, size_t j) {
    if (i >= size_ || j >= size_) {
      throw std::out_of_range("Index out of range in swap operation");
    }

    if (i != j) {
      T temp = std::move(data[i]);
      data[i] = std::move(data[j]);
      data[j] = std::move(temp);
    }
  }
};

// первое задание на поиск заданного числа как сумма двух элементов отсортированного массива
MyVector<int> twoSum(MyVector<int>& ref, int target) {
  int left = 0;
  int right = ref.size() - 1;
  int sum = 0;

  while (left < right) {
    sum = ref[left] + ref[right];

    if (sum == target) {
      MyVector<int> result(2);
      result[0] = left;
      result[1] = right;
      return result;
    } else if (sum < target) {
      ++left;
    } else {
      --right;
    }
  }

  MyVector<int> result(2, -1);  // Возвращаем [-1, -1] если пара не найдена
  return result;
}

// переворот массива
void reverseArray(MyVector<int>& ref) {
  int left = 0;
  int right = ref.size() - 1;
  while (left < right) {
    ref.swap(left, right);
    left++;
    right--;
  }
}

// переворото части массива
void reverseArray(MyVector<int>& ref, size_t left, size_t right) {
  while (left < right) {
    ref.swap(left, right);
    left++;
    right--;
  }
}

// второе задание переврнуть часть массива
void smartReverseArray(MyVector<int>& ref, int k) {
  int n = ref.size();
  reverseArray(ref, 0, n - 1);
  reverseArray(ref, k % n, n - 1);
  reverseArray(ref, 0, k % n - 1);
}

// третье задание на слияние двух отсортированных массивов
MyVector<int> mergeSortArrays(MyVector<int>& ref1, MyVector<int>& ref2) {
  MyVector<int> result;
  int i = 0, j = 0;
  while (i < ref1.size() && j < ref2.size()) {
    if (ref1[i] < ref2[j]) {
      result.push_back(ref1[i]);
      i++;
    } else {
      result.push_back(ref2[j]);
      j++;
    }
  }

  for (int k = i; k < ref1.size(); k++) {
    result.push_back(ref1[k]);
  }
  for (int k = j; k < ref2.size(); k++) {
    result.push_back(ref2[k]);
  }
  return result;
}

// четвертое задание на слияние двух массивов когда в первом есть место в конце для второго
void mergeSortArraysZeros(MyVector<int>& ref1, MyVector<int>& ref2) {
  int i = ref1.size() - ref2.size() - 1;
  int j = ref2.size() - 1;
  int k = ref1.size() - 1;

  while (j >= 0) {
    if (i >= 0 && ref1[i] > ref2[j]) {
      ref1[k] = ref1[i];
      i--;
    } else {
      ref1[k] = ref2[j];
      j--;
    }
    k--;
  }
}

// пятое задание отсортировать массив из нулей и единиц
void sortZerosArray(MyVector<int>& ref) {
  int left = 0;
  int right = ref.size() - 1;
  while (left < right) {
    if (ref[right] == 0) {
      ref.swap(left, right);
      left++;
    } else {
      right--;
    }
  }
}

// шестое задание отсортировать массив из нулей, единиц и двоек (задача флага нидерландов)
void flagSort(MyVector<int>& ref) {
  int left = 0;
  int mid = 0;
  int right = ref.size() - 1;
  while (mid <= right) {
    if (ref[mid] == 0) {
      ref.swap(left, mid);
      left++;
      mid++;
    } else if (ref[mid] == 1) {
      mid++;
    } else if (ref[mid] == 2) {
      ref.swap(mid, right);
      right--;
    }
  }
}

// седьмое задание передвинуть четные числа вперед
void evenNumbersForward(MyVector<int>& ref) {
  size_t evenindex = 0;
  for (size_t i = 0; i < ref.size(); i++) {
    if (ref[i] % 2 == 0) {
      ref.swap(i, evenindex);
      evenindex++;
    }
  }
}

// седьмое задание передвинуть нули в конец (типо нулевые оценки)
void zerosToEnd(MyVector<int>& ref) {
  int left = 0;
  int right = ref.size() - 1;
  while (left < right) {
    if (ref[left] == 0) {
      ref.swap(left, right);
      --right;
    } else {
      ++left;
    }
  }
}

int main() {
  // в написанных функциях домашней работы почти всегда векторы передаются по ссылке. (Исключение - первое задание)
  MyVector<int> vec1;
  MyVector<int> vec2;
  MyVector<int> vec3;
  MyVector<int> result;
  // Добавление элементов
  for (int i = 1; i < 8; ++i) {
    vec1.push_back(i);
  }

  for (int i = 0; i <= 20; ++i) {
    if (i % 2 == 0) {
      vec2.push_back(i);
    } else {
      vec3.push_back(i);
    }
  }

  MyVector<int> vec4 = {3, 8, 9, 11, 16, 18, 19, 21, 0, 0, 0, 0};
  MyVector<int> vec5 = {1, 2, 8, 15};
  MyVector<int> zeros = {0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0};
  MyVector<int> niderlands = {2, 0, 2, 1, 0, 0, 2, 1, 0, 1, 0, 2, 0, 1, 0, 0};
  MyVector<int> numbers = {3, 6, 2, 9, 4, 7, 1, 20, 34};

  result = twoSum(vec1, 30);
  result.show();

  // vec1.show();

  // reverseArray(vec1, 0, vec1.size() - 1);
  // vec1.show();

  // smartReverseArray(vec1, 24);
  // vec1.show();

  // result = mergeSortArrays(vec2, vec3);
  // result.show();

  // mergeSortArraysZeros(vec4, vec5);
  // vec4.show();

  // sortZerosArray(zeros);
  // zeros.show();

  // flagSort(niderlands);
  // niderlands.show();

  // evenNumbersForward(numbers);
  // numbers.show();

  zerosToEnd(niderlands);
  niderlands.show();

  return 0;
}