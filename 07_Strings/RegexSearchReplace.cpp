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

		std::cout.flush();

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

	std::string regex, str, replace_string;
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
			boost::smatch results;
			bool matched = boost::regex_search(str, results, e);

			std::smatch results_std;
			bool matched_std = std::regex_search(str, results_std, e_std);


			if (matched) {
				std::cout << "Boost: MATCH: ";
				std::copy(results.begin() + 1,
					        results.end(),
									std::ostream_iterator<std::string>(std::cout, ", "));

				std::cout << "\nReplace pattern: ";
				if (std::getline(std::cin, replace_string) && not replace_string.empty()) {
					std::cout << "RESULT (Boost): " << boost::regex_replace(str, e, replace_string);
				}
				else {
					std::cin.ignore();
					std::cin.clear();
				}
			}
			else {
				std::cout << "\nBoost: DOES NOT MATCH\n";
			}


			if (matched_std) {
				std::cout << "\nC++11: MATCH: ";
				std::copy(results_std.begin() + 1,
					        results_std.end(),
									std::ostream_iterator<std::string>(std::cout, ", "));

				std::cout << "\nReplace pattern: ";
				if (std::getline(std::cin, replace_string) && not replace_string.empty()) {
					std::cout << "RESULT (C++11): " << std::regex_replace(str, e_std, replace_string) << "\n";
				}
				else {
					std::cin.ignore();
					std::cin.clear();
				}
			}
			else {
				std::cout << "\nC++11: DOES NOT MATCH\n";
			}
			
			std::cout << "String to match: ";
		}

		std::cin.ignore();
		std::cin.clear();
	} while(1);
}

