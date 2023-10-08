#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include "s21_helpsrc.h"
#include "s21_vector.h"
namespace s21 {
template <typename T>
class Set {
 public:
  using key_type = T;
  using value_type = T;  // value type (the value itself is a key)
  using reference =
      value_type&;  // defines the type of the reference to an element
  using const_reference =
      const value_type&;     // defines the type of the constant reference
  using size_type = size_t;  // defines the type of the container size (standard
                             // type is size_t)

  struct Node {
    value_type value;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(const value_type& v) : value(v){};
    ~Node() = default;
  };

  class SetIterator {
   public:
    using iterator = SetIterator;
    SetIterator() : node_(nullptr) {}
    SetIterator(Node* node) : node_(node) {}
    SetIterator(const SetIterator& other) : node_(other.node_) {}
    SetIterator(const Node* node) : node_(const_cast<Node*>(node)) {}
    Node* current() const { return node_; }
    bool operator==(const iterator& other) const {
      return node_ == other.node_;
    }
    bool operator!=(const iterator& other) const {
      return node_ != other.node_;
    }
    reference operator*() const { return node_->value; }
    iterator& operator++() {
      if (!node_) {
        return *this;
      }
      if (node_->right) {
        node_ = node_->right;
        while (node_->left) {
          node_ = node_->left;
        }
      } else {
        Node* parent = node_->parent;
        while (parent && node_ == parent->right) {
          node_ = parent;
          parent = parent->parent;
        }
        node_ = parent;
      }
      return *this;
    }
    iterator operator++(int) {
      iterator temp(*this);
      ++(*this);
      return temp;
    }

   protected:
    Node* node_ = nullptr;
  };

  class SetConstIterator : public SetIterator {
   public:
    using const_iterator = SetConstIterator;
    SetConstIterator() : SetIterator() {}
    SetConstIterator(Node* node) : SetIterator(node) {}
    SetConstIterator(const SetIterator& it) : SetIterator(it.node_) {}
    bool operator==(const_iterator& other) const {
      return SetIterator::node_ == other.node_;
    }
    bool operator!=(const_iterator& other) const {
      return SetIterator::node_ != other.node_;
    }
    const_reference operator*() const { return SetIterator::node_->value; }
    const_iterator& operator++() {
      SetIterator::operator++();
      return *this;
    }
    const_iterator operator++(int) {
      iterator temp(*this);
      SetIterator::operator++();
      return temp;
    }
  };

  using iterator = SetIterator;
  using const_iterator = SetConstIterator;

  Set();  // default constructor, creates empty set
  Set(std::initializer_list<value_type> const&
          items);         // initializer list constructor
  Set(const Set& other);  // copy constructor
  Set(Set&& s) noexcept;  // move constructor
  ~Set();                 // destructor

  Set<value_type>& operator=(
      Set<value_type>&&
          other) noexcept;  // assignment operator overload for moving object

  iterator begin();              // returns an iterator to the beginning
  const_iterator begin() const;  // returns an iterator to the beginning
  iterator end();                // returns an iterator to the end
  const_iterator end() const;    // returns an iterator to the end
  bool empty() const;
  size_t size() const;
  size_type max_size();   // returns the maximum possible number of elements
  void clear() noexcept;  // clears the contents

  std::pair<iterator, bool> insert(const value_type& v);
  void erase(iterator pos);            // erases element at pos
  void swap(Set& other);               // swaps the contents
  void merge(Set& other);              // splices nodes from another container
  iterator find(const key_type& key);  // finds element with specific key
  bool contains(
      const key_type& v) const;  // checks if the container contains element

  template <typename... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void print() const;

 private:
  Node* root_ = nullptr;
  size_t size_ = 0;

