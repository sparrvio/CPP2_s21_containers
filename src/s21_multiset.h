#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_
#include "s21_helpsrc.h"
#include "s21_vector.h"

namespace s21 {
template <typename T>
class Multiset {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  struct Node {
    value_type value;
    Node *parent;
    Node *left;
    Node *right;

    Node(const value_type &value)
        : value(value), parent(nullptr), left(nullptr), right(nullptr) {}
    ~Node() = default;
  };

  class MultisetIterator {
   public:
    using iterator = MultisetIterator;
    using value_type = T;
    using reference = const T &;
    using pointer = const T *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    // explicit MultisetIterator(Node *node, const Multiset<T> *multiset) :
    // m_node_(node), m_multiset(multiset) {} MultisetIterator(Node* node, const
    // Multiset<T>* multiset = nullptr) : m_node_(node), m_multiset(multiset) {}
    // MultisetIterator(Node* node) : m_node__(node)
    MultisetIterator(Node *node = nullptr,
                     const Multiset<T> *multiset = nullptr)
        : m_node_(node), m_multiset(multiset){};
    ~MultisetIterator() = default;

    MultisetIterator &operator++() {
      m_node_ = get_successor(m_node_);
      return *this;
    }

    MultisetIterator operator++(int) {
      MultisetIterator temp(*this);
      ++(*this);
      return temp;
    }

    MultisetIterator &operator--() {
      if (m_node_ == nullptr) {
        m_node_ = get_maximum(m_multiset->m_root_);
      } else {
        m_node_ = get_predecessor(m_node_);
      }
      return *this;
    }

    MultisetIterator operator--(int) {
      MultisetIterator temp(*this);
      --(*this);
      return temp;
    }

    bool operator==(const MultisetIterator &other) const {
      return m_node_ == other.m_node_;
    }

    bool operator!=(const MultisetIterator &other) const {
      return !(*this == other);
    }

    reference operator*() const { return m_node_->value; }

    pointer operator->() const { return &m_node_->value; }

   private:
    Node *m_node_;
    const Multiset<value_type> *m_multiset;

    Node *multiset_minimum(Node *node) const {
      if (node == nullptr) {
        return nullptr;
      }
      if (node->left == nullptr) {
        return node;
      }
      return multiset_minimum(node->left);
    }

    Node *get_successor(Node *node) const {
      if (node == nullptr) {
        return nullptr;
      }
      if (node->right != nullptr) {
        return multiset_minimum(node->right);
      }
      Node *parent = node->parent;
      while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }

    Node *get_predecessor(Node *node) const {
      if (node == nullptr) {
        return multiset_maximum(m_multiset->m_root_);
      }
      if (node->left != nullptr) {
        return multiset_maximum(node->left);
      }
      Node *parent = node->parent;
      while (parent != nullptr && node == parent->left) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  };

  class ConstMultisetIterator {
   public:
    using value_type = T;
    using reference = const T &;
    using pointer = const T *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    explicit ConstMultisetIterator(
        const typename Multiset<value_type>::Node *node,
        const Multiset<value_type> *multiset)
        : m_node_(node), m_multiset(multiset) {}

    ConstMultisetIterator &operator++() {
      m_node_ = get_successor(m_node_);
      return *this;
    }

    ConstMultisetIterator operator++(int) {
      ConstMultisetIterator temp(*this);
      ++(*this);
      return temp;
    }

    ConstMultisetIterator &operator--() {
      if (m_node_ == nullptr) {
        m_node_ = get_maximum(m_multiset->m_root_);
      } else {
        m_node_ = get_predecessor(m_node_);
      }
      return *this;
    }

    ConstMultisetIterator operator--(int) {
      ConstMultisetIterator temp(*this);
      --(*this);
      return temp;
    }

    bool operator==(const ConstMultisetIterator &other) const {
      return m_node_ == other.m_node_;
    }

    bool operator!=(const ConstMultisetIterator &other) const {
      return !(*this == other);
    }

    reference operator*() { return m_node_->value; }

    pointer operator->() { return &m_node_->value; }

   private:
    const typename Multiset<value_type>::Node *m_node_;
    const Multiset<value_type> *m_multiset;

    Node *multiset_minimum(Node *node) const {
      if (node == nullptr) {
        return nullptr;
      }
      if (node->left == nullptr) {
        return node;
      }
      return multiset_minimum(node->left);
    }

    const typename Multiset<value_type>::Node *get_successor(
        const typename Multiset<value_type>::Node *node) const {
      if (node == nullptr) {
        return nullptr;
      }
      if (node->right != nullptr) {
        return multiset_minimum(node->right);
      }
      const typename Multiset<value_type>::Node *parent = node->parent;
      while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }

