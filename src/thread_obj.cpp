#include <thread>
#include <memory>
#include <vector>
#include <cstdlib>

#include "opts.hpp"
#include "thread_obj.hpp"

/*
	For the constructor, initialise to the ID of the object.
	Increment the total number of thread objects.
*/
thread_obj::thread_obj
()
:
	obj_id {(thread_obj::total_created) + 1}
{
	++ thread_obj::total_created;
}

/*
	Move Constructor
	Take the ID of the existing object.
	Do not increment the object counter because the resource is being moved, not copied!
*/
thread_obj::thread_obj (thread_obj && resource)
:
	obj_id {resource.obj_id}
{
	
}

/*
	Function that contains the thread to be joined.
*/
void thread_obj :: operator () ()
{
	/*
		Lock the thread in the Functor.
		While the thread is locked, run the loops and output the thread ID and the memory address of the Functor.
		As the lock guard is an RAII resource, when the function finishes, the lock guard destructor is called as it falls out of scope.
	*/
	std::lock_guard <std::mutex> thread_control (thread_obj::obj_m);

	for (std::size_t i {0}; i < opts::get_loopers(); ++i)
	{
		std::cout << "Thread ";
		std::cout << std::dec;
		std::cout << this -> obj_id;
		std::cout << std::endl;
		std::cout << "Object ";
		std::cout << std::hex;
		std::cout << this;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

/*
	Generate the smart pointer to the vector to the smart pointer to threads.
	To simplify this very nested variable returned here, this essentially stores a vector of threads on the heap.
	unique_ptr does not incur the instance counter performance penalty that is regularly encountered when using shared_ptr.
	Another reason for this design decision is the incompatibility with using shared_ptr in some <algorithm> functions, especially before recent C++ standards!
	This function has been added to thread_obj.cpp because thread_obj is the Functor in this program.
*/

std::unique_ptr <std::vector <std::unique_ptr <std::thread> > > thread_gen ()
{
	std::unique_ptr <std::vector <std::unique_ptr <std::thread> > > arr
	{std::make_unique <std::vector <std::unique_ptr <std::thread> > > ()};

	for (std::size_t i {1}; i <= opts::get_threads(); ++i)
	{
		/*
			Debug - used for checking dynamic memory allocation
		*/

		arr->push_back
		(
			std::make_unique <std::thread> (thread_obj () )
		);
	}

	return arr;
}

