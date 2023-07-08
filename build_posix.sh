mkdir -p bin/Release
mkdir -p obj/Release/src/
g++ -Wall -fexceptions -std=c++20 -g -O0 -Iinclude -Iinclude/ -Isrc/ -c main.cpp -o obj/Release/main.o
g++ -Wall -fexceptions -std=c++20 -g -O0 -Iinclude -Iinclude/ -Isrc/ -c src/opts.cpp -o obj/Release/src/opts.o
g++ -Wall -fexceptions -std=c++20 -g -O0 -Iinclude -Iinclude/ -Isrc/ -c src/thread_obj.cpp -o obj/Release/src/thread_obj.o
g++  -o bin/Release/concurrency_hybrid_exercise obj/Release/main.o obj/Release/src/opts.o obj/Release/src/thread_obj.o  -lboost_program_options  
