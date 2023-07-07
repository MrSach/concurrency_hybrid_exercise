
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
	Generate the smart pointer to the vector to the smart pointer to threads.
	To simplify this very nested variable returned here, this essentially stores a vector of threads on the heap.
	unique_ptr does not incur the instance counter performance penalty that is regularly encountered when using shared_ptr.
	Another reason for this design decision is the incompatibility with using shared_ptr in some <algorithm> functions, especially before recent C++ standards!
*/
std::unique_ptr <std::vector <std::unique_ptr <std::thread> > > thread_gen ()
{
	std::unique_ptr <std::vector <std::unique_ptr <std::thread> > > arr
	{std::make_unique <std::vector <std::unique_ptr <std::thread> > > ()};

	for (size_t i {1}; i <= opts::get_threads(); ++i)
	{
		/*
			Debug - used for checking dynamic memory allocation
		*/

		arr->push_back
		(
			std::make_unique <std::thread> (thread_obj (opts::get_loopers()) )
		);
	}

	return arr;
}

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
		*/
		opts::action act
		{
			opts::process_program_arg (argc, argv)
		};

		if (act == opts::action::help)
		{
			return 0;
		}
	}

	/*
		Get the loop count from the program options argument object and buffer to the thread_obj object.
		This Functor is used to loop through each thread and to write to the output stream.
	*/
	thread_obj::set_output_total(opts::get_loopers());

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
