#include "thread_obj.hpp"

bool thread_obj::set_output_total (const std::size_t & loops)
{
	thread_obj::output_total = loops;
	return 1;
}

/*
	Delegate to another constructor.
	This passes the default number of loops as an argument, but following redesign, this is unlikely to be necessary now.
*/
thread_obj::thread_obj
()
:
	thread_obj {concurrency_hybrid_exercise::loops_default}
{

}

/*
	For the constructor, pass the number of loops to be run for the object.
*/
thread_obj::thread_obj
(const std::size_t & output_count)
:
	obj_id {(thread_obj::total_created) + 1}
{
	++ thread_obj::total_created;
}

/*
	Move Constructor
*/
thread_obj::thread_obj (thread_obj && resource)
:
	obj_id {resource.obj_id}
{
	resource.obj_id = 0;
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

	for (size_t i {0}; i < this->output_total; ++i)
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
