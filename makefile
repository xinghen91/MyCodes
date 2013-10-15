# this is a makefile of the c project main
# the standard c compiler on GNU linux is gcc
# written by xinghen on October 12th, 2013

                    TARGET = .

                        GCC = gcc
                     CFLAGS = -g -Wall
                     CFLAGC = -g -c

                        SRC = t.c
                       OBJS = t.o
                       EXEC = main

					INCLUDE = -I/usr/include/python2.7 
					LIBS = -L/usr/lib -lpython2.7 

all: $(EXEC)

$(EXEC): $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) $(LIBS) -o $@
	rm -f $(OBJS)

$(OBJS): $(SRC)
	$(GCC) $(CFLAGC) $(SRC) $(INCLUDE)

install:
	cp $(EXEC) /usr/local/bin

uninstall:
	rm -f /usr/local/bin/$(EXEC)

clean:
	rm -f $(EXEC)
