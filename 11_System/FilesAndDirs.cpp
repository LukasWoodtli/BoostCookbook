#include <iostream>
#include <fstream>
#include <cassert>

#include <boost/filesystem/operations.hpp>


int main() {

	/////////////////////////////////////////////////////////
	///// Listing files in a directory //////////////////////
	/////////////////////////////////////////////////////////


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



	/////////////////////////////////////////////////////////
	///// Erasing and creating files and directories ////////
	/////////////////////////////////////////////////////////

	boost::system::error_code error;

	// boost::filesystem::create_directory can not create subdirectories
	boost::filesystem::create_directories("dir/subdir", error);
	assert(!error);

	std::ofstream ofs("dir/subdir/file.txt");
	ofs << "Boost.filesystem is fun!";
	assert(ofs);
	ofs.close();

	boost::filesystem::create_directory_symlink("dir/subdir", "symlink", error);

	if (!error) {
		std::cout << "Symlink created\n";
		assert(boost::filesystem::exists("symlink/file.txt"));
	}
	else {
		// remove file if symlink creation failed
		std::cerr << "Failed to create symlink\n";
		boost::filesystem::remove("dir/subdir/file.txt", error);
		assert(!error);
	}

}
