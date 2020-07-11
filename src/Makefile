scmp: main.o options.o recursive_file_search.o read_file.o
	clang++ main.o options.o recursive_file_search.o read_file.o -O0 -Wall -std=c++17 -o scmp

recursive_file_search.o: recursive_file_search.cpp
	clang++ -c -O0 recursive_file_search.cpp -Wall -std=c++17

options.o: options.cpp
	clang++ -c -O0 options.cpp -Wall -std=c++17

main.o: main.cpp
	clang++ -c -O0 main.cpp -Wall -std=c++17

read_file.o: read_file.cpp
	clang++ -c -O0 read_file.cpp -Wall -std=c++17

clean:
	rm -rf *.o
    
