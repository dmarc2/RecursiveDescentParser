CXX = gcc
CXXFLAGS = -Wall

OBJS = main.o parser.o lexer.o symbol.o

prog1 : ${OBJS}
	        ${CXX} $(CXXFLAGS) -o $@ ${OBJS}

main.o : parser.o lexer.o symbol.o

parser.o : parser.h lexer.h
lexer.o : lexer.h parser.h
symbol.o : symbol.h

clean :
		rm ${OBJS}

