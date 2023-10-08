#include <gtest/gtest.h>
// #include <list>
// #include <iterator>
// #include <queue>
#include "../s21_list.h"

// using namespace std;

namespace s21 {
TEST(Suite_List_Constructors, Default_1) {
  s21::List<double> l;
  EXPECT_EQ(0, l.size());
  EXPECT_EQ(l.head, l.tail);
}
TEST(Suite_List_Constructors, Default_2) {
  s21::List<double> l;
  auto iter1 = l.begin();
  auto iter2 = l.end();
  EXPECT_EQ(0, l.size());
  EXPECT_EQ(*iter1, *iter2);
}
TEST(Suite_List_Constructors, With_parameter) {
  s21::List<double> l1(5);
  EXPECT_EQ(l1.size(), 5);
  EXPECT_EQ(l1.front(), 0);
}
TEST(Suite_List_Constructors, Initializer_list) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Suite_List_Constructors, Copy) {
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  s21::List<int> l1(l2);
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}
TEST(Suite_List_Constructors, Move) {
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  s21::List<int> l1 = std::move(l2);
  EXPECT_EQ(1, l1.front());
  EXPECT_EQ(5, l1.back());
  EXPECT_EQ(0, l2.size());
}

TEST(Suite_List_Elements, front_and_back) {
  std::list<double> l1 = {1.366, 2, 3};
  s21::List<double> l2 = {1.366, 2, 3};
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
}

TEST(Suite_List_Modifiers, Clear) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  l1.clear();
  l2.clear();
  EXPECT_EQ(l1.size(), l2.size());
  EXPECT_EQ(l2.size(), 0);
}

TEST(Suite_List_Modifiers, empty) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(l1.empty(), l2.empty());
}

TEST(Suite_List_Modifiers, size) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Suite_List_Modifiers, Reverse) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  l1.reverse();
  l2.reverse();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Suite_List_Modifiers, Reverse_2) {
  s21::List<int> s21_list_1 = {1, 2, 3, 4};
  s21::List<int> s21_list_2 = {4, 3, 2, 1};
  s21_list_1.reverse();
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(Suite_List_Modifiers, Sort) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  l1.sort();
  l2.Sort();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Suite_List_Modifiers, Merge) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {3, 4, 5, 6};
  a1.merge(a2);
  s21::List<int> b1 = {1, 2, 3};
  s21::List<int> b2 = {3, 4, 5, 6};
  b1.Merge(b2);

  EXPECT_EQ(a1.front(), b1.front());
  EXPECT_EQ(a1.back(), b1.back());
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(Suite_List_Modifiers, Swap) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {3, 4, 5, 6};
  a1.swap(a2);
  s21::List<int> b1 = {1, 2, 3};
  s21::List<int> b2 = {3, 4, 5, 6};
  b1.Swap(b2);

  EXPECT_EQ(a1.front(), b1.front());
  EXPECT_EQ(a1.back(), b1.back());
  EXPECT_EQ(a1.size(), b1.size());
}
TEST(Suite_List_Modifiers, pop_back) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::List<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.pop_back();
  l2.pop_back();
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Suite_List_Modifiers, pop_front) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::List<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.pop_front();
  l2.pop_front();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Suite_List_Modifiers, Push_back) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::List<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.push_back(11);
  l2.push_back(11);
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());

  std::list<int> l3;
  s21::List<int> l4;
  l3.push_back(11);
  l4.push_back(11);
  EXPECT_EQ(l3.back(), l4.back());
  EXPECT_EQ(l3.size(), l4.size());
}

TEST(Suite_List_Modifiers, Push_front) {
  std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::List<int> l2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  l1.push_front(11);
  l2.push_front(11);
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());

  std::list<int> l3;
  s21::List<int> l4;
  l3.push_front(11);
  l4.push_front(11);
  EXPECT_EQ(l3.front(), l4.front());
  EXPECT_EQ(l3.size(), l4.size());
}
TEST(Suite_List_Iterators, Begin) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.begin();
  auto iter2 = l2.begin();
  EXPECT_EQ(*iter1, *iter2);
}

TEST(Suite_List_Iterators, End) {
  s21::List<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.end();
  auto iter2 = l2.end();
  EXPECT_EQ(*iter1, *iter2);
}

TEST(Suite_List_modifier, insert_0) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = l1.begin();  //++
  auto iter2 = l2.begin();  //++
  l1.insert(iter1, 11);
  l2.insert(iter2, 11);
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}
TEST(Suite_List_modifier, insert_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = ++l1.begin();  //++
  auto iter2 = ++l2.begin();  //++
  l1.insert(iter1, 11);
  l2.insert(iter2, 11);
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}
/////////////////////////////////////

