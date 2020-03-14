template <typename Input, typename Output, typename A, typename B>
void apply_all(Input begin, Input end, Output applyTo, A a, B b) {
    while(begin != end){
        *applyTo++ = (*begin)(a, b);
        ++begin;
    }
}
#include<iostream>
#include<vector>
#include<functional>

int main() {
    std::vector<std::function<int(int, int)>> fs;
    fs.push_back(std::plus<int> {});
    fs.push_back([] (int x, int y) {return 2*x -y;});
    fs.push_back(std::divides<int> {});

    std::vector<int> rs(fs.size());
    apply_all(fs.begin(), fs.end(), rs.begin(), 10, 2);

    for(auto a : rs) {
        std::cout << a << std::endl;
    }

}

