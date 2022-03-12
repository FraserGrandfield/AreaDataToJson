


/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 979248

  This file contains the implementation of the Measure class. Measure is a
  very simple class that needs to contain a few member variables for its name,
  codename, and a Standard Library container for data. The data you need to 
  store is values, organised by year. I'd recommend storing the values as 
  doubles.

  This file contains numerous functions you must implement. Each function you
  must implement has a TODO block comment. 
*/

#include <stdexcept>
#include <string>
#include <cstdlib>

#include "measure.h"
#include "bethyw.h"

/*
  TODO: Measure::Measure(codename, label);

  Construct a single Measure, that has values across many years.

  All StatsWales JSON files have a codename for measures. You should convert 
  all codenames to lowercase.

  @param codename
    The codename for the measure

  @param label
    Human-readable (i.e. nice/explanatory) label for the measure

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);
*/
Measure::Measure(const std::string codename, const std::string &label) : label(label) {
	std::string codenameToLowercase = "";
	for (std::string::size_type i = 0; i < codename.length(); i++) {
		if (codename[i] <= 'Z' && codename[i] >= 'A') {
			codenameToLowercase += (codename[i] + 32);
		} else {
			codenameToLowercase += codename[i];
		}
	}
	this->codename = codenameToLowercase;
}

/*
  TODO: Measure::getCodename()

  Retrieve the code for the Measure. This function should be callable from a 
  constant context and must promise to not modify the state of the instance or 
  throw an exception.

  @return
    The codename for the Measure

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    ...
    auto codename2 = measure.getCodename();
*/
const std::string Measure::getCodename() const noexcept {
	return codename;
}

/*
  TODO: Measure::getLabel()

  Retrieve the human-friendly label for the Measure. This function should be 
  callable from a constant context and must promise to not modify the state of 
  the instance and to not throw an exception.

  @return
    The human-friendly label for the Measure

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    ...
    auto label = measure.getLabel();
*/
const std::string Measure::getLabel() const noexcept {
	return label;
}

/*
  TODO: Measure::setLabel(label)

  Change the label for the Measure.

  @param label
    The new label for the Measure

  @example
    Measure measure("pop", "Population");
    measure.setValue(1999, 12345678.9);
    ...
    measure.setLabel("New Population");
*/
void Measure::setLabel(const std::string label) {
	this->label = label;
}

/*
  TODO: Measure::getValue(key)

  Retrieve a Measure's value for a given year.

  @param key
    The year to find the value for

  @return
    The value stored for the given year

  @throws
    std::out_of_range if year does not exist in Measure with the message
    No value found for year <year>

  @return
    The value

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    ...
    auto value = measure.getValue(1999); // returns 12345678.9
*/
const double Measure::getValue(const unsigned int key) const {
	double value;
	if (values.count(key)) {
		value = values.at(key);
	} else {
		std::string keyString = std::to_string(key);
		throw std::out_of_range("No value found for year " + keyString);
	}
	return value;
}
/*
  TODO: Measure::setValue(key, value)

  Add a particular year's value to the Measure object. If a value already
  exists for the year, replace it.

  @param key
    The year to insert a value at

  @param value
    The value for the given year

  @return
    void

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
*/
void Measure::setValue(const unsigned int year, const double value) {
	values[year] = value;
}

/*
  TODO: Measure::size()

  Retrieve the number of years data we have for this measure. This function
  should be callable from a constant context and must promise to not change
  the state of the instance or throw an exception.

  @return
    The size of the measure

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    auto size = measure.size(); // returns 1
*/
const int Measure::size() const noexcept{
	return values.size();
}

/*
  TODO: Measure::getDifference()

  Calculate the difference between the first and last year imported. This
  function should be callable from a constant context and must promise to not
  change the state of the instance or throw an exception.

  @return
    The difference/change in value from the first to the last year, or 0 if it
    cannot be calculated

  @example
    Measure measure("pop", "Population");
    measure.setValue(1999, 12345678.9);
    measure.setValue(1999, 12345679.9);
    auto diff = measure.getDifference(); // returns 1.0
*/
const double Measure::getDifference() const noexcept {
	double diff = 0;
	if (size() >= 2) {
		double earliestYear = values.begin()->second;
		double oldestYear = values.rbegin()->second;
		diff = std::abs(earliestYear - oldestYear);
	}
	return diff;
}

