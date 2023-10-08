#include "../s21_map.h"

#include <gtest/gtest.h>

#include <map>

TEST(map_test, constructorInit) {
  s21::Map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
  it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1).first, (*it2).first);
  EXPECT_EQ(m1.Size(), m2.size());
}

TEST(map_test, constructorEmpty) {
  s21::Map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.Size(), m2.size());
  m1.insert({1, 1});
  m2.insert({1, 1});
  EXPECT_EQ(m1.Size(), m2.size());
}

TEST(map_test, constructorCopy) {
  s21::Map<int, int> m1({{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}});
  s21::Map<int, int> m2(m1);
  EXPECT_EQ(m1.Size(), m2.Size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(map_test, constructorCopy2) {
  s21::Map<int, int> m1 = {{5, 5}, {4, 4}, {1, 1}, {2, 2}, {3, 3}};
  s21::Map<int, int> m2(m1);
  EXPECT_EQ(m1.Size(), m2.Size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1), (*it2));
}

TEST(map_test, constructorCopy3) {
  s21::Map<int, int> m1 = {{5, 5}, {4, 4}, {1, 1}, {2, 2}, {3, 3}};
  s21::Map<int, int> m2 = m1;
  EXPECT_EQ(m1.Size(), m2.Size());
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
}

TEST(map_test, constructorMove) {
  s21::Map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::Map<int, int> m3 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::Map<int, int> m2 = std::move(m1);
  std::cout << m1.Size() << std::endl;
  EXPECT_EQ(m1.Size(), 0);
  auto it1 = m2.begin();
  for (auto it2 = m3.begin(); it2 != m3.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(map_test, Max_size) {
  s21::Map<int, int> m1 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {1, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(map_test, at1) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  for (size_t i = 1; i < m1.Size(); i++) EXPECT_EQ(m1.at(i), m2.at(i));
}

TEST(map_test, begin) {
  s21::Map<int, int> m1 = {{1, 1}};
  std::map<int, int> m2 = {{1, 1}};
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(map_test, emptyFalse) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map_test, emptyTrue) {
  s21::Map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map_test, size) {
  s21::Map<int, int> m1;
  std::map<int, int> m2;
  std::pair<int, int> pair = {3, 1};
  m1.insert(pair);
  m2.insert(pair);
  EXPECT_EQ(m1.Size(), m2.size());
}

TEST(map_test, size0) {
  s21::Map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_EQ(m1.Size(), m2.size());
}

TEST(map_test, clear) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.Size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map_test, clearEmpty) {
  s21::Map<int, int> m1;
  std::map<int, int> m2;
  m1.clear();
  m2.clear();
  EXPECT_EQ(m1.Size(), m2.size());
  EXPECT_EQ(m1.empty(), m2.empty());
}

TEST(map_test, insertPair) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::pair<int, int> pair = {6, 6};
  EXPECT_EQ(m1.insert(pair).second, m2.insert(pair).second);
  EXPECT_EQ(m1.Size(), m2.size());
}

TEST(map_test, insertInEmpty) {
  s21::Map<int, int> m1;
  std::map<int, int> m2;
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(m1.insert(pair).second, m2.insert(pair).second);
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.Size(), m2.size());
}

TEST(map_test, insertNumKey) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.empty(), m2.empty());
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(m1.insert(3, 1).second, m2.insert(pair).second);
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.Size(), m2.size());
}

TEST(map_test, insert_or_assign) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 4}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.empty(), m2.empty());
  m1.insert_or_assign(3, 4);
  EXPECT_EQ(m1.at(3), m2.at(3));
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.Size(), m2.size());
}

TEST(map_test, insert_or_assign2) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 4}};
  EXPECT_EQ(m1.empty(), m2.empty());
  m1.insert_or_assign(6, 4);
  EXPECT_EQ(m1.at(6), m2.at(6));
  EXPECT_EQ(m1.empty(), m2.empty());
  EXPECT_EQ(m1.Size(), m2.size());
}

TEST(map_test, swap) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::Map<int, int> m11;
  std::map<int, int> m22;
  m1.swap(m11);
  m2.swap(m22);
  EXPECT_EQ(m1.Size(), m2.size());
  EXPECT_EQ(m11.Size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(map_test, swapEmpty) {
  s21::Map<int, int> m1;
  std::map<int, int> m2;
  s21::Map<int, int> m11;
  std::map<int, int> m22;
  m1.swap(m11);
  m2.swap(m22);
  EXPECT_EQ(m1.Size(), m2.size());
  EXPECT_EQ(m11.Size(), m22.size());
  auto it1 = m11.begin();
  for (auto it2 = m22.begin(); it2 != m22.end(); it1++, it2++)
    EXPECT_EQ((*it1).second, (*it2).second);
}

TEST(map_test, containsTrue) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.contains(1), true);
}

TEST(map_test, containsFalse) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1.contains(0), false);
}

TEST(map_test, Merge2) {
  s21::Map<int, int> s1{{1, 1}, {2, 2}, {3, 3}, {4, 4},
                        {5, 5}, {6, 6}, {7, 7}, {8, 8}};
  s21::Map<int, int> s2{{9, 9}, {-1, -1}, {3, 3}};
  std::map<int, int> s3{{1, 1}, {2, 2}, {3, 3}, {4, 4},
                        {5, 5}, {6, 6}, {7, 7}, {8, 8}};
  std::map<int, int> s4{{9, 9}, {-1, -1}, {3, 3}};
  s1.merge(s2);
  s3.merge(s4);
  EXPECT_EQ(s1.Size(), s3.size());
}

TEST(map_test, Erase) {
  s21::Map<int, int> m1;
  m1.insert({1, 1});

  auto s_pr = m1.insert({2, 2});
  m1.erase(s_pr.first);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(map_test, Erase_Test_2) {
  s21::Map<int, int> m1 = {{60, 60}, {58, 58}, {63, 63}, {1, 1},
                           {59, 59}, {61, 61}, {65, 65}};
  std::map<int, int> m2 = {{60, 60}, {58, 58}, {63, 63}, {1, 1},
                           {59, 59}, {61, 61}, {65, 65}};

  auto it1 = m1.begin();
  auto it2 = m2.begin();
  m1.erase(it1);
  m2.erase(it2);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, Erase_Test_3) {
  s21::Map<int, int> m1 = {{60, 60}, {58, 58}, {63, 63}, {1, 1},
                           {59, 59}, {61, 61}, {65, 65}};
  std::map<int, int> m2 = {{60, 60}, {58, 58}, {63, 63}, {1, 1},
                           {59, 59}, {61, 61}, {65, 65}};

  auto pair1 = m1.insert(62, 62);
  auto it1 = pair1.first;
  auto it2 = m2.begin();
  m1.erase(it1);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, Erase_Test_4) {
  s21::Map<int, int> m1 = {{60, 60}, {63, 63}, {1, 1},
                           {61, 61}, {65, 65}, {62, 62}};
  std::map<int, int> m2 = {{60, 60}, {63, 63}, {1, 1},
                           {61, 61}, {65, 65}, {62, 62}};

  auto pair1 = m1.insert(58, 58);
  auto it1 = pair1.first;
  auto it2 = m2.begin();
  m1.erase(it1);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, Erase_Test_5) {
  s21::Map<int, int> m1 = {{10, 10}, {12, 12}};
  std::map<int, int> m2 = {{10, 10}, {12, 12}};

  auto it1 = m1.begin();
  auto it2 = m2.begin();
  m1.erase(it1);
  m2.erase(it2);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, Erase_Test_6) {
  s21::Map<int, int> m1 = {{60, 60}, {55, 55}, {63, 63}, {1, 1},
                           {61, 61}, {65, 65}, {62, 62}};
  std::map<int, int> m2 = {{60, 60}, {55, 55}, {63, 63}, {1, 1},
                           {61, 61}, {65, 65}, {62, 62}};

  auto pair1 = m1.insert(58, 58);
  auto it1 = pair1.first;
  auto it2 = m2.begin();
  m1.erase(it1);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, Erase_Test_7) {
  s21::Map<int, int> m1 = {{4, 4}, {2, 2}, {1, 1}};
  std::map<int, int> m2 = {{4, 4}, {1, 1}};

  auto it1 = m1.begin();
  auto it2 = m2.begin();
  it1++;
  m1.erase(it1);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, Erase_Test_8) {
  s21::Map<int, int> m1 = {{4, 4}, {2, 2}, {1, 1}, {3, 3}, {0, 0}};
  std::map<int, int> m2 = {{4, 4}, {1, 1}, {3, 3}, {0, 0}};

  auto it1 = m1.begin();
  auto it2 = m2.begin();
  it1++;
  it1++;
  m1.erase(it1);
  it1 = m1.begin();
  it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, MergeTest_3) {
  s21::Map<int, int> m1 = {{1, 1}};
  s21::Map<int, int> m2 = {{5, 5}, {1, 1}, {7, 7}, {2, 2}, {3, 3}};
  std::map<int, int> m3 = {{1, 1}};
  std::map<int, int> m4 = {{5, 5}, {1, 1}, {7, 7}, {2, 2}, {3, 3}};

  m1.merge(m2);
  m3.merge(m4);
  auto it1 = m1.begin();
  auto it2 = m3.begin();
  for (; it1 != m1.end() && it2 != m3.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, MergeTest_4) {
  s21::Map<int, int> m1 = {{1, 1}, {0, 0}};
  s21::Map<int, int> m2 = {{5, 5}, {2, 2}, {7, 7}, {0, 0},
                           {3, 3}, {6, 6}, {9, 9}, {10, 10}};
  std::map<int, int> m3 = {{1, 1}, {0, 0}};
  std::map<int, int> m4 = {{5, 5}, {2, 2}, {7, 7}, {0, 0},
                           {3, 3}, {6, 6}, {9, 9}, {10, 10}};

  m1.merge(m2);
  m3.merge(m4);
  auto it1 = m1.begin();
  auto it2 = m3.begin();
  for (; it1 != m1.end() && it2 != m3.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, MergeTest_5) {
  s21::Map<int, int> m1 = {{5, 5}, {2, 2}, {6, 6}};
  s21::Map<int, int> m2 = {{5, 5}, {2, 2}, {7, 7}, {0, 0},
                           {3, 3}, {6, 6}, {9, 9}, {10, 10}};
  std::map<int, int> m3 = {{5, 5}, {2, 2}, {6, 6}};
  std::map<int, int> m4 = {{5, 5}, {2, 2}, {7, 7}, {0, 0},
                           {3, 3}, {6, 6}, {9, 9}, {10, 10}};

  m1.merge(m2);
  m3.merge(m4);
  auto it1 = m1.begin();
  auto it2 = m3.begin();
  for (; it1 != m1.end() && it2 != m3.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, MergeTest_6) {
  s21::Map<int, int> m1 = {{10, 10}, {13, 13}, {15, 15}};
  s21::Map<int, int> m2 = {{10, 10}, {20, 20}, {15, 15}, {13, 13}, {25, 25}};
  std::map<int, int> m3 = {{10, 10}, {13, 13}, {15, 15}};
  std::map<int, int> m4 = {{10, 10}, {20, 20}, {15, 15}, {13, 13}, {25, 25}};
  m1.merge(m2);
  m3.merge(m4);
  auto it1 = m1.begin();
  auto it2 = m3.begin();
  for (; it1 != m1.end() && it2 != m3.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, Emplace_Test) {
  s21::Map<int, int> m1 = {{10, 10}, {13, 13}, {15, 15}};
  std::map<int, int> m2 = {{10, 10}, {13, 13}, {15, 15}};
  m1.insert_many(std::make_pair(5, 5));
  m2.emplace(std::make_pair(5, 5));
  auto it1 = m1.begin();
  auto it2 = m2.begin();
  for (; it1 != m1.end() && it2 != m2.end(); ++it1, ++it2)
    EXPECT_EQ((*it1).first, (*it2).first);
}

TEST(map_test, Emplace) {
  s21::Map<int, int> m1;
  m1.insert_many(std::make_pair(1, 1));
  EXPECT_EQ(m1.contains(1), true);
}

TEST(map_test, EraseOneChild) {
  s21::Map<int, int> m1{{1, 1}, {2, 2}, {3, 3}};
  auto it = m1.begin();
  it++;
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(map_test, EraseOneChild2) {
  s21::Map<int, int> m1{{2, 2}};
  auto it = m1.begin();
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(map_test, EraseTwoChild) {
  s21::Map<int, int> m1{{2, 2}, {1, 1}, {3, 3}};
  auto it = m1.begin();
  it++;
  m1.erase(it);
  EXPECT_EQ(m1.contains(2), false);
}

TEST(map_test, Operator) {
  s21::Map<int, int> m1 = {{1, 1}};
  s21::Map<int, int> m2 = m1;
  auto it1 = m1.begin();
  for (auto it2 = m2.begin(); it2 != m2.end(); it1++, it2++)
    EXPECT_EQ((*it1), (*it2));
}

TEST(map_test, operatorBrace) {
  s21::Map<int, int> m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> m2 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_EQ(m1[1], 1);
  EXPECT_EQ(m2[1], 1);
  EXPECT_EQ(m1[5], 5);
  EXPECT_EQ(m2[5], 5);
  EXPECT_EQ(m1[1], m2[1]);
  EXPECT_EQ(m1[3], m2[3]);
  EXPECT_EQ(m1[5], m2[5]);
  m1[10] = 10;
  m2[10] = 10;
  m1.at(10) = 5;
  m2.at(10) = 5;
  EXPECT_EQ(m1.at(10), m2.at(10));
}
