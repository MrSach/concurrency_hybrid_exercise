#pragma once

#include <mutex>
#include <iostream>
#include <cstdlib>

#include "globals.hpp"

/*
	Functor Object.
	This object contains a mutex and is therefore contained within the class.
*/
class thread_obj
{
protected:

	/*
		Mutex object.
		Belongs to the class and not to instances.
		Needs to be inline here, although the reason is unclear.
	*/
	static inline std::mutex obj_m {};

	/*
		Object ID, which can be assigned to a different number, depending on the number of instances created.
	*/
	std::size_t obj_id;

	/*
		It's called an inline.
		Use it!
		c++17 features are very useful here!
		This belongs to the class itself and will determine the number of instances created.
	*/
	static inline size_t total_created {0};

	/*
		This is the number of times to write the output on the output stream.
	*/
	static inline size_t output_total {concurrency_hybrid_exercise::loops_default};

public:
	thread_obj ();
	thread_obj (const size_t & output_count);
	~ thread_obj () = default;
	thread_obj (const thread_obj & obj) = default;
	thread_obj (thread_obj && resource);

	static bool set_output_total (const std::size_t & loops);

	/*
		Function object - operator () - declaration.
	*/
	void operator () ();
};
