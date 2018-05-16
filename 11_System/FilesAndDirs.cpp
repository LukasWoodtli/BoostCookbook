#include <iostream>

#include <boost/filesystem/operations.hpp>


int main() {
	boost::filesystem::directory_iterator begin(".");
	boost::filesystem::directory_iterator end;
	
	for (; begin != end; ++begin) {
		boost::filesystem::file_status fs = begin->status();

		switch (fs.type()) {
			case boost::filesystem::regular_file:
				std::cout << "File      ";
				break;
			case boost::filesystem::symlink_file:
				std::cout << "SYMLINK   ";
				break;
			case boost::filesystem::directory_file:
				std::cout << "DIRECTORY ";
				break;
			default:
				std::cout << "OTHER     ";
				break;
		}

		if (fs.permissions() & boost::filesystem::owner_write) {
			std::cout << "W ";
		}
		else {
			std::cout << "  ";
		}
		
		std::cout << begin->path() << '\n';
	}
}
