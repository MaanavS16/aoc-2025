#include <chrono>
#include <iostream>

auto solve(std::vector<std::string> const &input) {
  int64_t result = 0;

  for (auto const &bank : input) {
    std::pair<int, int> b1{bank[0] - '0', 0};
    std::pair<int, int> b2;

    for (std::size_t i = 0; i < bank.size() - 1; ++i) {
      if (bank[i] - '0' > b1.first) {
        b1 = std::make_pair(bank[i] - '0', i);
      }
    }

    b2 = std::make_pair(bank[b1.second + 1] - '0', b1.second + 1);
    for (std::size_t i = b1.second + 1; i < bank.size(); ++i) {
      if (bank[i] - '0' > b2.first) {
        b2 = std::make_pair(bank[i] - '0', i);
      }
    }

    auto const jolts = b1.first * 10 + b2.first;
    std::cout << std::format("bank={} jolts={}\n", bank, jolts);
    result += jolts;
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
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                   .count()
            << "ns\n";
  return 0;
}
