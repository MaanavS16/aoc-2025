#include <algorithm>
#include <chrono>
#include <ios>
#include <iostream>
#include <queue>
#include <ranges>

using range_t = std::pair<int64_t, int64_t>;

auto solve(std::vector<range_t> const& ranges) {
  std::priority_queue<range_t, std::vector<range_t>, std::greater<range_t>> pq{ranges.begin(), ranges.end()};
  int64_t result = 0;

  while (!pq.empty()) {
    auto const [l, r] = pq.top();
    pq.pop();
    int64_t true_r = r;
    while (!pq.empty() && pq.top().first <= true_r) {
      true_r = std::max(true_r, pq.top().second);
      pq.pop();
    }
    result += true_r - l + 1;
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::vector<range_t> ranges{};
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "") {
      break;
    }

    auto subrange = std::string_view(line) | std::views::split('-');
    auto it = subrange.begin();
    std::pair<int64_t, int64_t> rs;

    auto first_begin = std::ranges::begin(*it);
    auto first_end = std::ranges::end(*it);
    std::from_chars(first_begin, first_end, rs.first);
    ++it;
    auto second_begin = std::ranges::begin(*it);
    auto second_end = std::ranges::end(*it);
    std::from_chars(second_begin, second_end, rs.second);

    ranges.push_back(rs);
  }

  auto const start = std::chrono::steady_clock::now();
  auto const ans = solve(ranges);
  auto const end = std::chrono::steady_clock::now();
  std::cout << ans << '\n';
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
  return 0;
}
