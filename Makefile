	CC=gcc
CFLAGS=-c
LIBS=-lgmp
TARGET=factorisation

all: $(TARGET)

$(TARGET): main.o table_operations.o pollardrho.o division_sucessive.o pollard_minus_1.o
	$(CC) $^ -o $@ $(LIBS)

main.o: main.c table_operations.h pollardrho.h division_sucessive.h pollard_minus_1.h
	$(CC) $(CFLAGS) $< -o $@

table_operations.o: table_operations.c table_operations.h
	$(CC) $(CFLAGS) $< -o $@

pollardrho.o: pollardrho.c pollardrho.h
	$(CC) $(CFLAGS) $< -o $@

division_sucessive.o: division_sucessive.c division_sucessive.h
	$(CC) $(CFLAGS) $< -o $@

pollard_minus_1.o: pollard_minus_1.c pollard_minus_1.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(TARGET)
