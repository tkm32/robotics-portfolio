// C vs Modern C++ の主要な差分を1ファイルで体験する
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>

int main() {
    // ========== auto ==========
    // C: int x = 42;  型を必ず明示
    // C++: コンパイラが推論してくれる
    auto x = 42;          // int
    auto pi = 3.14;       // double
    auto name = std::string("tak");  // std::string

    std::cout << "x=" << x << " pi=" << pi << " name=" << name << "\n";

    // ========== vector (可変長配列) ==========
    // C: int arr[100]; + size変数を別管理
    // C++: vectorが全部やってくれる
    std::vector<int> nums = {3, 1, 4, 1, 5, 9};
    nums.push_back(2);  // 末尾追加
    nums.pop_back();     // 末尾削除

    std::cout << "size=" << nums.size() << "\n";

    // ========== 範囲for ==========
    // C: for(int i=0; i<n; i++) printf("%d ", arr[i]);
    // C++: コンテナを直接回せる
    std::cout << "nums: ";
    for (auto n : nums) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // 参照で回すと書き換え可能
    for (auto& n : nums) {
        n *= 2;
    }

    std::cout << "doubled: ";
    for (const auto& n : nums) {  // const参照 = 読むだけ
        std::cout << n << " ";
    }
    std::cout << "\n";

    // ========== nullptr ==========
    // C: NULL は (void*)0 — 整数と紛らわしい
    // C++: nullptr は型安全
    int* ptr = nullptr;
    if (ptr == nullptr) {
        std::cout << "ptr is null\n";
    }

    // ========== 構造化束縛 (C++17) ==========
    // C: 構造体を返して .x .y でアクセス
    // C++17: 直接分解して受け取れる
    auto [min_it, max_it] = std::minmax_element(nums.begin(), nums.end());
    std::cout << "min=" << *min_it << " max=" << *max_it << "\n";

    // ========== std::array (固定長配列) ==========
    // C: int arr[3] = {1,2,3}; — サイズ情報が消える
    // C++: std::array はサイズを保持
    std::array<int, 3> fixed = {10, 20, 30};
    std::cout << "array size=" << fixed.size() << "\n";

    return 0;
}
