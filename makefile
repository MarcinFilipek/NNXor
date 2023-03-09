CC = gcc
CFLAGS = -g -Wall

INCLUDES = -I lib

LFAGS =

LIBS =

SRCS = src/main.c src/neuron.c src/func.c src/neural_network.c src/memory.c

OBJS = $(SRCS:.c=.o)

MAIN = NNXor

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN).exe $(OBJS) $(LFAGS) $(LIBS) -lm


.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^