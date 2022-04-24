all:
	g++ --std=c++17 main.cpp matrix.cpp -o a.out -fsanitize=address -g
	./a.out

test:
	clear
	g++ ./tests/main_tests.cpp matrix.cpp -I. `pkg-config --cflags --libs gtest` -o test.out -fsanitize=address -g
	./test.out

linter:
	cp ../materials/linters/CPPLINT.cfg .
	find . -name "*.cpp" -exec python3 ../materials/linters/cpplint.py {} \;
	find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	rm -f CPPLINT.cfg

clean:
	find . -name "*.out" -delete