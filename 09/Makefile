default: run

run: gen sort check

gen: gen.cpp
	g++ gen.cpp -o gen --std=c++14 -O2
	./gen test 8

sort: main.cpp
	g++ main.cpp -o sort --std=c++14 -O2 -pthread
	./sort test

check: gen sort
	g++ check.cpp -o check --std=c++14 -O2
	./check

clean:
	rm -f gen
	rm -f sort
	rm -f check
