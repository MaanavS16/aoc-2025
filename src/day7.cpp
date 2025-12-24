#include <chrono>
#include <iostream>

void print(std::vector<std::string> const& input) {
  for (auto const& line : input) {
    std::cout << line << '\n';
  }
  std::cout << "===================\n";
}

auto solve(std::vector<std::string>& input) {
  int result = 0;

  using coord_t = std::pair<int, int>;

  std::vector<coord_t> queue;
  for (auto i = 0; i < input[0].size(); ++i) {
    if (input[0][i] == 'S') {
      queue.push_back({0, i});
    }
  }

  while (!queue.empty()) {
    auto const [i, j] = queue.back();
    queue.pop_back();

    if (input[i][j] == '|' || i == input.size()) {
      continue;
    }
    input[i][j] = '|';

    if (input[i + 1][j] == '.') {
      queue.push_back({i + 1, j});
    } else if (input[i + 1][j] == '^') {
      result++;
      queue.push_back({i, j - 1});
      queue.push_back({i, j + 1});
    }
  }
  print(input);

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
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / lines.size()
            << "ns per line\n";
  return 0;
}
