#include "person.h"
Person& Person::operator = (const Person& rhs){
    if(this != &rhs){
        string* n = new string;
        string* a = new string;
        n = rhs.name;
        a = rhs.address;
        int age = rhs.age;
        delete name;
        delete address;
        name = n;
        address = a; 
        age = age;
    }
    return *this;
}
Person::Person(const Person& p){
    string* n = new string;
    string* a = new string;
    *n = *p.name;
    *a = *p.address;

    age = p.age;
    name = n;
    address = a;
}
std::ostream& operator << (std::ostream& os, const Person& p){
    os << *p.name << " Age: " << p.age << " Address: " << *p.address;
    return os;
}

int main() {
    string* n = new string("Simon Tenggren");
    string* a = new string("Råbyvägen 15K");
    Person x(n, a, 22);
    {
        Person b = x;
        std::cout << b << std::endl;
    }
    std::cout << x << std::endl;
}


