#include <chrono>
#include <iostream>

auto solve(std::vector<uint64_t> const& nums, std::vector<bool> const& mult_op) {
  uint64_t result = 0;

  auto const get = [&nums, &mult_op](int i, int j) { return nums[i * mult_op.size() + j]; };

  for (std::size_t i = 0; i < mult_op.size(); ++i) {
    uint64_t v = 0;

    if (mult_op[i]) {
      ++v;
    }

    for (std::size_t j = 0; j < (nums.size() / mult_op.size()); ++j) {
      std::cout << std::format("({}, {}) = {} mult={}\n", j, i, get(j, i), static_cast<int>(mult_op[i]));

      if (mult_op[i]) {
        v *= get(j, i);
      } else {
        v += get(j, i);
      }
      std::cout << v << std::endl;
    }

    result += v;
  }

  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::vector<uint64_t> nums;
  std::vector<bool> is_mult;

  std::string line;
  while (std::cin >> line) {
    if (line[0] == '*' || line[0] == '+') {
      is_mult.push_back(line[0] == '*');
    } else {
      nums.push_back(std::stoull(line));
    }
  }

  auto const start = std::chrono::steady_clock::now();
  auto const ans = solve(nums, is_mult);
  auto const end = std::chrono::steady_clock::now();
  std::cout << ans << '\n';
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns\n";
  return 0;
}
