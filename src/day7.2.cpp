#include <chrono>
#include <iostream>
#include <map>

void print(std::vector<std::string> const& input) {
  for (auto const& line : input) {
    std::cout << line << '\n';
  }
  std::cout << "===================\n";
}

auto solve(std::vector<std::string>& input) {
  uint64_t result = 0;

  using coord_t = std::pair<int, int>;

  std::deque<coord_t> queue;
  std::map<coord_t, uint64_t> memo;
  for (auto i = 0; i < input[0].size(); ++i) {
    if (input[0][i] == 'S') {
      queue.push_back({0, i});
      memo[{0, i}] = 1;
    }
  }

  while (!queue.empty()) {
    auto const [i, j] = queue.front();
    queue.pop_front();

    if (i == input.size()) {
      result += memo[{i, j}];
      continue;
    }

    if (input[i][j] == '|') {
      continue;
    }
    input[i][j] = '|';

    if (input[i + 1][j] == '^') {
      queue.push_back({i + 1, j - 1});
      queue.push_back({i + 1, j + 1});
      memo[{i + 1, j - 1}] += memo[{i, j}];
      memo[{i + 1, j + 1}] += memo[{i, j}];
    } else {
      queue.push_back({i + 1, j});
      memo[{i + 1, j}] += memo[{i, j}];
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
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
  return 0;
}
