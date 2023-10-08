#ifndef SRC_S21_CONTAINERS_OOP_H_
#define SRC_S21_CONTAINERS_OOP_H_

#include "s21_helpsrc.h"

namespace s21 {
template <class T>
class List {
  using A = class std::allocator<T>;

 public:
  template <class value_type>
  class Node {
   public:
    Node *pNext, *pPrev;
    value_type data;

   public:
    Node(value_type data = value_type(), Node* pPrev = nullptr,
         Node* pNext = nullptr) {
      this->data = data;
      this->pNext = pNext;
      this->pPrev = pPrev;
    }
  };
  using node_allocator =
      typename std::allocator_traits<A>::template rebind_alloc<List>;
  node_allocator allocator;
  /*-----------------------------------------iterators  ------*/
 public:
  template <class>
  class ListIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;
    using value_type = T;
    using pointer_type = value_type*;
    using reference = value_type&;
    using iterator = ListIterator<value_type>;
    ListIterator() { IterPointer_ = nullptr; }
    ListIterator(int) : ListIterator() {}
    ListIterator(Node<value_type>* IterNode) : ListIterator() {
      IterPointer_ = IterNode;
    }
    ListIterator(const ListIterator& other)
        : IterPointer_(other.IterPointer_){};
    ~ListIterator(){};
    reference operator*() const {
      if (IterPointer_ == nullptr) throw std::invalid_argument("null");
      return this->IterPointer_->data;
    }
    pointer_type operator->() const { return IterPointer_; }
    // pointer_type operator->() const { return &IterPointer_->data; }
    Node<value_type>* getIterPointer() { return IterPointer_; }
    ListIterator& operator++() {
      IterPointer_ = IterPointer_->pNext;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator it(*this);
      IterPointer_ = IterPointer_->pNext;
      return it;
    }
    ListIterator& operator+(int pos) {
      ListIterator::iterator current = getIterPointer();
      int temp = 0;
      while (temp != pos) {
        temp++;
        current = current.getIterPointer()->pNext;
      }
      return current;
    }
    ListIterator& operator--() {
      IterPointer_ = IterPointer_->pPrev;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator it = *this;
      --(*this);
      return it;
    }
    ListIterator operator[](const value_type index) {
      return *(IterPointer_ + index);
    }  //{return *(IterPointer_[index]);}
    bool operator==(const ListIterator& other) const {
      return this->IterPointer_ == other.IterPointer_;
    };  // this->IterPointer_
    bool operator!=(const ListIterator& other) const {
      return this->IterPointer_ != other.IterPointer_;
    };
    bool operator<=(const ListIterator& other) {
      return (this->IterPointer_ < other.IterPointer_) ||
             (this->IterPointer_ == other.IterPointer_);
    };

   private:
    Node<value_type>* IterPointer_;
    friend class List<value_type>;
  };

 public:
  template <class>
  class ListConstIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;
    using value_type = T;
    using pointer_type = value_type*;
    using reference = value_type&;
    using const_iterator = ListConstIterator<value_type>;
    ListConstIterator() { IterPointer_ = nullptr; }
    ListConstIterator(int) : ListConstIterator() {}
    ListConstIterator(Node<value_type>* IterNode) : ListConstIterator() {
      IterPointer_ = IterNode;
    }
    ListConstIterator(const ListConstIterator& other)
        : IterPointer_(other.IterPointer_){};
    ~ListConstIterator(){};
    reference operator*() const {
      if (IterPointer_ == nullptr) throw std::invalid_argument("null");
      return this->IterPointer_->data;
    }
    pointer_type operator->() const { return IterPointer_; }
    // pointer_type operator->() const { return &IterPointer_->data; }
    Node<value_type>* getIterPointer() { return IterPointer_; }
    ListConstIterator& operator++() {
      IterPointer_ = IterPointer_->pNext;
      return *this;
    }
    ListConstIterator operator++(int) {
      ListConstIterator it(*this);
      IterPointer_ = IterPointer_->pNext;
      return it;
    }
    ListConstIterator& operator+(int pos) {
      const_iterator current = getIterPointer();
      int temp = 0;
      while (temp != pos) {
        temp++;
        current = current.getIterPointer()->pNext;
      }
      return current;
    }
    ListConstIterator& operator--() {
      IterPointer_ = IterPointer_->pPrev;
      return *this;
    }
    ListConstIterator operator--(int) {
      ListConstIterator it = *this;
      --(*this);
      return it;
    }
    ListConstIterator operator[](const value_type index) {
      return *(IterPointer_ + index);
    }
    bool operator==(const_iterator& other) const {
      return this->IterPointer_ == other.IterPointer_;
    };
    bool operator!=(const_iterator& other) const {
      return this->IterPointer_ != other.IterPointer_;
    };

