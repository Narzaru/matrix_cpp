CC := gcc -std=c++17
CC_LANG := -xc++
CPP_STD_LIB := -lstdc++
LIBS := -lm
GTEST_CFLAGS := `pkg-config --cflags gtest`
GTEST_LIBS := `pkg-config --libs gtest`

all: s21_matrix_oop.a test
	./test


s21_matrix_oop.a:
	$(CC) -c -o s21_matrix_oop.o s21_matrix_oop.cpp $(LIBS) $(CPP_STD_LIB)
	ar rcs $@ s21_matrix_oop.o
	ranlib $@

test: s21_matrix_oop.a
	$(CC) $(GTEST_CFLAGS) -o $@ ./tests/main_tests.cpp $^ -I. $(CPP_STD_LIB) $(LIBS) $(GTEST_LIBS)

.PHONY: clean linter

clean:
	rm -f test
	find . -name "*.out" -delete
	find . -name "*.o" -delete
	find . -name "*.a" -delete

linter:
	cp ../materials/linters/CPPLINT.cfg .
	find . -name "*.cpp" -exec python3 ../materials/linters/cpplint.py {} \;
	find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	rm -f CPPLINT.cfg

main.out: clean s21_matrix_oop.a
	$(CC) -o main.out main.cpp s21_matrix_oop.a $(CPP_STD_LIB) $(LIBS)
	./main.out
