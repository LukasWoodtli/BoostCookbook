#include <iostream>
#include <regex>

#include <boost/regex.hpp>

int main() {

	std::cout << "Available reqex sytaxes:\n"
		<< "\t[0] Perl (boost) | ECMAScript (C++11)\n"
		<< "\t[1] Perl (boost) | ECMAScript (C++11) case insensitive\n"
		<< "\t[2] POSIX extended\n"
		<< "\t[3] POSIX extended case insensitive\n"
		<< "\t[4] POSIX basic\n"
		<< "\t[5] POSIX basic case insensitive\n"
		<< "Choose regex sytax: ";


	boost::regex::flag_type flag;
	std::regex_constants::syntax_option_type flag_std;

	switch(std::cin.get()) {
		case '0':
			flag = boost::regex::perl;
			flag_std = std::regex::ECMAScript;
			break;
		case '1':
			flag = boost::regex::perl | boost::regex::icase;
			flag_std = std::regex::ECMAScript | std::regex::icase;
			break;

		case '2':
			flag = boost::regex::extended;
			flag_std = std::regex::extended;
			break;
		case '3':
			flag = boost::regex::extended | boost::regex::icase;
			flag_std = std::regex::extended | std::regex::icase;
			break;

		case '4':
			flag = boost::regex::basic;
			flag_std = std::regex::basic;
			break;
		case '5':
			flag = boost::regex::basic | boost::regex::icase;
			flag_std = std::regex::basic | std::regex::icase ;
			break;

		default:
			std::cerr << "Incorrect regex syntax. Exiting...\n";
			return -1;
	}


	std::cin.ignore();
	std::cin.clear();

	std::string regex, str;
	do {
		std::cout << "Input regex: ";
		if (not std::getline(std::cin, regex) || regex.empty()) {
			return 0;
		}

		const boost::regex e(regex, flag);
		const std::regex e_std(regex, flag_std);
		if (e.status()) { // std::regex has no status()
			std::cout << "Incorrect regex pattern!\n";
			continue;
		}

		std::cout << "String to match: ";
		while (std::getline(std::cin, str) && not str.empty()) {
			bool matched = boost::regex_match(str, e);
			bool matched_std = std::regex_match(str, e_std);

			
			std::cout << "Boost: " << (matched ? "MATCH\n" : "DOES NOT MATCH\n");
			std::cout << "C++11: " << (matched_std ? "MATCH\n" : "DOES NOT MATCH\n");
			std::cout << "String to match: ";
		}

		std::cin.ignore();
		std::cin.clear();
	} while(1);
}

