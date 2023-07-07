/*
	Note: I could use block guards here, but I find #pragmas cleaner to read and write.
	Also, this is designed to be compiled with GCC 13.1.1.
*/

#pragma once

/*
	Declare globals under a namespace to demonstrate the use of namespaced data that is used throughout the program.
	This may also help to differentiate from local non-namespaced variables in function callbacks.
	For more frugal IDEs and text editors, which lack IntelliSense, etc., this also helps with identifying the origin without needing to use grep manually.
*/
namespace concurrency_hybrid_exercise
{

const std::size_t threads_default {8};
const std::size_t loops_default {100};

}
