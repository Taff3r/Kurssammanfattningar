#include <vector>
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <algorithm>
#include <iterator>
using std::bitset;
class Scheduler {
public:
    Scheduler(std::ifstream& in) : in(in) {};
    void schedule() {
       align(read());
       sort();
       shift();
    }
    std::ostream& print(std::ostream& os){
        std::for_each(lines.begin(), lines.end(), [&os] (const bitset<80>& bs) {os << bs.to_string() << std::endl;});
        return os;
    }
private:
    std::ifstream& in;
    std::vector<bitset<80>> lines;
    size_t read() {
        std::string line;
        size_t shift = 0;
        while(getline(in, line)){
           bitset<80> bs(line);
           shift = line.size();
           lines.push_back(bs);
        }
        return shift;
    }

    void align(size_t shift){
        std::for_each(lines.begin(), lines.end(), [&shift] (bitset<80>& bs) { bs = bs << 80 - shift; });
    }
        
    void sort(){
        std::sort(lines.begin(), lines.end(), [] (const bitset<80>& lhs, const bitset<80> rhs ) { return lhs.count() > rhs.count(); });
    }

    
    void shift(){
        for (size_t i = 1; i < lines.size(); ++i){
            while(!allZeroes(i)){
                lines[i] >>= 1;
            }
        }
    }

    bool allZeroes(size_t i){
        for(size_t k = 0; k < i; k++ ){
            if((lines[k] & lines[i]).any()){
                return false;
            }
        }
        return true;;
    }


    
};

int main () {
    std::ifstream in("activites.txt");
    if(!in) {
        std::cerr << "Cannot open activity file" << std::endl;
    }
    Scheduler sc(in);
    sc.schedule();
    sc.print(std::cout);
}
