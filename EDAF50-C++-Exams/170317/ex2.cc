#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<set>
#include<algorithm>
using std::string;
class Ruler {
private:
    string name;    
    int order;
    string nation;
    int from; 
    int to; 
    string comparable() const {
        string rep = nation;
        rep += from;
        return rep;
    }
public:
    Ruler() = default;
    Ruler(string name, int order, string nation, int from, int to = 0): name(name), order(order), nation(nation), from(from), to(to) {}
    friend std::ostream& operator << (std::ostream& os, const Ruler& r);
    friend std::istream& operator >> (std::istream& is, Ruler& r);
    
    bool operator < (const Ruler& rhs) const {
        return this->comparable() < rhs.comparable();
    }
};

std::ostream& operator << (std::ostream& os, const Ruler& r){
    os << r.name << " " << r.order << " of " << r.nation << ", " << r.from << "-";
    if (r.to == 0){
        os << "present";
    } else {
        os << r.to;
    }
    return os;
}
std::istream& operator >> (std::istream& is, Ruler& r){
    is >> r.name >> r.order >> r.nation >> r.from >> r.to;
    return is;
}

int main(int argc, char** args) {
    std::set<Ruler> rulers;
    if(argc == 1) return 0;
    std::ifstream file(*(args + 1));
    string line, word;
    while(getline(file, line)){
        std::istringstream ss(line);
        string name, nation;
        int order, from, to;
        ss >> name;
        ss >> order;
        ss >> nation;
        ss >> from;
        ss >> to;
        rulers.insert({name, order, nation, from, to});
    }
    file.close();
    std::for_each(rulers.begin(), rulers.end(), [] (const Ruler& r) { std::cout << r << std::endl;});

}
