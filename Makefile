CC = gcc

AR = ar

I = -I include
IEXAMPLE = $(I) -I examples

SRC = src/fsm.c

CFLAGS = -std=c11 -Wall -Wextra -Werror -O2
LDFLAGS = -L lib
LDLIBS = -lfsm

EXAMPLE = examples/door_controller.c
EXECUTABLES = test/test_fsm examples/door_example

LIBFSM = lib/libfsm.a

all: $(LIBFSM)

$(LIBFSM): obj/fsm.o
	$(AR) rcs $@ obj/fsm.o

obj/fsm.o: src/fsm.c
	$(CC) $(I) $(CFLAGS) -c $(SRC) -o $@

test: obj/test_fsm.o $(LIBFSM)
	$(CC) $(IEXAMPLE) $(CFLAGS) obj/test_fsm.o $(LDFLAGS) $(LDLIBS) -o test/test_fsm
	./test/test_fsm

obj/test_fsm.o: test/test_fsm.c $(LIBFSM)
	$(CC) $(IEXAMPLE) $(CFLAGS) -c test/test_fsm.c $(LDLIBS) $(LDFLAGS) -o obj/test_fsm.o

example: obj/door_example.o $(LIBFSM)
	$(CC) obj/door_example.o $(I) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -o examples/door_example

obj/door_example.o: $(LIBFSM)
	$(CC) -c $(EXAMPLE) $(I) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -o obj/door_example.o

clean:
	rm -f $(LIBFSM) obj/*.o $(EXECUTABLES)
