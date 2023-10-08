#ifndef SRC_S21_CONTAINERS_STACK_H_
#define SRC_S21_CONTAINERS_STACK_H_

#include "s21_helpsrc.h"
#include "s21_list.h"

namespace s21 {
template <class T, class Container = s21::List<T>>
class Stack {
 public:
  //  Stack Member type (type redefinition)
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 protected:
  Container ListBased;

 public:
  //  Stack Member functions
  Stack() : ListBased() {}
  Stack(std::initializer_list<value_type> const& items) : ListBased(items) {}
  Stack(const Stack& s) : ListBased(s.ListBased) {}
  Stack(Stack&& s) : ListBased(std::move(s.ListBased)) {}
  ~Stack() {}
  Stack& operator=(const Stack& s) {
    ListBased = s.ListBased;
    return *this;
  }
  Stack& operator=(Stack&& s) noexcept {
    ListBased = std::move(s.ListBased);
    return *this;
  }
  // Stack Element access
  const_reference top() { return ListBased.back(); }
  // Stack Capacity
  bool empty() { return ListBased.empty(); }
  size_type size() { return ListBased.size(); }
  // Stack Modifiers
  void push(const_reference value) { this->ListBased.push_back(value); }
  void pop() { this->ListBased.pop_back(); }
  void Swap(Stack& other) { this->ListBased.Swap(other.ListBased); }
  // appends new elements to the top of the container
  template <class... Args>
  decltype(auto) insert_many_front(Args&&... args) {
    ListBased.insert_many_back(std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif  // SRC_S21_CONTAINERS_STACK_H_
