CC := g++
STANDART := -std=c++17
CFLAG = -Wall -Wextra

GTEST_CFLAGS := `pkg-config --cflags gtest`
GTEST_LIBS := `pkg-config --libs gtest`
INCLUDE_PATHS := .
INCLUDE := $(addprefix -I,$(INCLUDE_PATHS))

all: s21_matrix_oop.a test

# lib build
./build/obj/s21_matrix_oop.o: s21_matrix_oop.cpp
	$(CC) $(STANDART) $(CFLAG) -c -o $@ $< $(INCLUDE)

s21_matrix_oop.a: ./build/obj/s21_matrix_oop.o
	ar -crs $@ $^
	ranlib $@

# test build
./build/tobj/s21_matrix_oop.o: s21_matrix_oop.cpp
	$(CC) --coverage $(STANDART) $(CFLAG) -c -o $@ $< $(INCLUDE)

./build/tobj/test.o: test.cpp
	$(CC) $(STANDART) $(GTEST_CFLAGS) $(CFLAG) -c -o $@ $< $(GTEST_LIBS) $(INCLUDE)

test: ./build/tobj/s21_matrix_oop.o ./build/tobj/test.o
	$(CC) $(STANDART) $(GTEST_CFLAGS) $(CFLAG) -o test $^ $(GTEST_LIBS) -lgcov $(INCLUDE)
	./test

gcov_report: test
	./test
	lcov --directory . -t "test" -o test.info -c --no-external
	genhtml -o gcov_report test.info
	@echo
	@echo report path is `pwd`/report/index.html

.PHONY: linter clean

main: s21_matrix_oop.a main.cpp
	g++ -o $@ main.cpp $<
	./$@

linter:
	@echo cpplint
	@cp ../materials/linters/CPPLINT.cfg .
	@find . -name "*.cpp" -exec python3 ../materials/linters/cpplint.py {} \;
	@find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	@rm -f CPPLINT.cfg

clean:
	@find . -name "*.a" -delete
	@find . -name "*.o" -delete
	@find . -name "*.gcda" -delete
	@find . -name "*.gcno" -delete
	@find . -name "*.info" -delete
	@rm -rf gcov_report
	@rm -f test
	@rm -f main
