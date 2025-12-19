#include <chrono>
#include <cmath>
#include <iostream>
#include <ranges>
#include <utility>

auto solve(std::vector<std::pair<int64_t, int64_t>> const &input) {

  long long res = 0;

  const auto lil_elf_bro_involved = [](auto const id) {
    std::size_t const len = std::ceil(std::log10(id));

    if (len % 2 == 1) {
      return false;
    }

    auto ms_id = id;
    for (std::size_t i = 0; i < len / 2; ++i) {
      ms_id /= 10;
    }

    return (id - std::pow(10, len / 2) * ms_id) == ms_id;
  };

  for (auto const &[r1, r2] : input) {
    for (std::size_t n = r1; n <= r2; ++n) {
      if (lil_elf_bro_involved(n)) {
        res += n;
      }
    }
  }
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::vector<std::pair<int64_t, int64_t>> lines{};
  std::string line;
  std::cin >> line;

  auto line_view = std::string_view(line);

  for (auto const &rng : (line_view | std::views::split(','))) {
    auto subrange = rng | std::views::split('-');
    auto it = subrange.begin();
    std::pair<int64_t, int64_t> rs;

    auto first_begin = std::ranges::begin(*it);
    auto first_end = std::ranges::end(*it);
    std::from_chars(first_begin, first_end, rs.first);
    ++it;
    auto second_begin = std::ranges::begin(*it);
    auto second_end = std::ranges::end(*it);
    std::from_chars(second_begin, second_end, rs.second);

    lines.push_back(rs);
  }

  auto const start = std::chrono::steady_clock::now();
  auto const ans = solve(lines);
  auto const end = std::chrono::steady_clock::now();
  std::cout << ans << '\n';
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                     start)
                   .count()
            << "us\n";
  return 0;
}
