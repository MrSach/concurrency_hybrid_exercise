#pragma once

#include <cstdlib>

#include "globals.hpp"

class opts
{
	public:
		/*
			Although the program argument handler is designed as a class, it is not designed to be instantiated.
			Instead, member attributes are static as only one argument handler is needed here!
		*/
		opts () = default;
		~ opts () noexcept = default;
		opts (const opts & po) = default;

		/*
			Enumeration - after some redesigns, only "help" and "arged" are actually used now.
			Store these as unsigned long integers according to machine architecture.
			Remember to keep this public access as this enumeration itself is used both in the object source and elsewhere in the program.
		*/
		enum class action : std::size_t {help = 0, arged = 1};

		/*
			This processes the arguments passed into the program.
		*/
		static opts::action process_program_arg (int argc, char ** argv);

		/*
			Getter functions.
			No need for setters as the mechanism is already handled by opts::process_program_arg (int, char **)
		*/
		static const std::size_t get_threads ();
		static const std::size_t get_loopers ();
		static opts::action get_action ();

	protected:

		/*
			Member attributes.
			Assign the threads and loops to the defult number to begin with and override later.
		*/
		static inline std::size_t thread_number {concurrency_hybrid_exercise::threads_default};
		static inline std::size_t loop_number {concurrency_hybrid_exercise::loops_default};
		static inline opts::action act {opts::action::help};

	private:
};
