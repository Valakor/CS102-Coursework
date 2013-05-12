# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall
LDFLAGS =


all : gmlwriter.o gmlreader.o lex.yy.o gml.tab.o user.o sn.o
	@echo "Compiling and linking"
	$(CC) $(CFLAGS) gmlwriter.o gmlreader.o lex.yy.o gml.tab.o user.o sn.o -o sn

user.o : user.h user.cpp
	$(CC) $(CFLAGS) -c user.cpp

gmlreader.o : gmlreader.h gmlreader.cpp
	$(CC) $(CFLAGS) -c gmlreader.cpp

gmlwriter.o : user.h gmlwriter.h mylist.h gmlwriter.cpp
	$(CC) $(CFLAGS) -c gmlwriter.cpp

lex.yy.o: lex.yy.c gml.tab.h gml.tab.c
	$(CC) $(CFLAGS) -w -c lex.yy.c

lex.yy.c: gml.lex gml.tab.c
	flex -f gml.lex

gml.tab.o: gml.tab.c
	$(CC) $(CFLAGS) -w -c gml.tab.c

gml.tab.c: gml.y
	bison -d gml.y

sn.o : user.h mylist.h sn.cpp
	$(CC) $(CFLAGS) -c sn.cpp


clean:
	rm -f sn *.o *~