   private:
    const Node<value_type>* IterPointer_;
    friend class List<value_type>;
  };
  /*---------------------------end of block "iterators"--------------------*/
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  List();
  List(const List& l);
  List(List&& l) noexcept;
  List(std::initializer_list<value_type> const& items);
  List(size_type n);
  ~List();
  List& operator=(const List& l);
  List& operator=(List&& l) noexcept;
  List& operator+(const List& l);
  using iterator = ListIterator<List>;
  using const_iterator = ListConstIterator<List>;
  const_reference front();
  const_reference back();
  iterator begin() const;
  iterator end() const;
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  void push_back(const_reference data);
  void push_front(const_reference data);
  void pop_back();
  void pop_front();
  void Swap(List& l);
  void reverse();
  void Merge(List& other);
  void Splice(iterator pos, List<value_type>& other);
  void unique();
  void Sort();
  void insert(iterator pos, const_reference data);
  void erase(iterator pos);
  template <typename... Args>
  iterator insert_many(iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);
  void initializeFields();
  void print();
  //  iterator my_next(typename s21::List<T>::iterator it, int n = 1);
  int Size;
  Node<value_type>* head;
  Node<value_type>* tail;
};
template <typename value_type>
List<value_type>::List() {
  tail = new Node<value_type>();
  head = tail;
  Size = 0;
}
template <typename value_type>
List<value_type>::List(const List& l) : List() {
  operator=(l);
}
template <typename value_type>
List<value_type>::List(List&& l) noexcept : List() {
  clear();
  head = l.head;
  tail = l.tail;
  Size = l.Size;
  l.head = NULL;
  l.tail = NULL;
  l.Size = 0;
}
template <typename value_type>
List<value_type>::List(std::initializer_list<value_type> const& items)
    : List() {
  for (const auto& element : items) {
    push_back(element);
  }
}
template <typename value_type>
List<value_type>::List(size_type n) : List() {
  for (size_type i = 0; i < n; i++) {
    push_back(value_type());
  }
}

template <typename value_type>
List<value_type>::~List() {
  clear();
  delete tail;
}
template <typename value_type>
List<value_type>& List<value_type>::operator=(const List& l) {
  clear();
  iterator currentPtr = l.begin();
  while (currentPtr != l.end()) {
    this->push_back(currentPtr.getIterPointer()->data);
    currentPtr++;
  }
  return *this;
}

