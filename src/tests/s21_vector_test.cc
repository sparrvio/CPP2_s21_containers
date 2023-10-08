#include "../s21_vector.h"

#include <gtest/gtest.h>

//--------------------------------------------------------------------
// constructor()
//--------------------------------------------------------------------

TEST(VectorTest, test_base_constructor_1) {
  s21::Vector<int> v;
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 0);
}

TEST(VectorTest, test_base_constructor_2) {
  s21::Vector<char> v;
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 0);
}

TEST(VectorTest, test_size_constructor_1) {
  s21::Vector<int> v(5);
  ASSERT_EQ(v.size(), 5);
  ASSERT_EQ(v.capacity(), 5);
}

TEST(VectorTest, test_size_constructor_2) {
  s21::Vector<char> v(5);
  ASSERT_EQ(v.size(), 5);
  ASSERT_EQ(v.capacity(), 5);
}

TEST(VectorTest, test_list_constructor_1) {
  s21::Vector<int> v = {};
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, test_list_constructor_2) {
  s21::Vector<double> v = {3.14};
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v[0], 3.14);
}

TEST(VectorTest, test_list_constructor_3) {
  s21::Vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, test_list_constructor_4) {
  s21::Vector<std::string> v = {"hello", "world"};
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], "hello");
  EXPECT_EQ(v[1], "world");
}

TEST(VectorTest, test_list_constructor_5) {
  struct Person {
    std::string name;
    int age;
  };
  s21::Vector<Person> v = {{"Alice", 25}, {"Bob", 30}};
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0].name, "Alice");
  EXPECT_EQ(v[0].age, 25);
  EXPECT_EQ(v[1].name, "Bob");
  EXPECT_EQ(v[1].age, 30);
}

TEST(VectorTest, test_copy_constructor_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2;
  v2.size();
}

TEST(VectorTest, CopyConstructorTest) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2(v1);
  EXPECT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
  v2[0] = 10;
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v2[0], 10);
  s21::Vector<int> v3;
  EXPECT_NO_THROW(s21::Vector<int> v4(v3));
}

TEST(VectorTest, test_move_constructor_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2(std::move(v1));
  EXPECT_TRUE(v1.empty());
  ASSERT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
}
//--------------------------------------------------------------------
// push_back()
//--------------------------------------------------------------------

TEST(VectorTest, test_push_back_1) {
  s21::Vector<int> v;
  v.push_back(1);
  ASSERT_EQ(v.size(), 1);
  ASSERT_EQ(v.capacity(), 1);
  ASSERT_EQ(v[0], 1);
}

TEST(VectorTest, test_push_back_2) {
  s21::Vector<int> v;
  v.push_back(1);
  v.push_back(2);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
}

TEST(VectorTest, test_push_back_3) {
  s21::Vector<int> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }
  EXPECT_EQ(10, v.size());
  EXPECT_EQ(16, v.capacity());
}

TEST(VectorTest, test_push_back_5) {
  s21::Vector<std::string> v;
  v.push_back("Hello");
  v.push_back("World");
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
  ASSERT_EQ(v[0], "Hello");
  ASSERT_EQ(v[1], "World");
}

//--------------------------------------------------------------------
// pop_back()
//--------------------------------------------------------------------

TEST(VectorTest, test_pop_back_1) {
  s21::Vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.pop_back();
  EXPECT_EQ(2, v.size());
  EXPECT_EQ(4, v.capacity());
  EXPECT_EQ(2, v.back());
}

TEST(VectorTest, test_pop_back_2) {
  s21::Vector<char> v;
  v.push_back(4);
  v.push_back(5);
  v.pop_back();
  v.pop_back();
  EXPECT_EQ(0, v.size());
  EXPECT_EQ(2, v.capacity());
}

TEST(VectorTest, test_pop_back_3) {
  s21::Vector<double> v;
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }
  for (int i = 0; i < 5; i++) {
    v.pop_back();
  }
  EXPECT_EQ(5, v.size());
  EXPECT_EQ(16, v.capacity());
}

//--------------------------------------------------------------------
// begin()
//--------------------------------------------------------------------

TEST(VectorTest, test_iterator_begin_1_int) {
  s21::Vector<int> v = {1, 2, 3};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, v.end());
}

TEST(VectorTest, test_iterator_begin_1_string) {
  s21::Vector<std::string> v = {"Hello", "Done", "Report"};
  auto it = v.begin();
  EXPECT_EQ(*it, "Hello");
  ++it;
  EXPECT_EQ(*it, "Done");
  ++it;
  EXPECT_EQ(*it, "Report");
  ++it;
  EXPECT_EQ(it, v.end());
}

