#include "dina.h"

extern "C" {
void add(int a, int b, int* res);
void sum_numbers(const int* numbers, std::size_t len, int* res);
}

namespace algo {

int Algorithms::add(int a, int b) const {
  int res{0};
  ::add(a, b, &res);
  return res;
}

void Algorithms::add_async(int a, int b, std::function<void(int)> callback) {
  int res = add(a, b);
  callback(res);
}

int Algorithms::sum(const std::vector<int>& numbers) const {
  int res{0};
  sum_numbers(numbers.data(), numbers.size(), &res);
  return res;
}

std::map<char, int> Algorithms::group_by_symbol(std::string_view word) const {
  std::map<char, int> result{};
  for (char s : word) {
    if (result.contains(s)) {
      result[s]++;
    } else {
      result[s] = 1;
    }
  }
  return result;
}

}  // namespace algo