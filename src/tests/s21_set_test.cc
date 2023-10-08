#include "../s21_set.h"

#include <gtest/gtest.h>

// Default constructor
TEST(SetTest, DefaultConstructor) {
  s21::Set<int> s;
  ASSERT_TRUE(s.empty());
}

// Initializer list constructor
TEST(SetTest, InitializerListConstructor) {
  s21::Set<int> s{1, 2, 3};
  ASSERT_EQ(s.size(), 3);
  ASSERT_TRUE(s.find(1) != s.end());
  ASSERT_TRUE(s.find(2) != s.end());
  ASSERT_TRUE(s.find(3) != s.end());
}

TEST(SetTest, InitializerListConstructor1) {
  s21::Set<int> s1({1, 2, 3, 4, 5});
  EXPECT_EQ(s1.size(), 5);
  EXPECT_TRUE(s1.find(1) != s1.end());
  EXPECT_TRUE(s1.find(2) != s1.end());
  EXPECT_TRUE(s1.find(3) != s1.end());
  EXPECT_TRUE(s1.find(4) != s1.end());
  EXPECT_TRUE(s1.find(5) != s1.end());

  s21::Set<std::string> s2({"hello", "world"});
  EXPECT_EQ(s2.size(), 2);
  EXPECT_TRUE(s2.find("hello") != s2.end());
  EXPECT_TRUE(s2.find("world") != s2.end());

  s21::Set<int> s3({});
  EXPECT_EQ(s3.size(), 0);

  s21::Set<std::string> s4({"foo", "bar", "baz", "qux"});
  EXPECT_EQ(s4.size(), 4);
  EXPECT_TRUE(s4.find("foo") != s4.end());
  EXPECT_TRUE(s4.find("bar") != s4.end());
  EXPECT_TRUE(s4.find("baz") != s4.end());
  EXPECT_TRUE(s4.find("qux") != s4.end());
}

// Copy constructor
TEST(SetTest, CopyConstructor) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2(s1);
  ASSERT_EQ(s1.size(), s2.size());
}

// Move constructor
TEST(SetTest, MoveConstructor) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2(std::move(s1));
  ASSERT_TRUE(s1.empty());
  ASSERT_EQ(s2.size(), 3);
  ASSERT_TRUE(s2.find(1) != s2.end());
  ASSERT_TRUE(s2.find(2) != s2.end());
  ASSERT_TRUE(s2.find(3) != s2.end());
}

// Destructor
TEST(SetTest, Destructor) {
  s21::Set<int>* s = new s21::Set<int>{1, 2, 3};
  ASSERT_EQ(s->size(), 3);
  delete s;
}

TEST(SetTest, MoveAssignment) {
  s21::Set<int> s1;
  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s21::Set<int> s2;
  s2.insert(4);
  s2.insert(5);
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
  EXPECT_EQ(s1.size(), 0);
  EXPECT_FALSE(s1.contains(1));
  EXPECT_FALSE(s1.contains(2));
  EXPECT_FALSE(s1.contains(3));
}

TEST(SetTest, EmptySetMoveAssignment) {
  s21::Set<int> s1;
  s21::Set<int> s2;
  s2.insert(1);
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_FALSE(s2.contains(1));
  EXPECT_EQ(s1.size(), 0);
  EXPECT_FALSE(s1.contains(1));
}

TEST(SetTest, SwapTest) {
  s21::Set<int> mySet1 = {1, 2, 3};
  s21::Set<int> mySet2 = {4, 5, 6, 7};
  mySet1.swap(mySet2);
  EXPECT_EQ(mySet1.contains(1), 0);
  EXPECT_EQ(mySet1.contains(2), 0);
  EXPECT_EQ(mySet1.contains(3), 0);
  EXPECT_EQ(mySet1.contains(4), 1);
  EXPECT_EQ(mySet1.contains(5), 1);
  EXPECT_EQ(mySet1.contains(6), 1);
  EXPECT_EQ(mySet1.size(), 4);

  EXPECT_EQ(mySet2.contains(1), 1);
  EXPECT_EQ(mySet2.contains(2), 1);
  EXPECT_EQ(mySet2.contains(3), 1);
  EXPECT_EQ(mySet2.contains(4), 0);
  EXPECT_EQ(mySet2.contains(5), 0);
  EXPECT_EQ(mySet2.contains(6), 0);
  EXPECT_EQ(mySet2.size(), 3);
}