TEST(VectorTest, test_iterator_begin_2) {
  s21::Vector<int> v;
  auto it = v.begin();
  EXPECT_EQ(it, v.end());
}

TEST(VectorTest, test_iterator_begin_3) {
  s21::Vector<int> v = {1};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(it, v.end());
}

TEST(VectorTest, test_iterator_begin_4) {
  s21::Vector<int> v = {1, 2, 3};
  auto it1 = v.begin();
  auto it2 = v.begin();
  EXPECT_EQ(it1, it2);
  ++it1;
  EXPECT_NE(it1, it2);
}

TEST(VectorTest, test_iterator_begin_5_int) {
  s21::Vector<int> v = {1, 2, 3};
  auto it = v.begin();
  *it = 4;
  EXPECT_EQ(*it, 4);
}

TEST(VectorTest, test_iterator_begin_5_string) {
  s21::Vector<std::string> v = {"Hello", "Done", "Report"};
  auto it = v.begin();
  *it = "Bye";
  EXPECT_EQ(*it, "Bye");
}

TEST(VectorTest, test_iterator_begin_6_int) {
  s21::Vector<int> v = {1, 2, 3};
  auto it = v.begin();
  int val = *(it++);
  EXPECT_EQ(val, 1);
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, test_iterator_begin_6_string) {
  s21::Vector<std::string> v = {"Hello", "Done", "Report"};
  auto it = v.begin();
  std::string val = *(it++);
  EXPECT_EQ(val, "Hello");
  EXPECT_EQ(*it, "Done");
}

TEST(VectorTest, test_iterator_begin_7) {
  s21::Vector<int> v = {1, 2, 3};
  auto it = v.begin();
  ++it;
  int val = *it;
  EXPECT_EQ(val, 2);
  EXPECT_EQ(*it, 2);
}

//--------------------------------------------------------------------
// end()
//--------------------------------------------------------------------
TEST(VectorTest, test_end_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  EXPECT_EQ(*(v1.end() - 1), 3);
}

TEST(VectorTest, test_end_2) {
  s21::Vector<std::string> v1 = {"Hello", "world", "!"};
  EXPECT_EQ(*(v1.end() - 1), "!");
}

TEST(VectorTest, test_end_3) {
  s21::Vector<int> v1;
  EXPECT_EQ(v1.end(), v1.begin());
}
//--------------------------------------------------------------------
// swap()
//--------------------------------------------------------------------
TEST(VectorTest, test_swap_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {4, 5, 6};
  s21::Vector<int> v1_copy = v1;
  s21::Vector<int> v2_copy = v2;

  v1.swap(v2);

  EXPECT_EQ(v1[0], v2_copy[0]);
  EXPECT_EQ(v1[1], v2_copy[1]);
  EXPECT_EQ(v1[2], v2_copy[2]);
  EXPECT_EQ(v2[0], v1_copy[0]);
  EXPECT_EQ(v2[1], v1_copy[1]);
  EXPECT_EQ(v2[2], v1_copy[2]);
}
//--------------------------------------------------------------------
// empty()
//--------------------------------------------------------------------
TEST(VectorTest, test_empty_1) {
  s21::Vector<int> v1;
  EXPECT_TRUE(v1.empty());
  v1.push_back(42);
  EXPECT_FALSE(v1.empty());
}

//--------------------------------------------------------------------
// at()
//--------------------------------------------------------------------
TEST(VectorTest, test_at_1) {
  s21::Vector<int> v1 = {1, 2, 3};

  EXPECT_EQ(v1.at(0), 1);
  EXPECT_EQ(v1.at(1), 2);
  EXPECT_EQ(v1.at(2), 3);
  EXPECT_THROW(v1.at(3), std::out_of_range);
}

TEST(VectorTest, test_at_2) {
  s21::Vector<std::string> v1 = {"Hello", "world"};

  EXPECT_EQ(v1.at(0), "Hello");
  EXPECT_EQ(v1.at(1), "world");
  EXPECT_THROW(v1.at(2), std::out_of_range);
}

//--------------------------------------------------------------------
// operator[]
//--------------------------------------------------------------------
TEST(VectorTest, test_operator_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  v1[1] = 42;
  EXPECT_EQ(v1[1], 42);
}

TEST(VectorTest, test_operator_2) {
  s21::Vector<std::string> v1 = {"Hello", "world"};
  EXPECT_EQ(v1[0], "Hello");
  EXPECT_EQ(v1[1], "world");
  v1[1] = "everyone";
  EXPECT_EQ(v1[1], "everyone");
}

