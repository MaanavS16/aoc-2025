#include <chrono>
#include <ios>
#include <iostream>
#include <ranges>

auto solve(std::vector<std::pair<int64_t, int64_t>> const& ranges, std::vector<int64_t> const& ingredients) {
  int64_t result = 0;

  for (auto const& ingredient : ingredients) {
    bool fresh = false;

    for (auto [a, b] : ranges) {
      if (ingredient >= a && ingredient <= b) {
        fresh = true;
        break;
      }
    }
    result += static_cast<int>(fresh);
  }

  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::vector<std::pair<int64_t, int64_t>> ranges{};
  std::vector<int64_t> ingredients{};
  std::string line;
  bool z = false;
  while (std::getline(std::cin, line)) {
    if (line == "") {
      z = true;
      continue;
    }

    if (z) {
      ingredients.push_back(std::stoll(line));
    } else {
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
  }

  auto const start = std::chrono::steady_clock::now();
  auto const ans = solve(ranges, ingredients);
  auto const end = std::chrono::steady_clock::now();
  std::cout << ans << '\n';
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
  return 0;
}