TEST(SetTest, Merge) {
  s21::Set<int> s1 = {1, 3, 5};
  s21::Set<int> s2 = {2, 4, 6};
  s1.merge(s2);
  EXPECT_TRUE(s2.empty());
  ASSERT_EQ(s1.size(), 6);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(SetTest, MergeWithDuplicates) {
  s21::Set<int> s1 = {1, 3, 5};
  s21::Set<int> s2 = {1, 3, 7};
  s1.merge(s2);
  EXPECT_TRUE(s2.empty());
  ASSERT_EQ(s1.size(), 4);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 7);
}

TEST(SetTest, MergeEmpty) {
  s21::Set<int> s1 = {1, 3, 5};
  s21::Set<int> s2;
  s1.merge(s2);
  EXPECT_TRUE(s2.empty());
  ASSERT_EQ(s1.size(), 3);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(SetTest, MergeAlreadyEmpty) {
  s21::Set<int> s1 = {1, 3, 5};
  s21::Set<int> s2;
  s2.merge(s1);
  EXPECT_TRUE(s1.empty());
  EXPECT_FALSE(s2.empty());
}

TEST(SetTest, MergeSelf) {
  s21::Set<int> s1 = {1, 3, 5};
  s1.merge(s1);
  ASSERT_EQ(s1.size(), 3);
  auto it = s1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 5);
}

TEST(SetTest, FindEmpty) {
  s21::Set<std::string> s;
  auto iter = s.find("one");
  EXPECT_EQ(iter, s.end());
}

TEST(SetTest, BeginEmptySet) {
  s21::Set<int> set;
  EXPECT_EQ(set.begin(), set.end());
}

TEST(SetTest, BeginNonEmptySet) {
  s21::Set<int> set = {3, 2, 1};
  EXPECT_EQ(*set.begin(), 1);
}

TEST(SetTest, Find) {
  s21::Set<int> s = {1, 2, 3};
  auto iter1 = s.find(1);
  EXPECT_NE(iter1, s.end());

  auto iter2 = s.find(4);
  EXPECT_EQ(iter2, s.end());
}

TEST(SetTest, FindMultiple) {
  s21::Set<int> s = {1, 2, 1};
  auto iter1 = s.find(1);
  EXPECT_NE(iter1, s.end());
  auto iter2 = s.find(2);
  EXPECT_NE(iter2, s.end());
  auto iter3 = s.find(3);
  EXPECT_EQ(iter3, s.end());
}

TEST(SetTest, Size) {
  s21::Set<int> set;
  set.insert(42);
  set.insert(24);
  set.insert(84);
  EXPECT_EQ(set.size(), 3);
}

TEST(SetTest, SizeEmpty) {
  s21::Set<int> set;
  EXPECT_EQ(set.size(), 0);
}

TEST(SetTest, MaxSizeTest) {
  s21::Set<int> mySet;
  size_t maxSize = mySet.max_size();
  EXPECT_GT(maxSize, 0);
  EXPECT_LE(maxSize, std::numeric_limits<size_t>::max());
}

