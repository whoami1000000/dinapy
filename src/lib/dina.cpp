#include "dina.h"

#include <future>
#include <thread>

#include "log/logging.h"

extern "C" {
void add(int a, int b, int* res);
void sum_numbers(const int* numbers, std::size_t len, int* res);
void factorial(std::int64_t n, std::int64_t* res);
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
    // if (result.contains(s)) {
    if (result.find(s) != result.end()) {
      result[s]++;
    } else {
      result[s] = 1;
    }
  }
  return result;
}

std::int64_t Algorithms::factorial(std::int64_t n) const {
  auto tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
  spdlog::debug("factorial({}) started at [thread={}]", n, tid);

  std::this_thread::sleep_for(std::chrono::seconds{n});

  std::int64_t res{0};
  ::factorial(n, &res);

  spdlog::debug("factorial({}) finished at [thread={}] with [result={}]", n, tid, res);

  return res;
}

std::vector<std::int64_t> Algorithms::factorial_parallel(const std::vector<std::int64_t>& values) {
  std::vector<std::future<std::int64_t>> futures;
  futures.reserve(values.size());

  for (auto n : values) {
    auto fut = std::async(std::launch::async, &Algorithms::factorial, this, n);
    futures.push_back(std::move(fut));
  }

  std::vector<std::int64_t> results;
  results.reserve(values.size());
  for (auto& f : futures) {
    results.push_back(f.get());
  }

  return results;
}

void Algorithms::factorial_async(std::int64_t n, std::function<void(const FactorialResult&)> callback) {
  auto f = [this, n, callback = std::move(callback)]() {
    auto res = factorial(n);
    if (callback) {
      FactorialResult fr{};
      fr.n = n;
      fr.result = res;
      fr.comment = "Everything is good";
      callback(fr);
    }
  };

  std::thread{std::move(f)}.detach();
}

}  // namespace algo