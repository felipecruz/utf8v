CFLAGS+=-std=c99

test: clean
	@gcc -g -I src/ src/utf8v.c src/thc.c tests/test_utf8v.c $(CFLAGS) \
	-o test -DDEBUG=1
	@./test

clean:
	@rm -f test