//--------------------------------------------------------------------
// operator=
//--------------------------------------------------------------------

TEST(VectorTest, test_operatorEQ_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  s21::Vector<int> v2 = {4, 5, 6};
  v1 = std::move(v2);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v1[2], 6);
  EXPECT_EQ(v2.size(), 0);
  EXPECT_TRUE(v2.empty());
}

TEST(VectorTest, test_operatorEQ_2) {
  s21::Vector<std::string> v1 = {"Hello", "world", "!"};
  s21::Vector<std::string> v2 = {"Goodbye", "cruel", "world"};
  v1 = std::move(v2);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], "Goodbye");
  EXPECT_EQ(v1[1], "cruel");
  EXPECT_EQ(v1[2], "world");
  EXPECT_EQ(v2.size(), 0);
  EXPECT_TRUE(v2.empty());
}

TEST(VectorTest, test_operatorEQ_3) {
  s21::Vector<int> v1;
  s21::Vector<int> v2 = {1, 2, 3};
  v1 = std::move(v2);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  EXPECT_EQ(v2.size(), 0);
  EXPECT_TRUE(v2.empty());
}
//--------------------------------------------------------------------
// front()
//--------------------------------------------------------------------
TEST(VectorTest, test_const_front_1) {
  s21::Vector<int> v1 = {1, 2, 3};

  EXPECT_EQ(v1.front(), 1);
}

TEST(VectorTest, test_const_front_2) {
  s21::Vector<std::string> v1 = {"Hello", "world"};
  EXPECT_EQ(v1.front(), "Hello");
}

TEST(VectorTest, test_const_front_3) {
  s21::Vector<int> v1;
  EXPECT_THROW(v1.front(), std::out_of_range);
}
//--------------------------------------------------------------------
// back()
//--------------------------------------------------------------------
TEST(VectorTest, test_const_back_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  EXPECT_EQ(v1.back(), 3);
}

TEST(VectorTest, test_const_back_2) {
  s21::Vector<std::string> v1 = {"Hello", "world", "!"};
  EXPECT_EQ(v1.back(), "!");
}

TEST(VectorTest, test_const_back_3) {
  s21::Vector<int> v1;
  EXPECT_THROW(v1.back(), std::out_of_range);
}

//--------------------------------------------------------------------
// T* data
//--------------------------------------------------------------------

TEST(VectorTest, test_data_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  int* data_ptr = v1.data();
  EXPECT_NE(data_ptr, nullptr);
  EXPECT_EQ(*data_ptr, 1);
  *data_ptr = 42;
  EXPECT_EQ(v1[0], 42);
}

TEST(VectorTest, test_data_2) {
  s21::Vector<std::string> v1 = {"Hello", "world", "!"};
  std::string* data_ptr = v1.data();
  EXPECT_NE(data_ptr, nullptr);
  EXPECT_EQ(*data_ptr, "Hello");
  *data_ptr = "Hi";
  EXPECT_EQ(v1[0], "Hi");
}

TEST(VectorTest, test_data_3) {
  s21::Vector<int> v1;
  int* data_ptr = v1.data();
  EXPECT_EQ(data_ptr, nullptr);
}
//--------------------------------------------------------------------
// size()
//--------------------------------------------------------------------
TEST(VectorTest, test_size_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  EXPECT_EQ(v1.size(), 3);
  v1.push_back(4);
  EXPECT_EQ(v1.size(), 4);
}

TEST(VectorTest, test_size_2) {
  s21::Vector<std::string> v1 = {"Hello", "world", "!"};
  EXPECT_EQ(v1.size(), 3);
  v1.push_back("Howdy");
  EXPECT_EQ(v1.size(), 4);
}

TEST(VectorTest, test_size_3) {
  s21::Vector<int> v1;
  EXPECT_EQ(v1.size(), 0);
}

//--------------------------------------------------------------------
// max_size()
//--------------------------------------------------------------------
TEST(VectorTest, test_max_size_1) {
  s21::Vector<int> v;
  EXPECT_GE(v.max_size(), v.size());
}

TEST(VectorTest, test_max_size_2) {
  s21::Vector<int> v;
  EXPECT_GT(v.max_size(), 0);
}

TEST(VectorTest, test_max_size_3) {
  s21::Vector<int> v(100);
  EXPECT_GE(v.max_size(), v.size());
}

//--------------------------------------------------------------------
// reserve()
//--------------------------------------------------------------------
TEST(VectorTest, test_reserve_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  v1.reserve(10);
  EXPECT_GE(v1.capacity(), 10);
  v1.push_back(4);
  EXPECT_EQ(v1.size(), 4);
  EXPECT_EQ(v1.capacity(), 10);
}

