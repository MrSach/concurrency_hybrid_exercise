# Concurrency - Hybrid Exercise

[![Terminal Program Example 1a](https://github.com/MrSach/concurrency_hybrid_exercise/blob/main/resource/image/thumb-1-a.png)](https://github.com/MrSach/concurrency_hybrid_exercise/blob/main/resource/image/thumb-1-a.png)

[![Terminal Program Example 1b](https://github.com/MrSach/concurrency_hybrid_exercise/blob/main/resource/image/thumb-1-b.png)](https://github.com/MrSach/concurrency_hybrid_exercise/blob/main/resource/image/thumb-1-b.png)

[![Terminal Program Example 1c](https://github.com/MrSach/concurrency_hybrid_exercise/blob/main/resource/image/thumb-1-c.png)](https://github.com/MrSach/concurrency_hybrid_exercise/blob/main/resource/image/thumb-1-c.png)





Starting in mid 2022, following steady progress on basic and intermediate C++ skills, I wanted to explore more advanced C++ techniques.
Clearly, I definitely had patience with C++, given the interest only grew through the intensive training and refinement of difficult concepts.
With adoption of multithreading over the years across software projects, it became evident that this would be a useful C++ skillset to explore.

Starting with simple online examples across geeksforgeeks, medium, tutorialspoint, cppreference, and various other resources, I felt ready to replicate and learn from the different techniques and examples, and sometimes made minor adjustments in order to observe the impacts, which were generally fine.
So far so good at this stage.
Having already trained hard in understanding Function Objects (Functors), function pointers and lambda functions, as well as a refined understanding of the application of objects using Resource Acquisition is Initialised (RAII), familiarising myself with `std::thread` was rapid and I soon began my journey with C++ concurrency.

First addressing the race conditions that broke thread safety, my first attempts to use the <mutex> library were successful.

Come late 2022 I was keen to experiment with a less conventional approach.
I wanted to experiment and to try using some skills learned earlier and to hybridise them with my next concurrency exercise.
Instead of limiting myself to a fixed number of statically allocated threads before runtime, I wanted a more flexible solution.
Heap allocation of threads was a desirable next outcome, as was the ability to determine the number of threads to allocate based on hardware.
Because of this, I considered using STL Containers to store threads and to allocate the Container objects using smart pointers.
A program that could use a dynamically calculated resource at runtime was my next target, and one that could allocate threads, themselves, on the heap, instead of being limited to the stack.
At the same time, I was weary of using C libraries in tandem with C++ STL objects.
If the C++ STL provided a use, then the STL was to be explored first.

Embracing a challenging journey with my next exercise, I spent months exploring how to work with using the `<thread>` library with `<mutex>` (`std::mutex` and `std::lock_guard<T>(std::mutex)`, `<memory>` (smart pointers to allocate memory to the heap instead of the stack), `<vector>` (STL containers), `<algorithm>` (the `std::for_each` function), `<iostream>` (writing to a shared resource, the output stream), and Functors.

Initially this proved very difficult and I found this experiment unrealistic.
Even Stack Overflow provided limited information for the obscure errors I encountered.
Perhaps I could decrypt the G++ diagnostics for each compilation error it threw?
The exercise was very demanding on the precise use of pointer syntax and I had to be very careful exactly when to dereference and the order of accesing memory addresses against accessing the values stored within them.
Eventually I managed to correct my errors in my syntax and managed to use the nested data types correctly.
Also taking care when to pass by value and when to pass by reference, and when to pass by pointer, I became much more confident with navigating through data using pointers and references.
This also gave a much greater appreciation for the use of RAII and how to use such objects that rely on it in C++.

Even with the pointers perfect and the scoping of object lifetimes tested, I was perplexed with thread safety issues.
Using `std::vector`s and `std::unique_ptr`s appeared to have broken the thread safety that was previously fine.
Persistent research saw me locate additional resources to persuade me to recondsider my methodology:
> https://stackoverflow.com/questions/23620533/thread-safe-vector

So, unsure whether the `std::vector` was even compatible with the `std::thread` data type, varying the use of STL Containers became the next workaround to this issue. Trying Queues, Deques, Arrays and Lists led to the same issue and I returned back to using vectors.
Perhaps the materials I consulted online were out of date?
The C++ STL is evolving faster these days and the mechanisms that it uses for data types is becoming more comprehensive.
Also having tried to use a mutex that did not belong to the Functor's class, I got stuck and found progress impossible.

Although I could have requested assistance with the project and posted questions on Stack Overflow, I felt weary of posting beginner questions and also queries related to experimental matters such as mine.
Instead of wasting moderators' time with such a foolish query, I decided to suspend this project and to focus on other matters, such as contributing code to open source projects and to build my brand further.
Come January 2023 I decided to withdraw a few steps back with concurrency and resume textbook learning.
C-style arrays worked well, which was good news, but I remained determined to reconsider the STL Container libraries and whether they can actually be used after all.
After some time away from multithreading, I resumed work on the suspended challenge from 2022.
In July 2023 I read a chapter on multithreading in Professional C++, 5th Edition.
Consulting the `<atomic>` examples, I attempted to replicate the `std::atomic_ref`, but found them inefficient (as was warned!) and also useless for managing thread safety in my example.
So, I decided that atomic variables were not appropriate for this particular challenge.

Exploring the section on mutexes, most of it appeared to be irrelevant.
However, there was one example that caught my attention.
The surprise of what it had in common for solving my particular problem led me to believe that this would be very easy to test in my program.
It featured a vector that stored threads in the main function.
It also used a Functor, which had a `std::lock_guard<T>` in the Functor's `operator ()` function, as well as a `std::mutex` member attribute.
One major difference had revealed something interesing.
The mutex in the book's example was declared as `static inline`.
I did attempt to use `static` before, but whether I also used `inline` was another question.
Having refactored my own code so many times, I considered that I may not have designed any solutions quite like the book's example.
Did I use `inline static` when declaring a class mutex?
Possibly, but possibly not.
Might as well try out to determine the result.
Amazingly, the `inline static` adjustment worked, and threads no longer interleaved.

So, at long last, after a year of starting this small, but educational journey, I have finally arrived at a working example of this unusual multithreading experiment.

Perhaps the next advancement is to explore thread management alongside lock-free methods?
Eventually I hope to also make use of GPU and CUDA programming libraries.

It would also be useful to develop multithreaded applications to read and write to shared resources with effective thread control.

----

# Compile from Source

POSIX systems:
Tested on the following system:
-  Linux 6.3.8-200
-  Fedora 38
-  GCC 13.1.1-4
-  boost-program-options-1.78.0-11

After cloning the repository onto your local machine, open a shell and assign the working directory as the root folder of the project.
Next, run `sh ./build_posix.sh` into a bash shell.
The resulting binary should be created here:
> ./bin/Release/concurrency_hybrid_exercise

Run the binary executable in a bash shell.

Note that program arguments are supported.
Add `--help` or `-h` after the executable path for more information.

Windows systems:
As this uses `std::thread`, it is recommended to use Cygwin and then follow the instructions for POSIX platforms in a Cygwin terminal shell.
I have not tested this in Windows yet, so this remains a work in progress.
Note: boost-program-options is a dependency, so that would also need to be installed and included when compiled and linked.

