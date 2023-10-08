#include "../s21_array.h"

#include <gtest/gtest.h>

TEST(ArrayTest, DefaultConstructor) {
  s21::Array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, DefaultConstructorLargeArray) {
  s21::Array<int, 1000> arr;
  EXPECT_EQ(arr.size(), 1000);
}

TEST(ArrayTest, DefaultConstructorChar) {
  s21::Array<char, 3> arr;
  EXPECT_EQ(arr.size(), 3);
}

TEST(ArrayTest, DefaultConstructorDouble) {
  s21::Array<double, 4> arr;
  EXPECT_EQ(arr.size(), 4);
}

TEST(ArrayTest, BeginTest) {
  s21::Array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.begin(), static_cast<void*>(&arr));
  EXPECT_EQ(*arr.begin(), 1);
  *arr.begin() = 6;
  EXPECT_EQ(arr[0], 6);
}

TEST(ArrayTest, StringBeginTest) {
  s21::Array<std::string, 3> arr{"foo", "bar", "baz"};
  EXPECT_EQ(arr.begin(), static_cast<void*>(&arr));
  EXPECT_EQ(*arr.begin(), "foo");
  *arr.begin() = "qux";
  EXPECT_EQ(arr[0], "qux");
}

TEST(ArrayTest, StringEndTest) {
  s21::Array<std::string, 3> arr{"foo", "bar", "baz"};
  EXPECT_EQ(*(arr.end() - 1), arr[2]);
  EXPECT_EQ(*(arr.end() - 1), "baz");
  *(arr.end() - 1) = "qux";
  EXPECT_EQ(arr[2], "qux");
}

TEST(ArrayTest, DoubleEndTest) {
  s21::Array<double, 5> arr{1.1, 2.2, 3.3, 4.4, 5.5};
  EXPECT_EQ(*(arr.end() - 1), arr[4]);
  EXPECT_EQ(*(arr.end() - 1), 5.5);
  *(arr.end() - 1) = 6.6;
  EXPECT_EQ(arr[4], 6.6);
}

TEST(ArrayTest, MaxSizeTest) {
  s21::Array<int, 5> arr;
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::Array<int, 5> int_arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> int_arr2 = {6, 7, 8, 9, 10};
  int_arr1 = std::move(int_arr2);
  EXPECT_EQ(int_arr1[0], 6);
  EXPECT_EQ(int_arr1[4], 10);

  s21::Array<double, 3> double_arr1 = {1.1, 2.2, 3.3};
  s21::Array<double, 3> double_arr2 = {4.4, 5.5, 6.6};
  double_arr1 = std::move(double_arr2);
  EXPECT_DOUBLE_EQ(double_arr1[0], 4.4);
  EXPECT_DOUBLE_EQ(double_arr1[2], 6.6);

  struct Person {
    std::string name;
    int age;
  };

  s21::Array<Person, 2> person_arr1 = {{"Alice", 30}, {"Bob", 40}};
  s21::Array<Person, 2> person_arr2 = {{"Charlie", 50}, {"David", 60}};
  person_arr1 = std::move(person_arr2);
  EXPECT_EQ(person_arr1[0].name, "Charlie");
  EXPECT_EQ(person_arr1[1].age, 60);

  s21::Array<int, 1> one_element_arr1 = {1};
  s21::Array<int, 1> one_element_arr2 = {2};
  one_element_arr1 = std::move(one_element_arr2);
  EXPECT_EQ(one_element_arr1[0], 2);
}

TEST(ArrayTest, AssignmentOperatorInt) {
  s21::Array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::Array<int, 5> arr2 = {6, 7, 8, 9, 10};
  arr1 = arr2;
  EXPECT_EQ(arr1[0], 6);
  EXPECT_EQ(arr1[1], 7);
  EXPECT_EQ(arr1[2], 8);
  EXPECT_EQ(arr1[3], 9);
  EXPECT_EQ(arr1[4], 10);
}

