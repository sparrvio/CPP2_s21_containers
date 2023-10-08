#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_
#include "s21_helpsrc.h"
namespace s21 {
template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  Vector();  // default constructor, creates empty vector
  Vector(
      size_type n);  // parameterized constructor, creates the vector of size n
  Vector(std::initializer_list<value_type> const&
             items);            // initializer list constructor, creates vector
                                // initizialized using std::initializer_list
  Vector(const Vector& v);      // copy constructor
  Vector(Vector&& v) noexcept;  // move constructor
  Vector& operator=(
      Vector&& v) noexcept;  // assignment operator overload for moving object
  ~Vector();                 // destructor

  reference at(size_type pos);  // access specified element with bounds checking
  reference operator[](size_type pos);  // access specified element
  const_reference front();              // access the first element
  const_reference back();               // access the last element
  iterator data();                      // direct access to the underlying array

  iterator begin();  // returns an iterator to the beginning
  iterator end();    // returns an iterator to the end

  void resize(size_type new_size);  // change size
  bool empty();                     // checks whether the container is empty
  size_type size();                 // returns the number of elements
  size_type max_size();  // returns the maximum possible number of elements
  void reserve(size_type new_capacity);  // allocate storage of size elements
                                         // and copies current array elements to
                                         // a newely allocated array
  size_type capacity();  // returns the number of elements that can be held in
                         // currently allocated storage
  void shrink_to_fit();  // reduces memory usage by freeing unused memory

  void clear();  // clears the contents
  iterator insert(
      iterator pos,
      const_reference value);  // inserts elements into concrete pos and returns
                               // the iterator that points to the new element
  void erase(iterator pos);    // erases element at pos
  void push_back(const_reference value);  // adds an element to the end
  void pop_back();                        // removes the last element
  void swap(Vector& other);               // swaps the contents

  template <typename... Args>
  iterator insert_many(const_iterator pos,
                       Args&&... args);  // inserts new elements into the
                                         // container directly before pos
  template <typename... Args>
  void insert_many_back(
      Args&&... args);  // appends new elements to the end of the container

