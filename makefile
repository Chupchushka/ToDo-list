all:
	clang++ -o clist src/main.cpp -lsqlite3
	sudo ln -s /Users/chupchushka/ToDo-list/clist /usr/local/bin/clist
	echo "Build complete."

clean:
	sudo rm /usr/local/bin/clist
	rm -f clist
	rm -f db.sqlite3
	echo "Clean complete."

rebuild: clean all
	echo "Rebuild complete."

test: rebuild
	clist -a "Test task 1"
	clist -a "Test task 2"
	clist -a "Test task 3"

	clist -t "urgent" "red" 1
	clist -t "work" "green" 2
	clist -t "personal" "yellow" 3

	echo "Test complete."