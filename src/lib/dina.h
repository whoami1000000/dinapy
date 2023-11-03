#pragma once

#include <map>
#include <string_view>
#include <vector>
#include <functional>

namespace algo {

class Algorithms final {
 public:
  int add(int a, int b) const;
  void add_async(int a, int b, std::function<void(int)> callback);
  int sum(const std::vector<int>& numbers) const;
  std::map<char, int> group_by_symbol(std::string_view word) const;
};

}  // namespace algo
