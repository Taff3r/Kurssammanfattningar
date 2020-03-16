#ifndef SENSORS_H
#define SENSORS_H
#include <string>
#include <unordered_map>
#include <istream>
class URLStream : public std::istream{
public:
    URLStream(std::string url);
};

using std::unordered_map;
using std::string;
class Sensors {
public:
    Sensors();
    void update(std::string url);
    double getTemp(const std::string& id) const;
    void print() const;

private:
    unordered_map<string, std::pair<string, double>> temps;
    
};


#endif
