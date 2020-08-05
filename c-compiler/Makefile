compiler: compiler.cpp
		  g++ compiler.cpp -o compiler

test: compiler
	  (./compiler test/input01; \
	   ./compiler test/input02; \
	   ./compiler test/input03; \
	   ./compiler test/input04; \
	   ./compiler test/input05)

clean:
	rm compiler