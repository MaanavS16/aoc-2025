#include <algorithm>
#include <chrono>
#include <ios>
#include <iostream>
#include <ranges>
#include <utility>

using coord_t = std::array<int64_t, 2>;
bool conflict(coord_t c1, coord_t c2, coord_t x1, coord_t x2) {
  const int64_t minx = std::min(c1[0], c2[0]), maxx = std::max(c1[0], c2[0]);
  const int64_t miny = std::min(c1[1], c2[1]), maxy = std::max(c1[1], c2[1]);

  bool result = false;
  if (x1[0] == x2[0]) {
    const int64_t x = x1[0];
    const int64_t y0 = std::min(x1[1], x2[1]);
    const int64_t y1 = std::max(x1[1], x2[1]);
    result = (minx < x && x < maxx && std::max(y0, miny) < std::min(y1, maxy));
  }

  if (x1[1] == x2[1]) {
    const int64_t y = x1[1];
    const int64_t x0 = std::min(x1[0], x2[0]);
    const int64_t x1_ = std::max(x1[0], x2[0]);
    result = (miny < y && y < maxy && std::max(x0, minx) < std::min(x1_, maxx));
  }
  return result;
}

auto solve(std::vector<coord_t> const& input) {
  int64_t ans = 0;
  for (auto i = 0u; i < input.size(); ++i) {
    for (auto j = 0u; j < i; ++j) {
      bool valid = true;
      for (auto k = 1; k <= input.size(); ++k) {
        if (conflict(input[i], input[j], input[k - 1], input[k % input.size()])) {
          valid = false;
          break;
        }
      }
      if (valid) {
        auto const dist = (std::abs(input[i][0] - input[j][0]) + 1) * (1 + std::abs(input[i][1] - input[j][1]));
        ans = std::max(ans, dist);
      }
    }
  }
  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::vector<coord_t> lines{};
  std::string line;
  while (std::cin >> line) {
    auto line_view = std::string_view(line);
    auto subrange = line_view | std::views::split(',');
    auto it = subrange.begin();

    coord_t coord;
    for (auto i = 0u; i < std::tuple_size<coord_t>::value; ++i) {
      auto bgn = std::ranges::begin(*it);
      auto end = std::ranges::end(*it);
      std::from_chars(bgn, end, coord[i]);
      ++it;
    }
    lines.push_back(coord);
  }
  auto const start = std::chrono::steady_clock::now();
  auto const ans = solve(lines);
  auto const end = std::chrono::steady_clock::now();
  std::cout << "ans: " << ans << '\n';
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
  return 0;
}
