#include <iostream>
#include <unordered_map>
#include <queue>

int main() {
    std::unordered_map<std::string, int> m = {{"apple", 3}};
    m.insert({"orange", 2});
    std::cout << m["orange"] << "\n";

    std::priority_queue<int> q;
    q.push(3);
    q.push(4);
    q.push(1);
    q.push(8);
    q.push(4);

    while(!q.empty()) {
        std::cout << q.top() << ", ";
        q.pop();
    }

    std::cout << "\n";
}