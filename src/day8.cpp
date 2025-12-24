#include <chrono>
#include <iostream>
#include <numeric>
#include <queue>
#include <ranges>
#include <utility>

using coord_t = std::array<int, 3>;
using coord_id_t = std::size_t;
using metadata_t = std::pair<uint64_t, std::pair<coord_id_t, coord_id_t>>;

struct union_find {
  union_find(std::size_t size) {
    parent_.resize(size);
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  std::size_t find(coord_id_t i) const {
    if (parent_[i] == i) {
      return i;
    }
    return find(parent_[i]);
  }

  void merge(coord_id_t a, coord_id_t b) { parent_[find(a)] = find(b); }

  [[__nodiscard__]] std::size_t answer() const {
    std::vector<coord_id_t> sizes(parent_.size(), 0);
    for (auto i = 0u; i < parent_.size(); ++i) {
      sizes[find(i)] += 1;
    }
    std::sort(sizes.begin(), sizes.end(), std::greater<std::size_t>());
    return sizes[0] * sizes[1] * sizes[2];
  }

 private:
  std::vector<coord_id_t> parent_;
};

inline uint64_t dist(coord_t const& a, coord_t const& b) {
  return std::pow(a[0] - b[0], 2) + std::pow(a[1] - b[1], 2) + std::pow(a[2] - b[2], 2);
}

auto solve(std::vector<coord_t> const& input) {
  std::priority_queue<metadata_t, std::vector<metadata_t>, std::greater<metadata_t>> dist_index;
  union_find uf(input.size());

  for (auto i = 0u; i < input.size(); ++i) {
    for (auto j = 0u; j < i; ++j) {
      auto const pairwise_dist = dist(input[i], input[j]);
      metadata_t const index_value = {pairwise_dist, {i, j}};
      dist_index.emplace(index_value);
    }
  }

  static auto constexpr MERGE_CYCLES = 1000u;
  std::size_t curr_merges = 0;

  while (curr_merges < MERGE_CYCLES) {
    auto const [curr_dist, ids] = dist_index.top();
    auto const [pid1, pid2] = ids;
    dist_index.pop();
    uf.merge(pid1, pid2);
    curr_merges++;
  }

  return uf.answer();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::vector<coord_t> lines{};
  std::string line;
  while (std::cin >> line) {
    auto line_view = std::string_view(line);
    auto subrange = line_view | std::views::split(',');
    auto it = subrange.begin();

    coord_t coord;
    for (auto i = 0u; i < std::tuple_size<coord_t>::value; ++i) {
      auto bgn = std::ranges::begin(*it);
      auto end = std::ranges::end(*it);
      std::from_chars(bgn, end, coord[i]);
      ++it;
    }
    lines.push_back(coord);
  }
  auto const start = std::chrono::steady_clock::now();
  auto const ans = solve(lines);
  auto const end = std::chrono::steady_clock::now();
  std::cout << "ans: " << ans << '\n';
  std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us\n";
  return 0;
}
