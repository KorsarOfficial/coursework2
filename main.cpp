#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <random>
#include <span>
#include <string_view>
#include <optional>
#include <ranges>

// prefix[i] = Sigma_{j=0}^{i-1} a[j]
[[nodiscard]] auto prefix_sums(std::span<const int> a) -> std::vector<long long> {
    std::vector<long long> pref(a.size() + 1, 0);
    for (std::size_t i = 0; i < a.size(); ++i) {
        pref[i + 1] = pref[i] + a[i];
    }
    return pref;
}

// sum(a[l..r]) = prefix[r+1] - prefix[l], O(1)
[[nodiscard]] constexpr auto range_sum(std::span<const long long> pref, int l, int r) -> long long {
    return pref[r + 1] - pref[l];
}

// max_w[i] = max{a[j] : i-k+1 <= j <= i}, O(n) monotone deque
[[nodiscard]] auto sliding_window_max(std::span<const int> a, int k) -> std::vector<int> {
    const int n = static_cast<int>(a.size());
    std::vector<int> result;
    result.reserve(n - k + 1);
    std::deque<int> dq;
    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && dq.front() < i - k + 1)
            dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            result.push_back(a[dq.front()]);
    }
    return result;
}

// find (i,j) s.t. a[i]+a[j]=target on sorted array, O(n)
[[nodiscard]] auto two_sum_sorted(std::span<const int> sorted_a, int target)
    -> std::optional<std::pair<int, int>> {
    int lo = 0, hi = static_cast<int>(sorted_a.size()) - 1;
    while (lo < hi) {
        const int s = sorted_a[lo] + sorted_a[hi];
        if (s == target) return std::pair{lo, hi};
        if (s < target) ++lo;
        else --hi;
    }
    return std::nullopt;
}

// find x in sorted array, O(log n)
[[nodiscard]] auto binary_search_index(std::span<const int> sorted_a, int x)
    -> std::optional<int> {
    int lo = 0, hi = static_cast<int>(sorted_a.size()) - 1;
    while (lo <= hi) {
        const int mid = lo + (hi - lo) / 2;
        if (sorted_a[mid] == x) return mid;
        if (sorted_a[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return std::nullopt;
}

// f(i) = max(a[i], f(i-1)+a[i]), O(n)
[[nodiscard]] auto max_subarray(std::span<const int> a) -> long long {
    long long cur = a[0], best = a[0];
    for (std::size_t i = 1; i < a.size(); ++i) {
        cur = std::max(static_cast<long long>(a[i]), cur + a[i]);
        best = std::max(best, cur);
    }
    return best;
}

void print_vec(std::string_view label, std::span<const int> v) {
    std::cout << label << ": [";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "]\n";
}

void print_vec_ll(std::string_view label, std::span<const long long> v) {
    std::cout << label << ": [";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "]\n";
}

int main() {
    // |A| = 20, a[i] in [-50, 100]
    constexpr int N = 20;
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(-50, 100);

    std::vector<int> a(N);
    std::ranges::generate(a, [&] { return dist(rng); });

    print_vec("A", a);
    std::cout << "\n";

    // prefix[i] = Sigma_{j=0}^{i-1} a[j]
    auto pref = prefix_sums(a);
    print_vec_ll("prefix_sums", pref);

    // range_sum(3,7) = prefix[8] - prefix[3]
    constexpr int ql = 3, qr = 7;
    std::cout << "range_sum(" << ql << "," << qr << ") = " << range_sum(pref, ql, qr) << "\n\n";

    // sliding window max, k=4
    constexpr int k = 4;
    auto sw_max = sliding_window_max(a, k);
    std::cout << "sliding_window_max (k=" << k << "):\n";
    print_vec("  result", sw_max);
    std::cout << "\n";

    // two-pointer on sorted copy
    auto sorted_a = a;
    std::ranges::sort(sorted_a);
    print_vec("sorted A", sorted_a);

    const int target = sorted_a[3] + sorted_a[N - 2];
    if (const auto result = two_sum_sorted(sorted_a, target)) {
        const auto [i1, i2] = *result;
        std::cout << "two_sum target=" << target << " -> indices (" << i1 << "," << i2 << ")"
                  << " = (" << sorted_a[i1] << "+" << sorted_a[i2] << ")\n\n";
    } else {
        std::cout << "two_sum target=" << target << " -> not found\n\n";
    }

    // binary search
    const int search_val = sorted_a[N / 2];
    if (const auto idx = binary_search_index(sorted_a, search_val)) {
        std::cout << "binary_search(" << search_val << ") -> index " << *idx << "\n\n";
    } else {
        std::cout << "binary_search(" << search_val << ") -> not found\n\n";
    }

    // f(i) = max(a[i], f(i-1)+a[i])
    const long long ms = max_subarray(a);
    std::cout << "max_subarray_sum = " << ms << "\n";

    return 0;
}
