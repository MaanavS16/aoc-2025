#include <chrono>
#include <iostream>
#include <string>
#include <vector>
auto solve(std::vector<std::vector<std::string>> const& nums, std::vector<bool> const& mult_op) {
  uint64_t result = 0;

  const std::size_t rows = nums.size();
  const std::size_t cols = nums[0].size();

  for (std::size_t j = 0; j < cols; ++j) {
    const std::size_t width = nums[0][j].size();

    // one number + power per character column
    std::vector<uint64_t> col_num(width, 0);
    std::vector<uint64_t> pow10(width, 1);

    // right-to-left across characters
    for (std::size_t k = width; k-- > 0;) {
      // top-to-bottom across rows
      for (std::size_t i = 0; i < rows; ++i) {
        char c = nums[i][j][k];
        if (c != ' ') {
          col_num[k] += (c - '0') * pow10[k];
          pow10[k] *= 10;
        }
      }
    }

    uint64_t col_result = mult_op[j] ? 1 : 0;

    for (uint64_t n : col_num) {
      if (mult_op[j])
        col_result *= n;
      else
        col_result += n;
    }

    result += col_result;
  }

  return result;
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(std::cin, line)) {
    if (!line.empty())
      lines.push_back(line);
  }

  // operator layout is last line
  const std::string op_line = lines.back();
  lines.pop_back();

  std::vector<std::size_t> col_starts;
  std::vector<bool> is_mult;

  for (std::size_t i = 0; i < op_line.size(); ++i) {
    if (op_line[i] == '*' || op_line[i] == '+') {
      col_starts.push_back(i);
      is_mult.push_back(op_line[i] == '*');
    }
  }

  std::vector<std::vector<std::string>> nums;
  nums.reserve(lines.size());

  for (auto const& row_line : lines) {
    std::vector<std::string> row;
    row.reserve(col_starts.size());

    for (std::size_t c = 0; c < col_starts.size(); ++c) {
      std::size_t start = col_starts[c];
      std::size_t end = (c + 1 < col_starts.size()) ? col_starts[c + 1] : row_line.size();

      row.emplace_back(row_line.substr(start, end - start));
    }

    nums.push_back(std::move(row));
  }

  auto const start = std::chrono::steady_clock::now();
  auto const ans = solve(nums, is_mult);
  auto const end = std::chrono::steady_clock::now();

  std::cout << ans << '\n';
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns\n";

  return 0;
}