/*
  TODO: Measure::getDifferenceAsPercentage()

  Calculate the difference between the first and last year imported as a 
  percentage. This function should be callable from a constant context and
  must promise to not change the state of the instance or throw an exception.

  @return
    The difference/change in value from the first to the last year as a decminal
    value, or 0 if it cannot be calculated

  @example
    Measure measure("pop", "Population");
    measure.setValue(1990, 12345678.9);
    measure.setValue(2010, 12345679.9);
    auto diff = measure.getDifferenceAsPercentage();
*/
const double Measure::getDifferenceAsPercentage() const noexcept {
	double diff = 0;
	if (size() >= 2) {
		double earliestYear = values.begin()->second;
		diff = getDifference() / earliestYear;
	}
	return diff * 100;
}

/*
  TODO: Measure::getAverage()

  Calculate the average/mean value for all the values. This function should be
  callable from a constant context and must promise to not change the state of 
  the instance or throw an exception.

  @return
    The average value for all the years, or 0 if it cannot be calculated

  @example
    Measure measure("pop", "Population");
    measure.setValue(1999, 12345678.9);
    measure.setValue(1999, 12345679.9);
    auto diff = measure.getDifference(); // returns 1
*/
const double Measure::getAverage() const noexcept {
	double average = 0;
	for (auto it = values.begin(); it != values.end(); it++) {
		average += it->second;
	}
	if (size()) {
		average = average / size();
	}
	return average;
}


/*
  TODO: operator<<(os, measure)

  Overload the << operator to print all of the Measure's imported data.

  We align the year and value outputs by padding the outputs with spaces,
  i.e. the year and values should be right-aligned to each other so they
  can be read as a table of numerical values.

  Years should be printed in chronological order. Three additional columns
  should be included at the end of the output, correspodning to the average
  value across the years, the difference between the first and last year,
  and the percentage difference between the first and last year.

  If there is no data in this measure, print the name and code, and 
  on the next line print: <no data>

  See the coursework specification for more information.

  @param os
    The output stream to write to

  @param measure
    The Measure to write to the output stream

  @return
    Reference to the output stream

  @example
    std::string codename = "Pop";
    std::string label = "Population";
    Measure measure(codename, label);

    measure.setValue(1999, 12345678.9);
    std::cout << measure << std::end;
*/
std::ostream &operator<<(std::ostream &output, const Measure measure) {
	output << measure.getLabel() << " (" << measure.getCodename() << ")" << std::endl;
	std::string years = "";
	std::string values = "";
	if (!measure.size()) {
		output << "<no data>" << std::endl;	
	} else {
		for (auto it = measure.values.begin(); it != measure.values.end(); it++) {
			std::string year = std::to_string(it->first);
			std::string value = std::to_string(it->second);
			BethYw::rightAlignTwoStrings(year, value);
			years += year + " ";
			values += value + " ";
		}
		//Average column
		std::string title = "Average";
		std::string val = std::to_string(measure.getAverage());
		BethYw::rightAlignTwoStrings(title, val);
		years += title + " ";
		values += val + " ";
		//Difference column
		title = "Diff.";
		val = std::to_string(measure.getDifference());
		BethYw::rightAlignTwoStrings(title, val);
		years += title + " ";
		values += val + " ";
		//% Diff column
		title = "% Diff.";
		val = std::to_string(measure.getDifferenceAsPercentage());
		BethYw::rightAlignTwoStrings(title, val);
		years += title;
		values += val;	
		output << years << std::endl;
		output << values << std::endl;
	}
	return output;
}

/*
  TODO: operator==(lhs, rhs)

  Overload the == operator for two Measure objects. Two Measure objects
  are only equal when their codename, label and data are all equal.

  @param lhs
    A Measure object

  @param rhs
    A second Measure object

  @return
    true if both Measure objects have the same codename, label and data; false
    otherwise
*/
bool operator==(const Measure lhs, const Measure rhs) {
	return (lhs.getLabel() == rhs.getLabel() &&
		lhs.getCodename() == rhs.getCodename() && 
		lhs.getValues() == rhs.getValues());
}

/*
	getValues()
	Retruns the map of values.

	@return
		the map of values.
*/
const std::map<unsigned int, double> Measure::getValues() const noexcept {
	return values;
}

/*
	operator+(lhs, rhs)
	Joins two measure object together. Keeps the content of lhs and adds rhs. If rhs contains
	data in lhs then rhs overrides the lhs data.

	@param lhs
		Measure object
	@param rhs
		Another Measure object
	@return
		The lhs Measure with the rhs data added.
*/
Measure operator+(Measure lhs, const Measure& rhs) {
	lhs.setLabel(rhs.getLabel());
	for (auto it = rhs.values.begin(); it != rhs.values.end(); it++) {
		lhs.setValue(it->first, it->second);	
	}
	return lhs;
}
