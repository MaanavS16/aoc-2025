#include <chrono>
#include <iostream>

void print_board(std::vector<std::string> const& input) {
  for (auto const& row : input) {
    std::cout << row << '\n';
  }
  std::cout << "============================================\n";
}

auto solve(std::vector<std::string>& input) {
  int64_t result = 0;

  using coord_t = std::pair<std::size_t, std::size_t>;
  std::vector<coord_t> process_queue;

  auto const get_adj = [&input](int i, int j) {
    std::vector<coord_t> adj;

    if (i > 0 && j > 0 && input[i - 1][j - 1] == '@')
      adj.push_back({i - 1, j - 1});
    if (i > 0 && input[i - 1][j] == '@')
      adj.push_back({i - 1, j});
    if (i > 0 && j + 1 < input[0].size() && input[i - 1][j + 1] == '@')
      adj.push_back({i - 1, j + 1});

    if (j > 0 && input[i][j - 1] == '@')
      adj.push_back({i, j - 1});
    if (j + 1 < input[0].size() && input[i][j + 1] == '@')
      adj.push_back({i, j + 1});

    if (i + 1 < input.size() && j > 0 && input[i + 1][j - 1] == '@')
      adj.push_back({i + 1, j - 1});
    if (i + 1 < input.size() && input[i + 1][j] == '@')
      adj.push_back({i + 1, j});
    if (i + 1 < input.size() && j + 1 < input[0].size() && input[i + 1][j + 1] == '@')
      adj.push_back({i + 1, j + 1});

    return adj;
  };

  auto const get_blocked_count = [&input, &get_adj](int i, int j) {
    auto const adj = get_adj(i, j);
    return std::reduce(adj.begin(), adj.end(), 0, [&input](int total, auto const& coord) {
      return total + static_cast<int>(input[coord.first][coord.second] == '@');
    });
  };

  for (auto i = 0u; i < input.size(); ++i) {
    for (auto j = 0u; j < input[0].size(); ++j) {
      if (input[i][j] == '@') {
        if (get_blocked_count(i, j) < 4) {
          process_queue.push_back({i, j});
        }
      }
    }
  }

  while (!process_queue.empty()) {
    auto const [i, j] = process_queue.back();
    process_queue.pop_back();
    if (input[i][j] == 'x') {
      continue;
    }
    input[i][j] = 'x';
    ++result;
    // print_board(input);
    for (auto const& [ai, aj] : get_adj(i, j)) {
      if (get_blocked_count(ai, aj) < 4) {
        process_queue.push_back({ai, aj});
      }
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
