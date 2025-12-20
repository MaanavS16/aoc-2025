#include <chrono>
#include <iostream>

auto solve(std::vector<std::string> const& input) {
  int64_t result = 0;

  auto const is_reachable = [&input](int i, int j) {
    int blocked = 0;
    blocked += static_cast<int>(i > 0 && j > 0 && input[i - 1][j - 1] == '@');
    blocked += static_cast<int>(i > 0 && input[i - 1][j] == '@');
    blocked += static_cast<int>(i > 0 && j + 1 < input[0].size() && input[i - 1][j + 1] == '@');

    blocked += static_cast<int>(j > 0 && input[i][j - 1] == '@');
    blocked += static_cast<int>(j + 1 < input[0].size() && input[i][j + 1] == '@');

    blocked += static_cast<int>(i + 1 < input.size() && j > 0 && input[i + 1][j - 1] == '@');
    blocked += static_cast<int>(i + 1 < input.size() && input[i + 1][j] == '@');
    blocked += static_cast<int>(i + 1 < input.size() && j + 1 < input[0].size() && input[i + 1][j + 1] == '@');

    return blocked < 4;
  };

  for (auto i = 0u; i < input.size(); ++i) {
    for (auto j = 0u; j < input[0].size(); ++j) {
      if (input[i][j] == '@')
        result += is_reachable(i, j);
    }
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::vector<std::string> lines{};
  std::string line;
  while (std::cin >> line) {
    lines.emplace_back(std::move(line));
  }

  auto const start = std::chrono::steady_clock::now();
  auto const ans = solve(lines);
  auto const end = std::chrono::steady_clock::now();
  std::cout << ans << '\n';
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
  return 0;
}