TEST(SetTest, Clear) {
  s21::Set<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

TEST(SetTest, ClearEmptySet) {
  s21::Set<int> s;
  s.clear();
  EXPECT_EQ(s.size(), 0);
  EXPECT_FALSE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_FALSE(s.contains(3));
}

TEST(SetTest, Insert) {
  s21::Set<int> set;
  set.insert(42);
  set.insert(24);
  set.insert(84);
  EXPECT_EQ(set.size(), 3);
  EXPECT_TRUE(set.contains(42));
  EXPECT_TRUE(set.contains(24));
  EXPECT_TRUE(set.contains(84));
  EXPECT_FALSE(set.insert(42).second);
}

TEST(SetTest, InsertString) {
  s21::Set<std::string> s;
  s.insert("foo");
  s.insert("bar");
  s.insert("baz");
  EXPECT_TRUE(s.contains("foo"));
  EXPECT_TRUE(s.contains("bar"));
  EXPECT_TRUE(s.contains("baz"));
  EXPECT_FALSE(s.contains("qux"));
  EXPECT_FALSE(s.contains("xyzzy"));
}

TEST(SetTest, InsertEmpty) {
  s21::Set<int> set;
  set.insert(42);
  EXPECT_EQ(set.size(), 1);
  EXPECT_TRUE(set.contains(42));
}

TEST(SetTest, InsertDuplicate) {
  s21::Set<int> set;
  set.insert(42);
  auto result = set.insert(42);
  EXPECT_FALSE(result.second);
  EXPECT_EQ(set.size(), 1);
}

TEST(SetEraseTest, EraseSingleElement) {
  s21::Set<int> s{5, 4, 3, 2, 1};
  auto it = s.find(3);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(4u, s.size());
  ASSERT_EQ(s.end(), s.find(3));
}

TEST(SetEraseTest, EraseSingleElement1) {
  s21::Set<int> s = {5, 6, 4, 7, 3, 8, 2, 9, 1};
  auto it = s.find(3);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(8u, s.size());
  ASSERT_EQ(s.end(), s.find(3));
}

TEST(SetEraseTest, EraseSingleElement2) {
  s21::Set<int> s = {5, 6, 4, 7, 3, 8, 2, 9, 1};
  auto it = s.find(7);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(8u, s.size());
  ASSERT_EQ(s.end(), s.find(7));
}

TEST(SetEraseTest, EraseSingleElement3) {
  s21::Set<int> s = {5, 8, 6, 7};
  auto it = s.find(8);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(3u, s.size());
  ASSERT_EQ(s.end(), s.find(8));
}

TEST(SetEraseTest, EraseFirstElement) {
  s21::Set<int> s{3, 2, 1};
  auto it = s.begin();
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(2u, s.size());
  ASSERT_EQ(s.end(), s.find(1));
}

TEST(SetEraseTest, EraseLastElement) {
  s21::Set<int> s{1, 2, 3};
  auto it = s.find(3);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(2u, s.size());
  ASSERT_EQ(s.end(), s.find(3));
}

TEST(IteratorTest, OperatorEqual) {
  s21::Set<int>::Node* root = new s21::Set<int>::Node(4);
  root->left = new s21::Set<int>::Node(2);
  root->left->parent = root;
  root->left->left = new s21::Set<int>::Node(1);
  root->left->left->parent = root->left;
  typename s21::Set<int>::SetIterator it1(root);
  typename s21::Set<int>::SetIterator it2(root);
  typename s21::Set<int>::SetIterator it3(root->left);
  typename s21::Set<int>::SetIterator it4(root->left->left);
  ASSERT_EQ(it1, it2);
  ASSERT_NE(it1, it3);
  ASSERT_NE(it1, it4);
}

TEST(IteratorTest, OperatorDereference) {
  s21::Set<int>::Node* root = new s21::Set<int>::Node(4);
  s21::Set<int>::SetIterator it(root);
  ASSERT_EQ(*it, 4);
}

TEST(IteratorTest, OperatorIncrement) {
  s21::Set<int> mySet;
  mySet.insert(4);
  mySet.insert(2);
  mySet.insert(1);
  mySet.insert(3);
  mySet.insert(6);
  mySet.insert(5);
  mySet.insert(7);
  s21::Set<int>::SetIterator it = mySet.begin();
  ASSERT_EQ(*it++, 1);
  ASSERT_EQ(*it++, 2);
  ASSERT_EQ(*it++, 3);
  ASSERT_EQ(*it++, 4);
  ASSERT_EQ(*it++, 5);
  ASSERT_EQ(*it++, 6);
  ASSERT_EQ(*it++, 7);
}

TEST(IteratorTest, OperatorIncrementEdgeCases) {
  s21::Set<int>::Node* root = new s21::Set<int>::Node(4);
  root->left = new s21::Set<int>::Node(2);
  root->right = new s21::Set<int>::Node(6);
  root->left->left = new s21::Set<int>::Node(1);
  root->left->right = new s21::Set<int>::Node(3);
  typename s21::Set<int>::SetIterator it2(root);
  typename s21::Set<int>::SetIterator it3(root->left);
  typename s21::Set<int>::SetIterator it4(root->left->left);
  ASSERT_EQ(it2++, root);
  ASSERT_EQ(++it3, root->left->right);
  ASSERT_EQ(it4++, root->left->left);
  delete root->left->left;
  delete root->left->right;
}

TEST(SetTest, insert_many) {
  s21::Set<int> my_set;
  auto res1 = my_set.insert_many(1);
  EXPECT_TRUE(res1[0].second);
  auto res2 = my_set.insert_many(2, 3, 4);
  EXPECT_TRUE(res2[0].second);
  EXPECT_TRUE(res2[1].second);
  EXPECT_TRUE(res2[2].second);
  auto res3 = my_set.insert_many(1, 2, 3);
  EXPECT_FALSE(res3[0].second);
  EXPECT_FALSE(res3[1].second);
  EXPECT_FALSE(res3[2].second);
}

TEST(SetTest, insert_many_string) {
  s21::Set<std::string> my_set;
  auto res1 = my_set.insert_many("one");
  EXPECT_TRUE(res1[0].second);
  auto res2 = my_set.insert_many("two", "three", "four");
  EXPECT_TRUE(res2[0].second);
  EXPECT_TRUE(res2[1].second);
  EXPECT_TRUE(res2[2].second);
  auto res3 = my_set.insert_many("one", "two", "three");
  EXPECT_FALSE(res3[0].second);
  EXPECT_FALSE(res3[1].second);
  EXPECT_FALSE(res3[2].second);
}
