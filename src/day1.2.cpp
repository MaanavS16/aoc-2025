#include <charconv>
#include <chrono>
#include <iostream>

inline long long mod(long long k, long long n) { return ((k % n) + n) % n; }

auto solve(std::vector<std::string> const &input) {
  int rot;
  int cursor = 50;
  int result = 0;

  for (auto const &line : input) {
    auto const rot_view = line.substr(1, line.size() - 1);
    std::from_chars(rot_view.data(), rot_view.data() + rot_view.size(), rot);

    if (line[0] == 'R') {
      auto const dist = 100 - cursor;
      auto const crosses =
          static_cast<int>(std::floor((rot - dist) / 100.0f)) + 1;
      result += crosses;
      if (dist == 0) {
        --result;
      }
      cursor = mod(cursor + rot, 100);
    } else {
      auto const dist = cursor;
      auto const crosses =
          static_cast<int>(std::floor((rot - dist) / 100.0f)) + 1;
      result += crosses;
      if (dist == 0) {
        --result;
      }
      cursor = mod(cursor - rot, 100);
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
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                       .count() /
                   lines.size()
            << "ns per line\n";
  return 0;
}
