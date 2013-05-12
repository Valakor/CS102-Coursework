# Name: Mark Redekopp
# email: redekopp@usc.edu

CC = g++
CFLAGS = -g -Wall
LDFLAGS =

all: sn bc
	@echo "Building sn and bc"

sn: gmlwriter.o gmlreader.o lex.yy.o gml.tab.o user.o sn.o
	@echo "Compiling and linking sn"
	$(CC) $(CFLAGS) gmlwriter.o gmlreader.o lex.yy.o gml.tab.o user.o sn.o -o sn

bc: gmlwriter.o gmlreader.o lex.yy.o gml.tab.o user.o bcuser.o bcalg.o bc.o
	@echo "Compiling and linking bc"
	$(CC) $(CFLAGS) gmlwriter.o gmlreader.o lex.yy.o gml.tab.o user.o bcuser.o bcalg.o bc.o -o bc

user.o: user.h user.cpp
	$(CC) $(CFLAGS) -c user.cpp

bcuser.o: bcuser.h bcuser.cpp
	$(CC) $(CFLAGS) -c bcuser.cpp
	
bcalg.o: bcalg.h bcalg.cpp
	$(CC) $(CFLAGS) -c bcalg.cpp

gmlreader.o: gmlreader.h gmlreader.cpp
	$(CC) $(CFLAGS) -c gmlreader.cpp

gmlwriter.o: user.h gmlwriter.h mylist.h gmlwriter.cpp
	$(CC) $(CFLAGS) -c gmlwriter.cpp

lex.yy.o: lex.yy.c gml.tab.h gml.tab.c
	$(CC) $(CFLAGS) -w -c lex.yy.c

lex.yy.c: gml.lex gml.tab.c
	flex -f gml.lex

gml.tab.o: gml.tab.c
	$(CC) $(CFLAGS) -w -c gml.tab.c

gml.tab.c: gml.y
	bison -d gml.y

sn.o: user.h mylist.h sn.cpp
	$(CC) $(CFLAGS) -c sn.cpp

bc.o: user.h mylist.h bcuser.h bcuser.cpp bcalg.h
	$(CC) $(CFLAGS) -c bc.cpp

clean:
	rm -f sn bc *.o *~ *.gch