template <typename value_type>
List<value_type>& List<value_type>::operator=(List&& l) noexcept {
  clear();
  iterator currentPtr = l.begin();
  while (currentPtr != l.end()) {
    this->push_back(currentPtr.getIterPointer()->data);
    currentPtr++;
  }
  l.clear();
  s21::List(std::move(l));
  return *this;
}
template <typename value_type>
List<value_type>& List<value_type>::operator+(const List& l) {
  // 1) get access to the list "l"
  iterator temp = l.begin();
  // 2) add nodes temp to the l list
  while (temp != l.end()) {
    push_back(*temp);
    temp++;
  }
  // 3.return unified list
  return *this;
}
template <typename value_type>
void List<value_type>::print() {
  for (Node<value_type>* node = head; node != tail; node = node->pNext) {
    std::cout << node->data << " ";
  }
  std::cout << std::endl;
}
template <typename value_type>
typename List<value_type>::const_reference List<value_type>::front() {
  return this->head->data;
}
template <typename value_type>
typename List<value_type>::const_reference List<value_type>::back() {
  return this->tail->pPrev->data;
}
template <typename value_type>
typename List<value_type>::iterator List<value_type>::begin() const {
  return iterator(this->head);
}
template <typename value_type>
typename List<value_type>::iterator List<value_type>::end() const {
  return iterator(this->tail);
}
template <typename value_type>
bool List<value_type>::empty() {
  return size() == 0;
}
template <typename value_type>
typename List<value_type>::size_type List<value_type>::size() {
  return Size;
}
template <typename value_type>
typename List<value_type>::size_type List<value_type>::max_size() {
  return allocator.max_size();
}
template <typename value_type>
void List<value_type>::clear() {
  while (Size) pop_front();
}
template <typename value_type>
void List<value_type>::push_back(const_reference data) {
  Node<value_type>* ptr = new Node<value_type>(data);
  ptr->pNext = tail;
  if (Size != 0) {
    tail->pPrev->pNext = ptr;
    ptr->pPrev = tail->pPrev;
  }
  tail->pPrev = ptr;
  if (Size == 0) {
    head = ptr;
  }
  Size++;
}
template <typename value_type>
void List<value_type>::push_front(const_reference data) {
  Node<value_type>* ptr = new Node<value_type>(data);
  ptr->pNext = head;
  if (head != NULL) {
    head->pPrev = ptr;
  }
  if (Size == 0) {
    head = ptr;
    ptr->pNext = tail;
    tail->pPrev = ptr;
  }
  head = ptr;
  ptr->pPrev = NULL;
  Size++;
}
template <typename value_type>
void List<value_type>::pop_back() {
  Node<value_type>* ptr = tail->pPrev;
  if (ptr == nullptr) {
    return;
  } else if (Size == 1) {
    head = tail;
    tail->pPrev = nullptr;
  }
  if (Size > 1) {
    tail->pPrev->pPrev->pNext = tail;
    tail->pPrev = tail->pPrev->pPrev;
  }
  delete ptr;
  Size--;
}
template <typename value_type>
void List<value_type>::pop_front() {
  {
    if (head == NULL) return;
    Node<value_type>* ptr = head->pNext;
    if (ptr != NULL) {
      ptr->pPrev = NULL;
    } else {
      tail = ptr;
    }
    delete head;
    head = ptr;
    Size--;
  }
}
template <typename value_type>
void List<value_type>::Swap(List& l) {
  std::swap(this->head, l.head);
  std::swap(this->tail, l.tail);
  std::swap(this->Size, l.Size);
}
template <typename value_type>
void List<value_type>::reverse() {
  Node<value_type>* currentNode = head;
  Node<value_type>* nextNode;
  if (head == nullptr) {
    return;
  } else {
    while (currentNode != tail) {
      nextNode = currentNode->pNext;
      currentNode->pNext = currentNode->pPrev;
      currentNode->pPrev = nextNode;
      currentNode = nextNode;
    }
    currentNode = head;
    head = tail->pPrev;
    tail->pPrev = currentNode;
    currentNode->pNext = tail;
  }
}

