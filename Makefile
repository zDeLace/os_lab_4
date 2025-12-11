CC = gcc
CFLAGS = -fPIC -O2 -I./include

all: libimpl_naive.so libimpl_fast.so prog_static prog_dynamic

libimpl_naive.so: src/impl_naive.c include/contracts.h
	$(CC) $(CFLAGS) -shared -o $@ src/impl_naive.c

libimpl_fast.so: src/impl_fast.c include/contracts.h
	$(CC) $(CFLAGS) -shared -o $@ src/impl_fast.c

prog_static: src/prog_static.c libimpl_naive.so
	$(CC) -I./include -o $@ src/prog_static.c ./libimpl_naive.so

prog_dynamic: src/prog_dynamic.c
	$(CC) -I./include -ldl -o $@ src/prog_dynamic.c

clean:
	rm -f *.so prog_static prog_dynamic
