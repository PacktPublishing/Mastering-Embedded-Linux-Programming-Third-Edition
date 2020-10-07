CFLAGS = -Wall -g -I../inc
OBJECTS = testlib.o
 
all: libtest.a

# Build the static library
libtest.a: $(OBJECTS)
	ar rc libtest.a $(OBJECTS)

testlib.o: testlib.c
	$(CC) $(CFLAGS) -c testlib.c

clean:
	rm -f $(OBJECTS)
	rm -f libtest.a

