CFLAGS+=-std=c99
COVERAGE_FLAGS=--coverage

test: clean
	@gcc -g -I src/ src/utf8v.c src/thc.c tests/test_utf8v.c $(CFLAGS) \
	-o test -DDEBUG=1
	@./test

coverage:
	gcc -g -I src/ src/utf8v.c src/thc.c \
		  tests/test_utf8v.c \
		  $(CFLAGS) $(COVERAGE_FLAGS) $(LIBS) -o coverage_utf8v -DDEBUG=0 -DTEST=1
	      ./coverage_utf8v
		  lcov --directory . --capture --output-file app.info
		  genhtml --output-directory coverage/ app.info

clean:
	rm -f *.o
	rm -f *.a
	rm -rf coverage/
	rm -f  *.gcno *.gcda
	rm -f app.info
	rm -f  test
	rm -f  coverage_utf8v