    const typename Multiset<value_type>::Node *get_predecessor(
        const typename Multiset<value_type>::Node *node) const {
      if (node == nullptr) {
        return nullptr;
      }
      if (node->left != nullptr) {
        return multiset_maximum(node->left);
      }
      const typename Multiset<T>::Node *parent = node->parent;
      while (parent != nullptr && node == parent->left) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  };

  using iterator = MultisetIterator;
  using const_iterator = ConstMultisetIterator;

  Multiset();  // default constructor, creates empty set
  Multiset(std::initializer_list<value_type> const
               &items);          // initializer list constructor
  Multiset(const Multiset &ms);  // copy constructor
  Multiset(Multiset &&ms);       // move constructor
  ~Multiset();                   // destructor

  Multiset<value_type> &operator=(
      Multiset<value_type>
          &&ms) noexcept;  // assignment operator overload for moving object

  // Итераторы
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty();          // checks whether the container is empty
  size_type size();      // returns the number of elements
  size_type max_size();  // returns the maximum possible number of elements

  // Модификаторы
  iterator insert(const value_type &value);
  void clear();
  void swap(Multiset &other);

  void erase(iterator pos);     // erases element at pos
  void merge(Multiset &other);  // splices nodes from another container

  size_type count(const key_type &key);  // returns the number of elements
                                         // matching specific key
  iterator find(const key_type &key);    // finds element with specific key

  bool contains(const key_type &key);  // checks if the container contains
                                       // element with specific key
  std::pair<iterator, iterator> equal_range(
      const key_type
          &key);  // returns range of elements matching a specific key
  iterator lower_bound(
      const key_type &key);  // returns an iterator to the first element not
                             // less than the given key
  iterator upper_bound(
      const key_type &key);  // returns an iterator to the first
                             // element greater than the given key

  template <typename... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  void print() const;

