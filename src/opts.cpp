#include <boost/program_options.hpp>
#include <iostream>
#include <cstdlib>
#include <thread>

#include "globals.hpp"
#include "opts.hpp"

opts::action opts::process_program_arg (int argc, char ** argv)
{
	std::cout << std::endl;

	/*
		Generate the help prompt using boost::program_options.
		Tailor to suit this program.
		Then generate a map for variables and a flag to display the help prompt in case of an error.
	*/
	boost::program_options::options_description od ("Program option specifics:");
	od.add_options()
	("help,h", "Display help")
	("threads,t", boost::program_options::value <std::size_t> (), "Assign specified number of threads to run")
	("loops,l", boost::program_options::value <std::size_t> (), "Assign specified number of loops to run for each thread");
	boost::program_options::variables_map vm;
	bool display_help {0};

	/*
		If there is an error in parsing command line arguments, notify the user.
		Also flag to proceed with the help menu.
	*/
	try
	{
		boost::program_options::store (boost::program_options::parse_command_line (argc, argv, od), vm);
		boost::program_options::notify (vm);
	}
	catch (...)
	{
		std::cerr << "Error occurred - please either clear argument list or follow the help guide below." << std::endl;
		display_help = 1;
	}

	/*
		Displays the help menu and returns the enum class value for help.
		This is reached either because the user entered an argument to request for help, or that there was an error in parsing an argument.
	*/
	if (vm.count ("help") || display_help == 1)
	{
		std::cout << od << std::endl;
		std::cout << std::endl;
		return opts::action::help;
	}

	/*
		If the arguments are ok and no help is requested, check individual arguments.
	*/
	std::cout << "Processing any arguments that may have been entered..." << std::endl;

	/*
		Check for threads.
	*/
	if (vm.count ("threads") )
	{
		/*
			Override existing value for the number of threads with the user-defined value.
		*/
		opts::thread_number = (vm ["threads"].as <std::size_t> () );
		std::cout << "Thread number assigned to " << opts::thread_number << std::endl;
	}
	else
	{
		/*
			If no value is given for threads, check the number of threads supported by the CPU.
			Double the number of threads if it supports at least the default number of threads.
			If not, keep it at the default.
			At the time of writing, the default is 8.
		*/
		std::cout << "Threads not specified, checking CPU hardware information..." << std::endl;
		std::size_t thread_count {std::thread::hardware_concurrency()};
		if (thread_count >= opts::thread_number)
		{
			std::cout << "CPU can run up to " << thread_count << " threads." << std::endl;
			opts::thread_number *= 2;
			std::cout << "Threads to run assigned to " << opts::thread_number << std::endl;
		}
		else
		{
			std::cout << "CPU below threshold, using minimum value of " << opts::thread_number << std::endl;
		}
	}

	/*
		Check the argument for loops.
		If given, override with the user-defined value.
	*/
	if (vm.count ("loops") )
	{
		opts::loop_number = (vm ["loops"].as <std::size_t> () );
		std::cout << "Each thread set to loop " << opts::loop_number << " times" << std::endl;
	}
	else
	{
		std::cout << "Loops not specified, using default value of " << opts::loop_number << std::endl;
	}

	std::cout << std::endl;

	opts::act = opts::action::arged;
	return opts::action::arged;
}

const std::size_t opts::get_threads ()
{
	return opts::thread_number;
}

const std::size_t opts::get_loopers ()
{
	return opts::loop_number;
}

opts::action opts::get_action ()
{
	return opts::act;
}
