#include <gtest/gtest.h>

#include "lib/dina.h"

TEST(Algo, Add) {
  algo::Algorithms a{};
  ASSERT_EQ(a.add(1, 2), 3);
}

TEST(Algo, Sum) {
  algo::Algorithms a{};
  ASSERT_EQ(a.sum({1, 2, 3, 4}), 10);
}

TEST(Algo, GroupBy) {
  algo::Algorithms a{};
  auto res = a.group_by_symbol("ololo");
  decltype(res) expected{{'o', 3}, {'l', 2}};
  ASSERT_EQ(res, expected);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}