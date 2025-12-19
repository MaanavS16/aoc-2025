#include <charconv>
#include <chrono>
#include <format>
#include <iostream>

inline long long mod(long long k, long long n) { return ((k % n) + n) % n; }

template <typename TIntegral>
std::size_t solve(std::vector<std::string> const &input) {
  int rot;
  TIntegral cursor = 50;
  std::size_t result = 0;

  for (auto const &line : input) {
    auto const rot_view = line.substr(1, line.size() - 1);
    std::from_chars(rot_view.data(), rot_view.data() + rot_view.size(), rot);
    if (line[0] == 'R')
      cursor = mod(cursor + rot, 100);
    else
      cursor = mod(cursor - rot, 100);

    if (cursor == 0) {
      ++result;
    }
  }

  return result;
}

template <typename TIntegral>
std::size_t solve_no_branch(std::vector<std::string> const &input) {
  int rot;
  TIntegral cursor = 50;
  std::size_t result = 0;

  for (auto const &line : input) {
    auto const rot_view = line.substr(1);
    std::from_chars(rot_view.data(), rot_view.data() + rot_view.size(), rot);

    // sign = +1 for 'R', -1 for 'L'
    // (line[0] == 'R') is 1 or 0
    // 2*x - 1 → {+1, -1}
    int sign = (int(line[0] == 'R') << 1) - 1;

    cursor = mod(cursor + sign * rot, 100);
    result += (cursor == 0);
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

  auto run_with_time = [&](auto &run, std::string_view name) {
    auto const start = std::chrono::steady_clock::now();
    auto const ans = run(lines);
    auto const end = std::chrono::steady_clock::now();
    std::cout << ans << '\n';
    std::cout << std::format("[{}] Runtime: ", name)
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                         .count() /
                     lines.size()
              << "ns per line\n";
  };

  run_with_time(solve<int64_t>, "naive w/ int64");
  run_with_time(solve_no_branch<int64_t>, "no branch w/ int64");
  run_with_time(solve<int32_t>, "naive w/ int32");
  run_with_time(solve_no_branch<int32_t>, "no branch w/ int32");
  run_with_time(solve<__int128>, "naive w/ int128");
  run_with_time(solve_no_branch<__int128>, "no branch w/ int128");
  run_with_time(solve<int16_t>, "naive w/ int16");
  run_with_time(solve_no_branch<int16_t>, "no branch w/ int16");
  run_with_time(solve<int8_t>, "naive w/ int8");
  run_with_time(solve_no_branch<int8_t>, "no branch w/ int8");

  return 0;
}
