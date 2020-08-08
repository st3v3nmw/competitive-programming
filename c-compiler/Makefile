compiler: compiler.cpp
		  g++ compiler.cpp -o compiler

test: compiler
		./compiler test/input05 && cc -o a.out out/input05.s && ./a.out
	#   (./compiler test/input01 && cc -o a.out out/input01.s && ./a.out \
	#   ./compiler test/input02 && cc -o a.out out/input02.s && ./a.out; \
	#   ./compiler test/input03 && cc -o a.out out/input03.s && ./a.out; \
	#   ./compiler test/input04 && cc -o a.out out/input04.s && ./a.out; \
	#   ./compiler test/input05 && cc -o a.out out/input05.s && ./a.out)

clean:
	rm a.out compiler