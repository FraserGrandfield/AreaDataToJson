#ifndef BETHYW_H_
#define BETHYW_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 979248

  This file contains declarations for the helper functions for initialising and
  running Beth Yw?

  TODO: Read the block comments with TODO in bethyw.cpp to know which 
  functions you need to declare in this file.
 */

#include <string>
#include <unordered_set>
#include <vector>

#include "lib_cxxopts.hpp"

#include "datasets.h"
#include "areas.h"

const char DIR_SEP =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

namespace BethYw {

/*
  TODO: Enter your student number here!
*/
const std::string STUDENT_NUMBER = "979248";

/*
  Run Beth Yw?, parsing the command line arguments and acting upon them.
*/
int run(int argc, char *argv[]);

/*
  Create a cxxopts instance.
*/
cxxopts::Options cxxoptsSetup();

/*
  Parse the datasets argument and return a std::vector of all the datasets
  to import. InputFileSource is declared in datasets.h.
*/
std::vector<BethYw::InputFileSource> parseDatasetsArg(
  cxxopts::ParseResult& args);

/*
  Parse the areas argument and return a std::unordered_set of all the
  areas to import, or an empty set if all areas should be imported.
*/
std::unordered_set<std::string> parseAreasArg(cxxopts::ParseResult& args);
    
 /*
    Parse the measures argument and return a std::unordered_set of all the
    measures to import, or an empty set if all measures should be imported.
 */
std::unordered_set<std::string> parseMeasuresArg(cxxopts::ParseResult& args);

std::tuple<unsigned int, unsigned int> parseYearsArg(cxxopts::ParseResult& args);

void loadAreas(Areas &areas, const std::string dir, const std::unordered_set<std::string> areasFilter);

void loadDatasets(Areas &areas,
	std::string dir,
	std::vector<InputFileSource> datasetsToImport,
	std::unordered_set<std::string> areasFilter,
	std::unordered_set<std::string> measuresFilter,
	std::tuple<unsigned int, unsigned int> yearsfilter) noexcept;

const bool isAllInVectorOfStrings(const std::vector<std::string> vec);

void rightAlignTwoStrings(std::string& str1, std::string& str2);

const std::string toLowercase(const std::string& str);
} // namespace BethYw

#endif // BETHYW_H_
