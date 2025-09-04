all:
	clang++ -o clist src/main.cpp -lsqlite3
	sudo ln -s /Users/chupchushka/ToDo-list/clist /usr/local/bin/clist
	echo "Build complete."
clean:
	sudo rm /usr/local/bin/clist
	rm -f clist
	rm -f db.sqlite3
	echo "Clean complete."