 private:
  Node *m_root_;
  size_type m_size_;
  Node *get_minimum(Node *node) const;
  void erase(iterator it, Node *node);
  void delete_subtree(Node *node);
  std::pair<iterator, bool> insert_emplace(const key_type &key);
  void print_tree(Node *node) const;
};

//--------------------------------------------------------------------
// Implementation
//--------------------------------------------------------------------

template <typename value_type>
Multiset<value_type>::Multiset() : m_root_(nullptr), m_size_(0) {}

template <typename value_type>
Multiset<value_type>::Multiset(std::initializer_list<value_type> const &items)
    : Multiset() {
  if (items.size() > max_size()) throw std::bad_alloc();
  for (const auto &item : items) {
    insert(item);
  }
}

template <typename value_type>
Multiset<value_type>::Multiset(const Multiset &ms) : Multiset() {
  for (const auto &item : ms) {
    insert(item);
  }
}

template <typename value_type>
Multiset<value_type>::Multiset(Multiset &&ms) : Multiset() {
  swap(ms);
}

template <typename value_type>
Multiset<value_type>::~Multiset() {
  delete_subtree(m_root_);
}

template <typename value_type>
Multiset<value_type> &Multiset<value_type>::operator=(
    Multiset<value_type> &&ms) noexcept {
  if (this != &ms) {
    clear();
    swap(ms);
  }
  return *this;
}

template <typename value_type>
typename Multiset<value_type>::iterator Multiset<value_type>::begin() {
  return iterator(get_minimum(m_root_), this);
}

template <typename value_type>
typename Multiset<value_type>::const_iterator Multiset<value_type>::begin()
    const {
  return const_iterator(get_minimum(m_root_), this);
}

template <typename value_type>
typename Multiset<value_type>::iterator Multiset<value_type>::end() {
  return iterator(nullptr, this);
}

template <typename value_type>
typename Multiset<value_type>::const_iterator Multiset<value_type>::end()
    const {
  return const_iterator(nullptr, this);
}

template <typename value_type>
bool Multiset<value_type>::empty() {
  return (m_size_ == 0);
}

template <typename value_type>
size_t Multiset<value_type>::size() {
  return m_size_;
}

template <typename value_type>
size_t Multiset<value_type>::max_size() {
  return SIZE_MAX / sizeof(value_type);
}

template <typename value_type>
typename Multiset<value_type>::iterator Multiset<value_type>::insert(
    const value_type &value) {
  Node *node = m_root_;
  Node *parent = nullptr;
  while (node != nullptr) {
    parent = node;
    if (value <= node->value) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  Node *new_node = new Node(value);
  new_node->parent = parent;
  if (parent == nullptr) {
    m_root_ = new_node;
  } else if (value <= parent->value) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }
  ++m_size_;
  return iterator(new_node, this);
}

template <typename value_type>
void Multiset<value_type>::clear() {
  delete_subtree(m_root_);
  m_root_ = nullptr;
  m_size_ = 0;
}

template <typename value_type>
void Multiset<value_type>::swap(Multiset &other) {
  Node *tmp_root = m_root_;
  size_t tmp_size = m_size_;
  this->m_root_ = other.m_root_;
  other.m_root_ = tmp_root;
  this->m_size_ = other.m_size_;
  other.m_size_ = tmp_size;
}

template <typename value_type>
void s21::Multiset<value_type>::erase(iterator it) {
  erase(it, m_root_);
}

template <typename value_type>
void s21::Multiset<value_type>::merge(Multiset &other) {
  if (this->m_root_ == other.m_root_) return;
  auto it = other.begin();
  for (size_t i = 0; i < other.m_size_; ++i) {
    this->insert(*it);
    ++it;
  }
  other.clear();
}

template <typename key_type>
size_t Multiset<key_type>::count(const key_type &key) {
  size_type count = 0;
  Node *node = m_root_;
  while (node) {
    if (key < node->value) {
      node = node->left;
    } else if (node->value < key) {
      node = node->right;
    } else {
      ++count;
      node = node->left;
    }
  }
  return count;
}

template <typename key_type>
typename Multiset<key_type>::iterator Multiset<key_type>::find(
    const key_type &key) {
  Node *current = m_root_;
  while (current != nullptr) {
    if (key < current->value) {
      current = current->left;
    } else if (key > current->value) {
      current = current->right;
    } else {
      return iterator(current, nullptr);
    }
  }
  return end();
}

template <typename key_type>
bool Multiset<key_type>::contains(const key_type &key) {
  return (find(key) != end());
}

template <typename key_type>
std::pair<typename Multiset<key_type>::iterator,
          typename Multiset<key_type>::iterator>
Multiset<key_type>::equal_range(const key_type &key) {
  return {this->lower_bound(key), this->upper_bound(key)};
}

template <typename key_type>
typename Multiset<key_type>::iterator Multiset<key_type>::lower_bound(
    const key_type &key) {
  auto it = begin();
  while (it != end() && (*it < key)) {
    ++it;
  }
  return it;
}

template <typename key_type>
typename Multiset<key_type>::iterator Multiset<key_type>::upper_bound(
    const key_type &key) {
  auto it = begin();
  while (it != end() && !(key < *it)) {
    ++it;
  }
  return it;
}

template <typename key_type>
template <typename... Args>
Vector<std::pair<typename Multiset<key_type>::iterator, bool>>
Multiset<key_type>::insert_many(Args &&...args) {
  Vector<std::pair<iterator, bool>> result = {
      (insert_emplace(std::forward<Args>(args)))...};
  return result;
}
//--------------------------------------------------------------------
// Implementation private
//--------------------------------------------------------------------

template <typename value_type>
typename Multiset<value_type>::Node *Multiset<value_type>::get_minimum(
    Node *node) const {
  while (node != nullptr && node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename value_type>
void Multiset<value_type>::delete_subtree(Node *node) {
  if (node != nullptr) {
    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
  }
}

template <typename value_type>
void Multiset<value_type>::erase(iterator it, Node *node) {
  if (!node) {
    return;
  }
  if ((it != nullptr) and (*it < node->value)) {
    erase(it, node->left);
  } else if ((it != nullptr) and (*it > node->value)) {
    erase(it, node->right);
  } else {
    if (!node->left && !node->right) {
      if (node == m_root_) {
        m_root_ = nullptr;
      } else if (node == node->parent->left) {
        node->parent->left = nullptr;
      } else {
        node->parent->right = nullptr;
      }
      delete node;
      --m_size_;
    } else if (node->left && node->right) {
      Node *min_node = node->right;
      while (min_node->left) {
        min_node = min_node->left;
      }
      node->value = min_node->value;
      erase(iterator(min_node), min_node);
    } else {
      Node *child = node->left ? node->left : node->right;
      if (node == m_root_) {
        m_root_ = child;
        if (child) {
          child->parent = nullptr;
        }
      } else if (node == node->parent->left) {
        node->parent->left = child;
        if (child) {
          child->parent = node->parent;
        }
      } else {
        node->parent->right = child;
        if (child) {
          child->parent = node->parent;
        }
      }
      delete node;
      --m_size_;
    }
  }
}

template <typename key_type>
std::pair<typename Multiset<key_type>::iterator, bool>
Multiset<key_type>::insert_emplace(const key_type &value) {
  auto result = insert(value);
  return std::pair<iterator, bool>(result, true);
}

template <typename value_type>
void Multiset<value_type>::print_tree(Node *node) const {
  if (node) {
    print_tree(node->left);
    std::cout << node->value << " ";
    print_tree(node->right);
  }
}

template <typename value_type>
void Multiset<value_type>::print() const {
  print_tree(m_root_);
  std::cout << std::endl;
}

}  // namespace s21
#endif  //
SRC_S21_MULTISET_H_