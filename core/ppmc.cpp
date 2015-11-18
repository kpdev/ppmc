#include <boost/program_options.hpp>
#include <iostream>

namespace opt = boost::program_options;


int main(int argc, char *argv[])
{
	// Constructing an options describing variable and giving it a
	// textual description "All options"
	opt::options_description desc("All options");

	// When we are adding options, first parameter is a name
	// to be used in command line. Second parameter is a type
	// of that option, wrapped in value<> class. Third parameter
	// must be a short description of that option

	const char txt_help[]		("help");
	const char txt_file[]		("file");
	const char txt_output_path[]("output-path");

	desc.add_options()
		(txt_file, opt::value<std::string>(), "which file needs to be processed")
		(txt_output_path, opt::value<std::string>(), "path to processed file")
		(txt_help, "produce help message")
		;

	// Variable to store our command line arguments
	opt::variables_map vm;

	// Parsing and storing arguments
	opt::store(opt::parse_command_line(argc, argv, desc), vm);

	opt::notify(vm);

	if (vm.count(txt_help)) {
		std::cout << desc << "\n";
		return 1;
	}

	if (vm.count(txt_file) == 0 || vm.count(txt_output_path) == 0) {
		std::cout << "Wrong parameters\n";
		return 1;
	}

	std::cout << "File: "
		<< vm[txt_file].as<std::string>() 
		<< ", Path: "
		<< vm[txt_output_path].as<std::string>()
		<< std::endl;

	return 0;
}