  Node* copy(const Node* node, Node* parent);
  std::pair<iterator, bool> insert(const value_type& v, Node* node);
  bool contains(const key_type& v, const Node* node) const;
  iterator find(const key_type& key, const Node* node);
  void erase(iterator it, Node* node);
  void destroy_tree(Node* node) noexcept;
  void print_tree(Node* node) const;
};

//--------------------------------------------------------------------
// Implementation
//--------------------------------------------------------------------

template <typename value_type>
Set<value_type>::Set() : root_(nullptr), size_(0) {}

template <typename value_type>
Set<value_type>::Set(const Set& other) : root_(nullptr), size_(0) {
  if (other.root_) {
    root_ = copy(other.root_, nullptr);
    size_ = other.size_;
  }
}

template <typename value_type>
Set<value_type>::Set(std::initializer_list<value_type> const& items) {
  if (items.size() > max_size()) throw std::bad_alloc();
  for (const auto& value : items) {
    insert(value);
  }
}

template <typename value_type>
Set<value_type>::Set(Set&& other) noexcept {
  root_ = other.root_;
  size_ = other.size_;
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
Set<value_type>::~Set() {
  destroy_tree(root_);
}

template <typename value_type>
Set<value_type>& Set<value_type>::operator=(Set<value_type>&& other) noexcept {
  if (this != &other) {
    destroy_tree(root_);
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename value_type>
std::pair<typename Set<value_type>::iterator, bool> Set<value_type>::insert(
    const value_type& v) {
  if (!root_) {
    root_ = new Node(v);
    ++size_;
    return std::make_pair(iterator(root_), true);
  } else {
    return insert(v, root_);
  }
}

template <typename key_type>
bool Set<key_type>::contains(const key_type& v) const {
  return contains(v, root_);
}

template <typename value_type>
void s21::Set<value_type>::erase(iterator it) {
  erase(it, root_);
}

template <typename value_type>
void s21::Set<value_type>::swap(Set& other) {
  Node* tmp_root = root_;
  size_t tmp_size = size_;
  this->root_ = other.root_;
  other.root_ = tmp_root;
  this->size_ = other.size_;
  other.size_ = tmp_size;
}

template <typename value_type>
void s21::Set<value_type>::merge(Set& other) {
  if (this->root_ == other.root_) return;
  auto it = other.begin();
  for (size_t i = 0; i < other.size_; ++i) {
    this->insert(*it);
    ++it;
  }
  other.clear();
}

template <typename key_type>
typename Set<key_type>::iterator s21::Set<key_type>::find(const key_type& key) {
  return find(key, root_);
}

template <typename value_type>
size_t Set<value_type>::size() const {
  return size_;
}

template <typename value_type>
size_t s21::Set<value_type>::max_size() {
  return SIZE_MAX / sizeof(value_type);
}

template <typename value_type>
void s21::Set<value_type>::clear() noexcept {
  destroy_tree(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename value_type>
bool Set<value_type>::empty() const {
  return size_ == 0;
}

template <typename value_type>
typename Set<value_type>::iterator s21::Set<value_type>::begin() {
  Node* node = root_;
  while (node && node->left) {
    node = node->left;
  }
  return iterator(node);
}

template <typename value_type>
typename Set<value_type>::const_iterator s21::Set<value_type>::begin() const {
  Node* node = root_;
  while (node && node->left) {
    node = node->left;
  }
  return const_iterator(node);
}

template <typename value_type>
typename s21::Set<value_type>::iterator Set<value_type>::end() {
  return iterator(static_cast<typename s21::Set<value_type>::Node*>(nullptr));
}

template <typename value_type>
typename s21::Set<value_type>::const_iterator Set<value_type>::end() const {
  return const_iterator(
      static_cast<typename s21::Set<value_type>::Node*>(nullptr));
}

//--------------------------------------------------------------------
// Implementation private
//--------------------------------------------------------------------

template <typename value_type>
typename s21::Set<value_type>::Node* Set<value_type>::copy(const Node* node,
                                                           Node* parent) {
  if (!node) {
    return nullptr;
  }
  Node* new_node = new Node(node->value);
  new_node->parent = parent;
  new_node->left = copy(node->left, new_node);
  new_node->right = copy(node->right, new_node);
  return new_node;
}

template <typename value_type>
std::pair<typename Set<value_type>::iterator, bool> Set<value_type>::insert(
    const value_type& v, Node* node) {
  if (!node) {
    root_ = new Node(v);
    ++size_;
    return std::make_pair(iterator(root_), true);
  }
  if (v < node->value) {
    if (!node->left) {
      node->left = new Node(v);
      node->left->parent = node;
      ++size_;
      return std::make_pair(iterator(node->left), true);
    } else {
      return insert(v, node->left);
    }
  } else if (v > node->value) {
    if (!node->right) {
      node->right = new Node(v);
      node->right->parent = node;
      ++size_;
      return std::make_pair(iterator(node->right), true);
    } else {
      return insert(v, node->right);
    }
  } else {
    return std::make_pair(iterator(node), false);
  }
}

template <typename value_type>
void s21::Set<value_type>::destroy_tree(Node* node) noexcept {
  if (node != nullptr) {
    destroy_tree(node->left);
    destroy_tree(node->right);
    node->left = nullptr;
    node->right = nullptr;
    delete node;
  }
}

template <typename key_type>
bool Set<key_type>::contains(const key_type& v, const Node* node) const {
  if (!node) {
    return false;
  }
  if (v == node->value) {
    return true;
  }
  if (v < node->value) {
    return contains(v, node->left);
  } else {
    return contains(v, node->right);
  }
}

template <typename value_type>
void Set<value_type>::erase(iterator it, Node* node) {
  if (!node) {
    return;
  }
  if (*it < node->value) {
    erase(it, node->left);
  } else if (*it > node->value) {
    erase(it, node->right);
  } else {
    if (!node->left && !node->right) {
      if (node == root_) {
        root_ = nullptr;
      } else if (node == node->parent->left) {
        node->parent->left = nullptr;
      } else {
        node->parent->right = nullptr;
      }
      delete node;
      --size_;
    } else if (node->left && node->right) {
      Node* min_node = node->right;
      while (min_node->left) {
        min_node = min_node->left;
      }
      node->value = min_node->value;
      erase(iterator(min_node), min_node);
    } else {
      Node* child = node->left ? node->left : node->right;
      if (node == root_) {
        root_ = child;
        child->parent = nullptr;
      } else if (node == node->parent->left) {
        node->parent->left = child;
        child->parent = node->parent;
      } else {
        node->parent->right = child;
        child->parent = node->parent;
      }
      delete node;
      --size_;
    }
  }
}

template <typename key_type>
typename Set<key_type>::iterator s21::Set<key_type>::find(const key_type& key,
                                                          const Node* node) {
  if (!node) return iterator();
  if (key == node->value) {
    return iterator(node);
  }
  if (key > node->value) {
    return find(key, node->right);
  } else {
    return find(key, node->left);
  }
}

template <typename value_type>
template <typename... Args>
Vector<std::pair<typename Set<value_type>::iterator, bool>>
Set<value_type>::insert_many(Args&&... args) {
  Vector<std::pair<iterator, bool>> result = {
      (insert(std::forward<Args>(args)))...};
  return result;
}

template <typename value_type>
void Set<value_type>::print_tree(Node* node) const {
  if (node) {
    print_tree(node->left);
    std::cout << node->value << " ";
    print_tree(node->right);
  }
}

template <typename value_type>
void Set<value_type>::print() const {
  print_tree(root_);
  std::cout << std::endl;
}
}  // namespace s21
#endif  // SRC_S21_SET_H_