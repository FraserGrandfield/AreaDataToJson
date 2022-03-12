#ifndef AREA_H_
#define AREA_H_

/*
    +---------------------------------------+
    | BETH YW? WELSH GOVERNMENT DATA PARSER |
    +---------------------------------------+

    AUTHOR: 979248

    This file contains the Area class declaration. Area objects contain all the
    Measure objects for a given local area, along with names for that area and a
    unique authority code.

    TODO: Read the block comments with TODO in area.cpp to know which 
    functions and member variables you need to declare in this class.
 */

#include <string>
#include <map>
#include <iostream>
#include "measure.h"

#include "lib_json.hpp"
using json = nlohmann::json;
/*
    An Area object consists of a unique authority code, a container for names
    for the area in any number of different languages, and a container for the
    Measures objects.

    TODO: Based on your implementation, there may be additional constructors
    or functions you implement here, and perhaps additional operators you may wish
    to overload.
*/
class Area {
 private:
 	std::string localAuthorityCode;
 	std::map<std::string, std::string> names;
	std::map<std::string, Measure> measures;
public:
	Area(const std::string& localAuthorityCode);
	~Area() = default;
	const std::string getLocalAuthorityCode() const;
	const std::string getName(const std::string lang) const;
	void setName(const std::string lang, const std::string name);
	Measure& getMeasure(const std::string key);
	void setMeasure(const std::string codename, const Measure measure);
	const int size() const noexcept;
	friend std::ostream &operator<<(std::ostream &output, const Area area);
	friend bool operator==(const Area lhs, const Area rhs);
	const std::map<std::string, std::string> getNames() const;
	const std::map<std::string, Measure> getMeasures() const;
	friend Area operator+(Area lhs, const Area& rhs);
	
};


#endif // AREA_H_






