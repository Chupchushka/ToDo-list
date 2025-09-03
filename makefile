all:
	clang++ -o main src/main.cpp -lsqlite3
	./main
clean:
	rm -f main