template <typename value_type>
void List<value_type>::Merge(List& other) {
  this->operator+(other);
  this->Sort();
}
template <typename value_type>
void List<value_type>::Splice(iterator pos, List<value_type>& other) {
  if (!other.head || !other.tail->pPrev) return;  // if other.empty()

  Node<value_type>* startNode = other.head;
  Node<value_type>* endNode = other.tail->pPrev;
  startNode->pPrev = pos.getIterPointer()->pPrev;
  endNode->pNext = pos.getIterPointer();
  if (pos.getIterPointer()->pPrev != nullptr) {
    pos.getIterPointer()->pPrev->pNext = startNode;
  } else {
    head = startNode;
  }
  pos.getIterPointer()->pPrev = endNode;
  Size = Size + other.Size;
  other.Size = 0;
  other.head = nullptr;
  // other.tail->pPrev = other.tail;
  other.tail = nullptr;
}
template <typename value_type>
void List<value_type>::unique() {
  if (head == nullptr) {
    return;
  }
  // this->Sort();
  Node<value_type>* currentNode = head;
  while (currentNode != nullptr) {
    Node<value_type>* nextNode = currentNode->pNext;
    while (nextNode != nullptr && nextNode->data == currentNode->data) {
      Node<value_type>* temp = nextNode;
      nextNode = nextNode->pNext;
      if (nextNode != nullptr) nextNode->pPrev = currentNode;
      delete temp;
      Size--;
    }
    currentNode->pNext = nextNode;
    if (nextNode != nullptr) nextNode->pPrev = currentNode;
    currentNode = nextNode;
  }
}
template <typename value_type>
void List<value_type>::Sort() {
  bool SwapDone = true;  //  activated when swapped, default: on
  Node<value_type>* currNode;
  if (head == NULL)  // if list is empty, exit
  {
    return;
  }
  while (SwapDone) {
    currNode = head;   // we start from head
    SwapDone = false;  // reset for each iteration
    while (currNode->pNext != tail) {
      if (currNode->data >
          currNode->pNext->data) {  // if the next element is less
        value_type temp = currNode->data;
        currNode->data = currNode->pNext->data;
        currNode->pNext->data = temp;
        SwapDone = true;  //  the swap is done and switch the flag
      }
      currNode = currNode->pNext;  // move next
    }
    tail->pPrev = currNode;  //  mark the last swapped node
  }
}
template <typename value_type>
void List<value_type>::initializeFields() {
  Size = 0;
  head = nullptr;
  tail = nullptr;
}
template <typename value_type>
void List<value_type>::insert(iterator pos, const_reference data) {
  Node<value_type>* newNode = new Node<value_type>(data);
  iterator posNode = pos.IterPointer_;
  if (posNode != begin()) {
    newNode->pPrev = posNode.getIterPointer()->pPrev;
    newNode->pNext = posNode.getIterPointer();
    posNode.getIterPointer()->pPrev->pNext = newNode;
    posNode.getIterPointer()->pPrev = newNode;
  } else {
    newNode->pNext = posNode.getIterPointer();
    posNode.getIterPointer()->pPrev = newNode;
    head = newNode;
  }
  ++Size;
}
template <typename value_type>
void List<value_type>::erase(iterator pos) {
  if (pos == end()) {
    return;
  }
  if (pos == begin()) {
    pop_front();
    return;
  }
  for (auto current = head; current != tail; current = current->pNext) {
    if (current->pNext == pos.getIterPointer()) {
      current->pNext = pos.getIterPointer()->pNext;
      delete pos.getIterPointer();
      Size--;
      return;
    }
  }
}
/*----------BONUS---------------*/
template <typename value_type>
template <typename... Args>
typename List<value_type>::iterator List<value_type>::insert_many(
    iterator pos, Args&&... args) {
  Node<value_type>* nodeIn = pos.IterPointer_;
  Node<value_type>* newNode = new Node<value_type>(std::forward<Args>(args)...);
  newNode->pPrev = nodeIn->pPrev;
  newNode->pNext = nodeIn;
  if (nodeIn->pPrev) {
    nodeIn->pPrev->pNext = newNode;
  } else {
    head = newNode;
  }
  nodeIn->pPrev = newNode;
  Size++;
  return iterator(newNode);
}
template <typename value_type>
template <typename... Args>
void List<value_type>::insert_many_back(Args&&... args) {
  for (auto newData : {std::forward<Args>(args)...}) {
    push_back(newData);
  }
}
template <typename value_type>
template <typename... Args>
void List<value_type>::insert_many_front(Args&&... args) {
  for (auto newData : {std::forward<Args>(args)...}) {
    push_front(newData);
  }
}
}  // namespace s21

#endif  // SRC_S21_CONTAINERS_OOP_H_
