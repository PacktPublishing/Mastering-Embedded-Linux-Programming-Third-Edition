CFLAGS := -Wall -g -fPIC -I../inc
OBJECTS := testlib.o
 
all: libtest.so

# Build the shared library
libtest.so: $(OBJECTS)
	$(CC) -shared -o libtest.so $(OBJECTS)

testlib.o: testlib.c
	$(CC) $(CFLAGS) -c testlib.c

clean:
	rm -f $(OBJECTS)
	rm -f libtest.so

