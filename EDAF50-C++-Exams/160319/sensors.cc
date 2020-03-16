#include "sensors.h"
#include <algorithm>
#include <sstream>
void Sensors::update(std::string url) {
    try {
        URLStream conn(url);
        string xml, word;
        while(conn >> xml) { // Read entire xml file into string
            xml += " "; // add blankspace into xml for easier use with string stream
        } 
        std::istringstream wordsXML(xml);
        while(wordsXML >> word){
        
        }
        
    } catch (std::exception& e){
        // Conn failed
        return;
    }

   
}