TEST(VectorTest, test_reserve_2) {
  s21::Vector<std::string> v1;
  v1.reserve(100);
  EXPECT_GE(v1.capacity(), 100);
  v1.push_back("Hello");
  EXPECT_EQ(v1.size(), 1);
  EXPECT_EQ(v1.capacity(), 100);
}

TEST(VectorTest, test_reserve_3) {
  s21::Vector<int> v1 = {1, 2, 3};
  v1.reserve(1);
  EXPECT_EQ(v1.capacity(), 3);
}

TEST(VectorTest, test_reserve_4) {
  s21::Vector<std::string> v1;
  v1.reserve(1);
  EXPECT_GE(v1.capacity(), 1);
  v1.push_back("Hello");
  EXPECT_EQ(v1.size(), 1);
  EXPECT_EQ(v1.capacity(), 1);
  v1.push_back("my");
  v1.push_back("World");
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1.capacity(), 4);
}
//--------------------------------------------------------------------
// shrink_to_fit()
//--------------------------------------------------------------------
TEST(VectorTest, test_shrink_to_fit_1) {
  s21::Vector<int> v = {1, 2, 3};
  v.push_back(4);
  v.push_back(5);
  v.reserve(10);
  v.shrink_to_fit();
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorTest, test_shrink_to_fit_2) {
  s21::Vector<int> v;
  v.reserve(10);
  v.shrink_to_fit();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, test_shrink_to_fit_3) {
  s21::Vector<int> v = {1, 2, 3};
  v.reserve(3);
  v.shrink_to_fit();
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 3);
}
//--------------------------------------------------------------------
// capacity()
//--------------------------------------------------------------------
TEST(VectorTest, test_capacity_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  EXPECT_GE(v1.capacity(), 3);
  v1.reserve(10);
  EXPECT_GE(v1.capacity(), 10);
}

TEST(VectorTest, test_capacity_2) {
  s21::Vector<std::string> v1 = {"Hello", "world", "!"};
  EXPECT_GE(v1.capacity(), 3);
  v1.reserve(100);
  EXPECT_GE(v1.capacity(), 100);
}

TEST(VectorTest, test_capacity_3) {
  s21::Vector<int> v1;
  EXPECT_GE(v1.capacity(), 0);
}

//--------------------------------------------------------------------
// clear()
//--------------------------------------------------------------------
TEST(VectorTest, test_clear_1) {
  s21::Vector<int> v1 = {1, 2, 3};
  v1.clear();
  EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, test_clear_2) {
  s21::Vector<std::string> v1 = {"Hello", "world", "!"};
  v1.clear();
  EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, test_clear_3) {
  s21::Vector<int> v1;
  v1.clear();
  EXPECT_TRUE(v1.empty());
}

//--------------------------------------------------------------------
// erase()
//--------------------------------------------------------------------
TEST(VectorTest, test_erase_1) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin() + 2;
  v.erase(it);
  ASSERT_EQ(v.size(), 4);
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 2);
  ASSERT_EQ(v[2], 4);
  ASSERT_EQ(v[3], 5);
}

TEST(VectorTest, test_erase_2) {
  s21::Vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  v.erase(it);
  it = v.begin();
  v.erase(it);
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[0], 3);
  ASSERT_EQ(v[1], 4);
  ASSERT_EQ(v[2], 5);
}
//--------------------------------------------------------------------
// insert()
//--------------------------------------------------------------------
TEST(VectorTest, test_insert_1) {
  s21::Vector<int> v = {1, 2, 3};
  auto it = v.insert(v.begin(), 4);
  ASSERT_EQ(*it, 4);
  ASSERT_EQ(v.size(), 4);
  ASSERT_EQ(v[0], 4);
  ASSERT_EQ(v[1], 1);
  ASSERT_EQ(v[2], 2);
  ASSERT_EQ(v[3], 3);
}

TEST(VectorTest, test_insert_2) {
  s21::Vector<std::string> v = {"my", "world"};
  auto it = v.insert(v.begin(), "Hello");
  ASSERT_EQ(*it, "Hello");
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[0], "Hello");
  ASSERT_EQ(v[1], "my");
  ASSERT_EQ(v[2], "world");
}

TEST(VectorTest, test_insert_3) {
  s21::Vector<std::string> v = {"Hello", "world"};
  auto it = v.insert(v.begin() + 1, "my");
  ASSERT_EQ(*it, "my");
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v[0], "Hello");
  ASSERT_EQ(v[1], "my");
  ASSERT_EQ(v[2], "world");
}