TEST(ArrayTest, AssignmentOperatorDouble) {
  s21::Array<double, 3> arr1 = {1.0, 2.0, 3.0};
  s21::Array<double, 3> arr2 = {4.0, 5.0, 6.0};
  arr1 = arr2;
  EXPECT_DOUBLE_EQ(arr1[0], 4.0);
  EXPECT_DOUBLE_EQ(arr1[1], 5.0);
  EXPECT_DOUBLE_EQ(arr1[2], 6.0);
}

TEST(ArrayTest, AssignmentOperatorChar) {
  s21::Array<char, 4> arr1 = {'a', 'b', 'c', 'd'};
  s21::Array<char, 4> arr2 = {'e', 'f', 'g', 'h'};
  arr1 = arr2;
  EXPECT_EQ(arr1[0], 'e');
  EXPECT_EQ(arr1[1], 'f');
  EXPECT_EQ(arr1[2], 'g');
  EXPECT_EQ(arr1[3], 'h');
}

TEST(ArrayTest, AssignmentOperatorString) {
  s21::Array<std::string, 2> arr1 = {"hello", "world"};
  s21::Array<std::string, 2> arr2 = {"foo", "bar"};
  arr1 = arr2;
  EXPECT_EQ(arr1[0], "foo");
  EXPECT_EQ(arr1[1], "bar");
}

TEST(ArrayTest, EmptyArrayTest) {
  s21::Array<int, 5> arr;
  EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, NonEmptyArrayTest) {
  s21::Array<int, 3> arr = {1, 2, 3};
  EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, ClearArrayTest) {
  s21::Array<int, 3> arr = {1, 2, 3};
  // arr3.clear();
  // EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, FillIntArrayTest) {
  s21::Array<int, 5> arr;
  arr.fill(42);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 42);
  }
}

TEST(ArrayTest, FillDoubleArrayTest) {
  s21::Array<double, 5> arr;
  arr.fill(3.14);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_DOUBLE_EQ(arr[i], 3.14);
  }
}

TEST(ArrayTest, FillBoolArrayTest) {
  s21::Array<bool, 5> arr;
  arr.fill(true);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_TRUE(arr[i]);
  }
}

TEST(ArrayTest, FillSingleIntArrayTest) {
  s21::Array<int, 1> arr;
  arr.fill(42);
  EXPECT_EQ(arr[0], 42);
}

TEST(ArrayTest, FillMultipleIntArrayTest) {
  s21::Array<int, 3> arr;
  arr.fill(42);
  EXPECT_EQ(arr[0], 42);
  EXPECT_EQ(arr[1], 42);
  EXPECT_EQ(arr[2], 42);
}

TEST(ArrayTest, SwapTest) {
  s21::Array<int, 3> arr3 = {7, 8, 9};
  s21::Array<int, 3> arr4 = {10, 11, 12};
  arr3.swap(arr4);
  EXPECT_EQ(arr3[0], 10);
  EXPECT_EQ(arr3[1], 11);
  EXPECT_EQ(arr3[2], 12);
  EXPECT_EQ(arr4[0], 7);
  EXPECT_EQ(arr4[1], 8);
  EXPECT_EQ(arr4[2], 9);
}

TEST(ArrayTest, SelfSwapTest) {
  s21::Array<int, 3> arr = {1, 2, 3};
  arr.swap(arr);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(DataTest, Array) {
  s21::Array<int, 5> arr = {1, 2, 3, 4, 5};
  int* ptr = arr.data();
  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_EQ(*(ptr + i), i + 1);
  }
}

TEST(BackTest, Array) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  const int& last_element = arr.back();
  EXPECT_EQ(last_element, 5);
}

TEST(FrontTest, Array) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  const int& first_element = arr.front();
  EXPECT_EQ(first_element, 1);
}

TEST(AtTest, Array) {
  std::array<int, 5> arr{1, 2, 3, 4, 5};
  int& element = arr.at(2);
  EXPECT_EQ(element, 3);
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }