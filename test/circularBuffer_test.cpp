#include "circularBuffer.hpp"

#include <bits/stdc++.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
class CircularBufferTest : public ::testing::Test {
public:
  // Sets up the test fixture.
  void SetUp() override{

  };

  // Tears down the test fixture.
  void TearDown() override{

  };
};
TEST_F(CircularBufferTest, TEST_PUSH_Normal) {
  CircularBuffer<int, 5> circular;
  std::vector<int> Expected_value{0, 1, 2};
  std::vector<int> result;
  for (int i = 0; i < 3; i++) {
    circular.push_back(i);
  }
  while (!circular.empty()) {
    result.push_back(circular.head());
    circular.pop();
  }
  EXPECT_EQ(result, Expected_value);
}
TEST_F(CircularBufferTest, TEST_PUSH_POP) {
  CircularBuffer<int, 5> circular;

  std::vector<int> Expected_value{6, 7, 8, 9, 10};
  std::vector<int> result;
  for (int i = 0; i <= 10; i++) {
    circular.push_back(i);
  }
  while (!circular.empty()) {
    result.push_back(circular.head());
    circular.pop();
  }
  EXPECT_EQ(result, Expected_value);
}
TEST_F(CircularBufferTest, TEST_POP_THROW) {
  CircularBuffer<int, 5> circular;
  std::vector<int> Expected_value{5, 6, 7, 8, 9};
  std::vector<int> result;
  for (int i = 0; i < 10; i++) {
    circular.push_back(i);
  }
  while (!circular.empty()) {
    result.push_back(circular.head());
    circular.pop();
  };
  EXPECT_THROW(circular.pop(), std::runtime_error);
}
TEST_F(CircularBufferTest, TEST_EMPTY) {
  CircularBuffer<int, 5> circular;
  EXPECT_TRUE(circular.empty());
  std::vector<int> result;
  for (int i = 0; i < 10; i++) {
    circular.push_back(i);
  }
  EXPECT_FALSE(circular.empty());
}
TEST_F(CircularBufferTest, TEST_size) {
  CircularBuffer<int, 5> circular;
  EXPECT_EQ(circular.getsize(), 0);
  std::vector<int> result;
  for (int i = 0; i < 3; i++) {
    circular.push_back(i);
  }
  EXPECT_EQ(circular.getsize(), 3);
}
TEST_F(CircularBufferTest, Test_iterator) {
  CircularBuffer<int, 5> circular;
  for (int i = 0; i < 3; i++) {
    circular.push_back(i);
  }
  auto first = circular.begin();
  EXPECT_EQ(*first, 0);
  EXPECT_EQ(*++first, 1);
  EXPECT_EQ(*++first, 2);
}
TEST_F(CircularBufferTest, Test_iterator_range) {
  CircularBuffer<int, 5> circular;
  std::array<int, 5> expected_value{6, 7, 8, 9, 10};
  for (int i = 0; i <= 10; i++) {
    circular.push_back(i);
  }
  int i = 0;
  for (auto v : circular) {
    EXPECT_EQ(v, expected_value[i]);
    i++;
    std::cout << v << std::endl;
  }
}