TEST(VectorTest, test_insert_4) {
  s21::Vector<int> v{1, 2, 3, 4};
  auto it = v.insert(v.begin(), 0);
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3);
  EXPECT_EQ(v[4], 4);

  it = v.insert(v.begin() + 2, 5);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(*it, 5);
  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[2], 5);
  EXPECT_EQ(v[3], 2);
  EXPECT_EQ(v[4], 3);
  EXPECT_EQ(v[5], 4);

  it = v.insert(v.end(), 6);
  EXPECT_EQ(v.size(), 7);
  EXPECT_EQ(*it, 6);
  EXPECT_EQ(v[0], 0);
  EXPECT_EQ(v[1], 1);
  EXPECT_EQ(v[2], 5);
  EXPECT_EQ(v[3], 2);
  EXPECT_EQ(v[4], 3);
  EXPECT_EQ(v[5], 4);
  EXPECT_EQ(v[6], 6);
}

TEST(VectorTest, test_insert_5) {
  s21::Vector<int> v;
  v.insert(v.begin(), 0);
  EXPECT_EQ(v[0], 0);
}
//--------------------------------------------------------------------
// insert_many_back()
//--------------------------------------------------------------------
TEST(VectorTest, test_emplace_back_1) {
  s21::Vector<int> vec = {1, 2, 3};
  vec.insert_many_back(4, 5, 6);
  s21::Vector<int> vec_1 = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ(vec.size(), 6);
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec_1[i]);
  }
}

TEST(VectorTest, test_emplace_back_2) {
  s21::Vector<std::string> vec = {"Hello", "my"};
  s21::Vector<std::string> vec_1 = {"Hello", "my", "World", "!",
                                    "Hello", "my", "friend"};
  vec.insert_many_back("World", "!", "Hello", "my", "friend");
  EXPECT_EQ(vec.size(), 7);
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec[i], vec_1[i]);
  }
}

//--------------------------------------------------------------------
// insert_many()
//--------------------------------------------------------------------
TEST(VectorTest, test_emplace_1) {
  s21::Vector<int> v{1, 2, 3, 4, 5};
  auto it = v.insert_many(v.begin() + 2, 6);
  EXPECT_EQ(*it, 6);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[2], 6);
  EXPECT_EQ(v[3], 3);
}
TEST(VectorTest, test_emplace_2) {
  s21::Vector<int> v{1, 2, 3, 4, 5};
  auto it = v.insert_many(v.begin() + 5, 6);
  EXPECT_EQ(*it, 6);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[5], 6);
}

TEST(VectorTest, test_emplace_3) {
  s21::Vector<int> v{1, 2, 3, 4, 5};
  auto it = v.insert_many(v.begin(), 0);
  EXPECT_EQ(*it, 0);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[0], 0);
}

TEST(VectorTest, test_emplace_4) {
  s21::Vector<std::string> v{"hello", "world"};
  auto it = v.insert_many(v.begin() + 1, "there");
  EXPECT_EQ(*it, "there");
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[1], "there");
}

TEST(VectorTest, test_emplace_5) {
  s21::Vector<int> v{1, 2, 3, 4, 5};
  auto it = v.insert_many(v.begin() + 2, -10);
  EXPECT_EQ(*it, -10);
  EXPECT_EQ(v.size(), 6);
  EXPECT_EQ(v[2], -10);
}

TEST(VectorTest, test_emplace_7) {
  s21::Vector<std::string> v{"hello", "world"};

  auto it = v.insert_many(
      v.begin() + 1,
      "this is a very long string that we want to insert into the vector");

  EXPECT_EQ(
      *it, "this is a very long string that we want to insert into the vector");
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], "hello");
  EXPECT_EQ(
      v[1],
      "this is a very long string that we want to insert into the vector");
  EXPECT_EQ(v[2], "world");
}

TEST(VectorTest, test_emplace_8) {
  s21::Vector<std::string> v{"hello", "world"};
  auto it =
      v.insert_many(v.begin() + 1, "this", "is", "a", "list", "of", "words");

  EXPECT_EQ(v.size(), 8);
  EXPECT_EQ(*it, "words");
  EXPECT_EQ(v[0], "hello");
  EXPECT_EQ(v[1], "this");
  EXPECT_EQ(v[2], "is");
  EXPECT_EQ(v[3], "a");
  EXPECT_EQ(v[4], "list");
  EXPECT_EQ(v[5], "of");
  EXPECT_EQ(v[6], "words");
  EXPECT_EQ(v[7], "world");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
