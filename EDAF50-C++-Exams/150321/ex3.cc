#include <vector>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <random>
class BulgarianSolitaire {
public:
    BulgarianSolitaire(unsigned int n): numStacks{n}, d(0, n) { distribute(); };
    bool atGoal() const;
    void move();
    friend std::ostream& operator << (std::ostream& os, const BulgarianSolitaire& bs);
private:
    unsigned int numStacks;
    std::default_random_engine e;
    std::uniform_int_distribution<unsigned> d;
    std::vector<unsigned int> stacks;
    void distribute();
};


void BulgarianSolitaire::distribute(){
    :wq
}

bool BulgarianSolitaire::atGoal() const {
    if(stacks.size() != numStacks){ // if we don't have enough stacks we can not be finished
        return false;
    }
    std::vector<unsigned int> adjDiff; 
    std::adjacent_difference(stacks.begin(), stacks.end(), std::back_inserter(adjDiff));
    bool asc = stacks[0] < stacks[1];
    if( asc ){
        return std::count(adjDiff.begin(), adjDiff.end(), 1) == numStacks;
    }
    return std::count(adjDiff.begin() + 1, adjDiff.end(), 1) == numStacks - 1 && stacks[0] == numStacks;
}

void BulgarianSolitaire::move() {
    // remove one from each stack
    size_t removed = stacks.size(); // number of removed cards is the numbers of stacks before
    for(size_t i = 0; i != stacks.size(); ++i) {
        stacks[i]--;
    }
    stacks.resize(numStacks); // resize to max pos

    // replace the removed cards at random positions 
    for(size_t i = 0; i != removed; ++i){
        stacks[d(e)]++;
    }

    // remove all stacks with zero cards
    stacks.erase(std::find(stacks.begin(), stacks.end(), 0), stacks.end());
}

std::ostream& operator << (std::ostream& os, const BulgarianSolitaire& bs){
    std::for_each(bs.stacks.begin(), bs.stacks.end(), [&os] (int i) { os << i << " ";});
    return os;
}

int main() {
    int n;    
    std::cout << "Number of cards: ";
    std::cin >> n;
    BulgarianSolitaire bs(n);

}
