CC=clang
CFLAGS+=-Wall -Wextra -Werror

%:
	mkdir -p bin
	$(CC) $(CFLAGS) $@.c -o bin/$@

.PRECIOUS: %.o

.PHONY: clean

clean:
	rm bin/*
	rm *.o
