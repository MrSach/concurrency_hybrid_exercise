
/*
	Program
		Concurrency - Hybrid Exercise

	Description
		Terminal program.
		Combines the application of vectors, smart pointers and threads using a function object (Functor).
		Also supports program argument handling.
		A class-wide mutex that is shared across each instance of the Functor object ensures that only one lock can be used in the function to write to the output stream and only one thread is permitted to access it at a time.

	Author
		Sacha

	Date
		7.7.2023
*/

#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <algorithm>
#include <memory>

#include "globals.hpp"
#include "opts.hpp"
#include "thread_obj.hpp"

/*
	Main function
*/
int main (int argc, char ** argv)
{

	std::cout << std::endl;

	/*
		Title
	*/
	std::cout << "Concurrency - Hybrid Exercise";

	/*
		Line breaks
	*/
	std::cout << std::endl;

	{
		/*
			Process arguments using the program arguments object, "opts".
			As the member attributes of relevance are static, just call the relevant member method of the class.
			If the program arguments are processed correctly, this will be "arged".
			If the user requests for help, or there is an error in processing the program arguments, this will instead default to "help" and the program will then terminate.
		*/
		opts::process_program_arg (argc, argv);

		if (opts::get_action() == opts::action::help)
		{
			return 0;
		}
	}

	/*
		Generate the smart pointer to the vector of threads using the function defined earlier.
	*/
	std::unique_ptr <std::vector <std::unique_ptr <std::thread> > >
	thread_capacity
	{
		thread_gen ()
	};

	/*
		Use an STL algorithm to go through each thread in the vector series.
		As STL threads are not designed to be copied, a reference is needed in order to be usable across functions.
		Each thread is then joined to the main program.
		As there is no return type, the void keyword has been used to explicitly define the output data type specifier.
		Because the vector is dynamically allocated through smart pointers, the vector needs to be accessed through the smart pointer, "thread_capacity".
		The vector itself in turn stores smart pointers to threads for each entry, so to access those another layer of smart pointer referencing is required here.
	*/
	std::for_each
	(
		thread_capacity->begin (),
		thread_capacity->end (),
		[]
		(std::unique_ptr <std::thread> & x )
		-> void
		{
			x.get()->join();
		}
	);

	/*
		Clear the threads after they have executed.
	*/
	thread_capacity->clear ();

	/*
		Add whitespace to the terminal console output at the end of the program.
	*/
	std::cout << std::endl;
	std::cout << std::endl;

	/*
		Return status - successful program execution.
	*/
	return 0;
}
