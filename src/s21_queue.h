#ifndef SRC_S21_CONTAINERS_QUEUE_H_
#define SRC_S21_CONTAINERS_QUEUE_H_

#include "s21_helpsrc.h"
#include "s21_list.h"

namespace s21 {
template <class T, class Container = s21::List<T>>
class Queue {
 public:
  //  Queue Member type (type redefinition)
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 protected:
  Container ListBased;

 public:
  //  Queue Member functions
  Queue() : ListBased() {}
  Queue(std::initializer_list<value_type> const& items) : ListBased(items) {}
  Queue(const Queue& q) : ListBased(q.ListBased) {}
  Queue(Queue&& q) : ListBased(std::move(q.ListBased)) {}
  ~Queue() {}

  Queue& operator=(const Queue& q) {
    ListBased = q.ListBased;
    return *this;
  }
  Queue& operator=(Queue&& q) noexcept {
    ListBased = std::move(q.ListBased);
    return *this;
  }
  // Queue Element access
  const_reference front() { return ListBased.front(); }
  const_reference back() { return ListBased.back(); }
  // Queue Capacity
  bool empty() { return ListBased.empty(); }
  size_type size() { return ListBased.size(); }
  // Queue Modifiers
  void push(const_reference value) { this->ListBased.push_back(value); }
  void pop() { this->ListBased.pop_front(); }
  void Swap(Queue& other) { this->ListBased.Swap(other.ListBased); }
  template <class... Args>
  decltype(auto) insert_many_back(Args&&... args) {
    return ListBased.insert_many_back(std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif  // SRC_S21_CONTAINERS_QUEUE_H_
