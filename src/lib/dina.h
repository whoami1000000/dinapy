#pragma once

#include <functional>
#include <map>
#include <string_view>
#include <vector>

namespace algo {

class Algorithms final {
 public:
  [[nodiscard]] int add(int a, int b) const;
  void add_async(int a, int b, std::function<void(int)> callback);
  [[nodiscard]] int sum(const std::vector<int>& numbers) const;
  [[nodiscard]] std::map<char, int> group_by_symbol(std::string_view word) const;
  [[nodiscard]] std::int64_t factorial(std::int64_t n) const;
  std::vector<std::int64_t> factorial_parallel(const std::vector<std::int64_t>& values);
  void factorial_async(std::int64_t n, std::function<void(std::int64_t)> callback);
};

}  // namespace algo