TEST(Suite_List_modifier, insert_2) {
  std::list<std::string> l1 = {"hello", "world"};
  s21::List<std::string> l2 = {"hello", "world"};

  // insert "how" in the beginning
  auto it1 = l1.begin();
  // it1++;
  if (it1 != l1.end()) {
    l1.insert(it1, "how");
  }
  auto it2 = l2.begin();
  // it2++;
  if (it2 != l2.end()) {
    l2.insert(it2, "how");
  }
  // check that lists contain the same
  EXPECT_EQ(l1.size(), l2.size());
  auto it1_begin = l1.begin();
  auto it2_begin = l2.begin();
  while (it1_begin != l1.end() && it2_begin != l2.end()) {
    EXPECT_EQ(*it1_begin, *it2_begin);
    ++it1_begin;
    ++it2_begin;
  }
}

TEST(Suite_List_modifier, insert_3) {
  std::list<std::string> l1 = {"hello", "world"};
  s21::List<std::string> l2 = {"hello", "world"};

  // insert "how" after "hello"
  auto it1 = l1.begin();
  // it1++;
  if (it1 != l1.end()) {
    l1.insert(it1, "how");
  }
  auto it2 = l2.begin();
  // it2++;
  if (it2 != l2.end()) {
    l2.insert(it2, "how");
  }
  // check that lists contain the same
  EXPECT_EQ(l1.size(), l2.size());
  auto it1_begin = l1.begin();
  auto it2_begin = l2.begin();
  while (it1_begin != l1.end() && it2_begin != l2.end()) {
    EXPECT_EQ(*it1_begin, *it2_begin);
    ++it1_begin;
    ++it2_begin;
  }
}

TEST(Suite_List_modifier, insert_front_4) {
  std::list<std::string> l1 = {"hello", "world"};
  s21::List<std::string> l2 = {"hello", "world"};

  // insert "how" in the end
  auto it1 = l1.end();
  l1.insert(it1, "how");
  auto it2 = l2.end();
  l2.insert(it2, "how");

  // check that the nodes order is correct
  EXPECT_EQ(l1.size(), l2.size());
  auto it1_begin = l1.begin();
  auto it2_begin = l2.begin();
  while (it1_begin != l1.end() && it2_begin != l2.end()) {
    EXPECT_EQ(*it1_begin, *it2_begin);
    ++it1_begin;
    ++it2_begin;
  }
}

TEST(Suite_List_modifier, erase) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  auto iter1 = ++l1.begin();
  auto iter2 = ++l2.begin();
  l1.erase(iter1);
  l2.erase(iter2);
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.size(), l2.size());
}
TEST(Suite_List_modifier, Splice) {
  std::list<int> a1 = {1, 2, 3};
  std::list<int> a2 = {3, 4, 5, 6};
  auto iter1 = ++a1.begin();
  a1.splice(iter1, a2);
  s21::List<int> b1 = {1, 2, 3};
  s21::List<int> b2 = {3, 4, 5, 6};
  auto iter2 = ++b1.begin();
  b1.Splice(iter2, b2);

  EXPECT_EQ(a1.front(), b1.front());
  EXPECT_EQ(a1.back(), b1.back());
  EXPECT_EQ(a1.size(), b1.size());
}

TEST(Suite_List_modifier, unique_1) {
  std::list<int> l1 = {1, 2, 3, 4, 5};
  s21::List<int> l2 = {1, 2, 3, 4, 5};
  l1.unique();
  l2.unique();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Suite_List_modifier, unique_2) {
  std::list<int> l1 = {1, 2, 66, 1, 66};
  s21::List<int> l2 = {1, 2, 66, 1, 66};
  l1.unique();
  l2.unique();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}
TEST(Suite_List_modifier, List_modifier_unique_3_Test) {
  std::list<int> l1 = {1, 2, 2, 66, 66};
  s21::List<int> l2 = {1, 2, 2, 66, 66};
  l1.unique();
  l2.unique();
  EXPECT_EQ(l1.front(), l2.front());
  EXPECT_EQ(l1.back(), l2.back());
  EXPECT_EQ(l1.size(), l2.size());
}

TEST(Suite_List_modifier, EmplaceBack) {
  List<int> list;
  list.insert_many_back(1);
  list.insert_many_back(2);
  list.insert_many_back(3);

  ASSERT_EQ(list.size(), 3U);

  auto iter = list.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
}

TEST(Suite_List_modifier, EmplaceFront) {
  List<int> list;

  list.insert_many_front(1);
  list.insert_many_front(2);
  list.insert_many_front(3);

  ASSERT_EQ(list.size(), 3U);

  auto iter = list.begin();
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 1);
}
// TEST(Suite_ListTest, MaxSize) {
//   List<int> list;
//   const auto max_size = list.max_size();
//   EXPECT_GT(max_size, 0U);
//   EXPECT_GT(max_size, list.size());
//   EXPECT_LT(max_size, std::numeric_limits<List<int>::size_type>::max());
// }

TEST(Suite_ListTest, Emplace) {
  List<int> list;

  list.insert_many_back(1);
  list.insert_many_back(2);
  list.insert_many_back(3);

  ASSERT_EQ(list.size(), 3U);

  auto iter = list.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
}

TEST(Suite_ListTest, EmplaceInt) {
  List<int> list = {1, 2, 3};
  auto iter = list.begin();
  ++iter;
  auto it = list.insert_many(iter, 4);
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(list.size(), 4U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

}  // namespace s21