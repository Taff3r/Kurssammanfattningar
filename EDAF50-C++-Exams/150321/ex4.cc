#include <algorithm>
#include <iostream>
#include <vector>
template <typename Container>
class sort_insert_iterator : public std::iterator<std::random_access_iterator_tag, void, void, void, void>{
public:
    using value_type = typename Container::value_type;
    explicit sort_insert_iterator(Container& c) : c(&c) {};
    sort_insert_iterator& operator ++() {return *this;}
    sort_insert_iterator& operator *() {return *this;}
    sort_insert_iterator& operator = (const value_type& v) {
        c->insert(std::lower_bound(c->begin(), c->end(), v), v);
        return *this;
    }
private:
    Container* c;
};
template <typename Container>
sort_insert_iterator<Container> sort_inserter(Container& c) {
    return sort_insert_iterator<Container> (c);
}

int main() {
    std::vector<int> v;
    int a[] = {333,3,4,5,1};
    std::copy(std::begin(a), std::end(a), sort_inserter(v));
    for(auto& a : v) {
        std::cout << a << " ";
    }
}


