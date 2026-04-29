// 課題: 以下を実装してください
// 1. int型のvectorを作り、{5, 2, 8, 1, 9, 3} で初期化
// 2. 範囲forで全要素を2倍にする
// 3. 2倍にした結果を出力する
// 4. vectorの中から最大値と最小値を見つけて出力する（std::minmax_element使用）

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> arr = {5, 2, 8, 1, 9, 3};
    for (auto& n : arr) {
        n *= 2;
        std::cout << n << " ";
    }
    std::cout << "\n";

    auto result = std::minmax_element(arr.begin(), arr.end());
    std::cout << *result.first << ", " << *result.second << "\n";
    return 0;
}
