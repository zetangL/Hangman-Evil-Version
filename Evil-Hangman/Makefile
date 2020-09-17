CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o my_string.o generic_vector.o tree.o
OBJECTS2 = main.o my_string.o unit_test.o test_def.o generic_vector.o tree.o

ALL : string_driver unit_test
unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o

string_driver: $(OBJECTS)
	$(CC) -g  $(CFLAGS) $(OBJECTS) -o string_driver
my_string.o: my_string.c my_string.h
	$(CC) -g  $(CFLAGS) -c my_string.c -o my_string.o
main.o:main.c my_string.h generic_vector.h tree.h
	$(CC) -g  $(CFLAGS) -c main.c -o main.o

unit_test.o: unit_test.c unit_test.h
	$(CC) -g  $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: test_def.c unit_test.h
	$(CC) -g $(CFLAGS) -c test_def.c -o test_def.o

generic_vector.o: generic_vector.c  generic_vector.h
	$(CC) -g $(CFLAGS) -c generic_vector.c -o generic_vector.o

tree.o: tree.c tree.h
	$(CC) -g $(CFLAGS) -c tree.c -o tree.o

clean:
	rm string_driver unit_test $(OBJECTS2)
