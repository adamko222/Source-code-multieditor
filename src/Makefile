scmp: main.o options.o recursive_file_search.o
	clang++ -O3 main.o options.o recursive_file_search.o -Wall -std=c++17 -o scmp

recursive_file_search.o: recursive_file_search.cpp
	clang++ -c -O3 recursive_file_search.cpp -Wall -std=c++17

options.o: options.cpp
	clang++ -c -O3 options.cpp -Wall -std=c++17

main.o: main.cpp
	clang++ -c -O3 main.cpp -Wall -std=c++17

read_file.o: read_file.cpp
	clang++ -c -O3 read_file.cpp -Wall -std=c++17

clean:
	rm -rf *.o
    
