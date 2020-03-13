#include <string>
#include <iostream>
#include <set>
class NameList {
public:
    NameList() {}
    ~NameList(){}

    void insert(const std::string& name){
        names.insert(new std::string(name));
    }

    void printSorted() const {
        for(auto it = names.begin(); it != names.end(); ++it ){
            std::cout << *it << std::endl;
        }
    }
private:
    typedef std::set<std::string*> list_type;
    list_type names;
};

/* 3a:
 * The class leaks memory since the destructor is not implemented. Each and everyone of the strings in the set has to be individually deleted in the destructor.
 */

/* 
 * 3b:
 * The iterator points to the memory address of the strings and not their values.
 */

/*
 * 3c:
 * The set keeps the POINTERS sorted, i.e. the addresses.
 * We can fix this my simply adding more memory i.e another map that keeps the actual values and then print that map.
 * Ineffecient but gets the job done.
 *
 * BETTER SOLUTION: (FROM SOL. SHEET):
 * Write a comperator for inserting in sorted order into the set.
 *
 */

// Correction:
class NuNameList {
public:
    NuNameList() {}
    // Destructor that has to be implemented
    ~NuNameList(){
        for(auto it = names.begin(); it != names.end(); ++it) {
            delete *it; // delete the reference of the iterator.
        }
    }

    void insert(const std::string& name){
        names.insert(new std::string(name));
    }

    void printSorted() const {
        std::set<std::string> sorted;
        for(auto it = names.begin(); it != names.end(); ++it ){
            std::cout << **it << std::endl; 
        }
    }
private:
    struct OrderInserter {
        bool operator () (const std::string* lhs, const std::string* rhs) {
            return *lhs < * rhs;
        }
    };
    typedef std::set<std::string*, OrderInserter> list_type;
    list_type names;
};

// Test:

int main() {
    NuNameList l;

    l.insert("simon");
    l.insert("alexander");
    l.insert("jörgen");
    l.insert("tenggren");
    
    l.printSorted();
    // destructor is called when l goes out of scope. NO LEAKS.
}
