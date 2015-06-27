BINARY  = server
CC      = g++
CFLAGS  = -pthread -std=c++14
FILES   = $(shell find . -name "*.cpp")
HEADERS = $(shell find . -name "*.h")
OBJS    = $(FILES:.cpp=.o)
	 
all: $(BINARY)

${BINARY}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${BINARY}

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${BINARY} ${OBJS}
