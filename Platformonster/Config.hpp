#pragma once
#include <map>
#include <string>
#include <boost/variant.hpp>

typedef boost::variant<float, int, std::string, bool> Option;
typedef std::map<std::string, Option> Config;

