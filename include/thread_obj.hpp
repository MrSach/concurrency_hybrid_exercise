#pragma once

#include <memory>
#include <mutex>
#include <iostream>
#include <cstdlib>

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

public:
	thread_obj ();
	~ thread_obj () = default;
	thread_obj (const thread_obj & obj) = delete;
	thread_obj (thread_obj && resource);

	/*
		Function object - operator () - declaration.
	*/
	void operator () ();
};

/*
	Generate vector for thread object with Functor as threaded function.
*/
std::unique_ptr <std::vector <std::unique_ptr <std::thread> > > thread_gen ();
