#include <chrono>
#include <iostream>

auto solve(std::vector<std::string> const &input) {
  int64_t result = 0;

  for (auto const &bank : input) {
    std::pair<int, int> prev_battery{0, -1};
    int64_t curr_jolts = 0;

    static constexpr auto TOTAL_BATTERIES = 12;

    for (std::size_t i = 0; i < TOTAL_BATTERIES; ++i) {
      std::pair<int, int> curr_battery{bank[prev_battery.second + 1] - '0',
                                       prev_battery.second + 1};

      for (std::size_t j = prev_battery.second + 1;
           j < bank.size() - (TOTAL_BATTERIES - i - 1); ++j) {
        if (bank[j] - '0' > curr_battery.first) {
          curr_battery = std::make_pair(bank[j] - '0', j);
        }
      }

      curr_jolts += curr_battery.first * std::pow(10, TOTAL_BATTERIES - i - 1);
      prev_battery = curr_battery;
    }

    std::cout << std::format("bank={} jolts={}\n", bank, curr_jolts);
    result += curr_jolts;
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
