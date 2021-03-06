#ifndef MEASURE_H_
#define MEASURE_H_

/*
    +---------------------------------------+
    | BETH YW? WELSH GOVERNMENT DATA PARSER |
    +---------------------------------------+

    AUTHOR: 979248

    This file contains the decalaration of the Measure class.

    TODO: Read the block comments with TODO in measure.cpp to know which 
    functions and member variables you need to declare in this class.
 */

#include <string>
#include <map>
#include <iostream>

#include "lib_json.hpp"
using json = nlohmann::json;
/*
    The Measure class contains a measure code, label, and a container for readings
    from across a number of years.

    TODO: Based on your implementation, there may be additional constructors
    or functions you implement here, and perhaps additional operators you may wish
    to overload.
*/

class Measure {
private:
	std::string codename;
	std::string label;
	std::map<unsigned int, double> values;
public:
	Measure(std::string code, const std::string &label);
	~Measure() = default;
	const std::string getCodename() const noexcept;
	const std::string getLabel() const noexcept;
	void setLabel(const std::string label);
	const double getValue(const unsigned int key) const;
	void setValue(const unsigned int year, const double value);
	const int size() const noexcept;
	const double getDifference() const noexcept;
	const double getDifferenceAsPercentage() const noexcept;
	const double getAverage() const noexcept;
	friend std::ostream &operator<<(std::ostream &output, const Measure measure);
	friend bool operator==(const Measure lhs, const Measure rhs);
	const std::map<unsigned int, double> getValues() const noexcept;
	friend Measure operator+(Measure lhs, const Measure& rhs);
};

#endif // MEASURE_H_
