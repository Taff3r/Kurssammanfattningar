#ifndef PERSON_H 
#define PERSON_H 
#include <cstddef>
#include <iostream>
#include <string>
using std::string;
class Person {
public:
    Person(string* name, string* address, int age) : name(name), address(address), age{age}{}
    ~Person() {delete name; delete address;}
    Person& operator = (const Person&);
    Person(const Person&);
    friend std::ostream& operator << (std::ostream&, const Person&);
private:
    string* name;
    string* address;
    int age;
};
#endif
