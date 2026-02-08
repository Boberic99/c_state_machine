CC = gcc

AR = ar

I = -I include
IEXAMPLE = $(I) -I examples

SRC = src/fsm.c

CFLAGS = -std=c11 -Wall -Wextra -Werror -O2
LDFLAGS = -L lib
LDLIBS = -lfsm

TEST = -c test/test_fsm.c
EXAMPLE = -c examples/door_controller.c 
EXECUTABLES = test/test_fsm examples/door_example

LIBFSM = lib/libfsm.a

all: $(LIBFSM)

$(LIBFSM): obj/fsm.o
	$(AR) rcs $@ obj/fsm.o

obj/fsm.o: src/fsm.c
	$(CC) $(I) $(CFLAGS) -c $(SRC) -o $@

test: obj/test_fsm.o $(LIBFSM) obj/door_model.o
	$(CC) $(IEXAMPLE) $(CFLAGS) obj/door_model.o obj/test_fsm.o $(LDFLAGS) $(LDLIBS) -o test/test_fsm
	./test/test_fsm

obj/test_fsm.o: test/test_fsm.c $(LIBFSM) obj/door_model.o
	$(CC) $(IEXAMPLE) $(CFLAGS) $(TEST) $(LDLIBS) $(LDFLAGS) -o obj/test_fsm.o

example: obj/door_example.o obj/door_model.o $(LIBFSM)
	$(CC) obj/door_example.o obj/door_model.o $(I) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -o examples/door_example

obj/door_example.o: $(LIBFSM)
	$(CC) $(EXAMPLE) $(I) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -o obj/door_example.o

obj/door_model.o: examples/door_model.c
	$(CC) $(IEXAMPLE) -c $^ -o $@

clean:
	rm -f $(LIBFSM) obj/*.o $(EXECUTABLES)