 private:
  T* arr_;
  size_t capacity_;
  size_t size_;
};
//--------------------------------------------------------------------
// Implementation
//--------------------------------------------------------------------
template <typename value_type>
Vector<value_type>::Vector() {
  arr_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename value_type>
Vector<value_type>::Vector(size_type value) {
  if (value > max_size()) throw std::bad_alloc();
  size_ = value;
  capacity_ = value;
  arr_ = reinterpret_cast<value_type*>(new int8_t[value * sizeof(value_type)]);
  ;
  for (size_t i = 0; i < value; i++) {
    arr_[i] = value_type();
  }
}

template <typename value_type>
Vector<value_type>::Vector(std::initializer_list<value_type> const& items) {
  if (items.size() > max_size()) throw std::bad_alloc();
  size_ = items.size();
  capacity_ = items.size();
  arr_ =
      reinterpret_cast<value_type*>(new int8_t[capacity_ * sizeof(value_type)]);
  std::uninitialized_copy(items.begin(), items.end(), arr_);
}

template <typename value_type>
Vector<value_type>::Vector(const Vector& v) {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  arr_ =
      reinterpret_cast<value_type*>(new int8_t[capacity_ * sizeof(value_type)]);
  try {
    std::uninitialized_copy(v.arr_, v.arr_ + v.size_, arr_);
  } catch (...) {
    delete[] reinterpret_cast<int8_t*>(arr_);
    throw std::bad_alloc();
  }
}

template <typename value_type>
Vector<value_type>::Vector(Vector&& v) noexcept {
  this->size_ = v.size_;
  this->capacity_ = v.capacity_;
  this->arr_ = v.arr_;
  v.size_ = 0;
  v.capacity_ = 0;
  v.arr_ = nullptr;
}

template <typename value_type>
Vector<value_type>::~Vector() {
  clear();
  size_ = 0;
  capacity_ = 0;
  delete[] reinterpret_cast<int8_t*>(arr_);
  arr_ = nullptr;
}

template <typename value_type>
Vector<value_type>& Vector<value_type>::operator=(Vector&& v) noexcept {
  if (this != &v) {
    this->clear();
    this->arr_ = v.arr_;
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    v.arr_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <typename value_type>
value_type& Vector<value_type>::at(size_type pos) {
  if (pos < size_) {
    return arr_[pos];
  } else {
    throw std::out_of_range("Index out of range");
  }
}

template <typename value_type>
value_type& Vector<value_type>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename value_type>
const value_type& Vector<value_type>::front() {
  if (this->empty()) throw std::out_of_range("Index out of range");
  return arr_[0];
}

template <typename value_type>
const value_type& Vector<value_type>::back() {
  if (this->empty()) throw std::out_of_range("Index out of range");
  return arr_[size_ - 1];
}

template <typename value_type>
value_type* Vector<value_type>::data() {
  return arr_;
}

template <typename value_type>
inline value_type* Vector<value_type>::begin() {
  return iterator(arr_);
}

template <typename value_type>
inline value_type* Vector<value_type>::end() {
  return iterator(arr_ + size_);
}

template <typename value_type>
size_t Vector<value_type>::size() {
  return this->size_;
}

template <typename value_type>
size_t Vector<value_type>::max_size() {
  return SIZE_MAX / sizeof(value_type);
}

template <typename value_type>
size_t Vector<value_type>::capacity() {
  return this->capacity_;
}

template <typename value_type>
void Vector<value_type>::shrink_to_fit() {
  if (capacity_ == size_) return;
  value_type* new_arr =
      reinterpret_cast<value_type*>(new int8_t[size_ * sizeof(value_type)]);
  try {
    std::uninitialized_copy(arr_, arr_ + size_, new_arr);
  } catch (...) {
    delete[] reinterpret_cast<int8_t*>(new_arr);
    throw;
  }
  for (size_t i = 0; i < size_; ++i) {
    (arr_ + i)->~value_type();
  }
  delete[] reinterpret_cast<int8_t*>(arr_);
  arr_ = new_arr;
  capacity_ = size_;
}

template <typename value_type>
void Vector<value_type>::reserve(size_type new_capacity) {
  if (new_capacity <= capacity_) return;
  if (new_capacity > max_size()) throw std::bad_alloc();
  value_type* new_arr = reinterpret_cast<value_type*>(
      new int8_t[new_capacity * sizeof(value_type)]);
  try {
    std::uninitialized_copy(arr_, arr_ + size_, new_arr);
  } catch (...) {
    delete[] reinterpret_cast<int8_t*>(new_arr);
    throw std::bad_alloc();
  }

  if (arr_ != nullptr) {
    for (size_t i = 0; i < size_; ++i) {
      if ((arr_ + i) != nullptr) {
        (arr_ + i)->~value_type();
      }
    }
    delete[] reinterpret_cast<int8_t*>(arr_);
  }
  arr_ = new_arr;
  capacity_ = new_capacity;
}

template <typename value_type>
void Vector<value_type>::resize(size_type new_size) {
  if (new_size > capacity_) reserve(new_size);
  for (size_t i = size_; i < new_size; ++i) {
    new (arr_ + i) value_type();
  }
  size_ = new_size;
}

template <typename value_type>
bool Vector<value_type>::empty() {
  return (size_ == 0 ? true : false);
}

template <typename value_type>
void Vector<value_type>::clear() {
  for (size_t i = 0; i < size_; ++i) {
    (arr_ + i)->~value_type();
  }
  size_ = 0;
}

template <typename value_type>
typename Vector<value_type>::iterator Vector<value_type>::insert(
    iterator pos, const_reference value) {
  if (size_ == 0) {
    push_back(value);
    return begin();
  }

  if (pos < this->begin() || pos > this->end()) {
    throw std::out_of_range("position is out of range");
  }

  size_t index = pos - this->begin();
  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }

  resize(size_ + 1);
  std::move_backward(this->begin() + index, this->end() - 1, this->end());
  iterator result = this->begin() + index;
  arr_[index] = value;
  return result;
}

template <typename value_type>
void Vector<value_type>::erase(iterator pos) {
  for (iterator i = pos; i != end() - 1; ++i) {
    *(i) = *(i + 1);
  }
  --size_;
}

template <typename value_type>
void Vector<value_type>::push_back(const_reference value) {
  if (capacity_ == size_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  try {
    new (arr_ + size_) value_type(value);
  } catch (...) {
    (arr_ + size_)->~value_type();
    throw;
  }
  size_++;
}

template <typename value_type>
void Vector<value_type>::pop_back() {
  --size_;
  (arr_ + size_)->~value_type();
}

template <typename value_type>
void Vector<value_type>::swap(Vector<value_type>& other) {
  s21::Vector<value_type> tmp;
  tmp.arr_ = this->arr_;
  tmp.size_ = this->size_;
  tmp.capacity_ = this->capacity_;
  this->arr_ = other.arr_;
  this->size_ = other.size_;
  this->capacity_ = other.capacity_;
  other.arr_ = tmp.arr_;
  other.size_ = tmp.size_;
  other.capacity_ = tmp.capacity_;
  tmp.arr_ = nullptr;
  tmp.size_ = 0;
  tmp.capacity_ = 0;
}

template <typename value_type>
template <typename... Args>
typename Vector<value_type>::iterator Vector<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  iterator it = const_cast<iterator>(pos);
  for (auto value : {std::forward<Args>(args)...}) {
    it = insert(it, value);
    it++;
  }
  return --it;
}

template <typename value_type>
template <typename... Args>
void Vector<value_type>::insert_many_back(Args&&... args) {
  for (auto value : {std::forward<Args>(args)...}) {
    push_back(value);
  }
}
}  // namespace s21
#endif  // SRC_S21_VECTOR_H_