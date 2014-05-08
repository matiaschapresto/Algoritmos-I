# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS=-c

all: tpi

tpi: Test.o interfaz.o mainHoteles.o habitacion.o reserva.o hotel.o ministerio.o
	$(CC)  Test.o interfaz.o mainHoteles.o habitacion.o reserva.o hotel.o ministerio.o -o tpi

Test.o: Test.cpp
	$(CC) $(CFLAGS) Test.cpp
	
interfaz.o: interfaz.cpp
	$(CC) $(CFLAGS) interfaz.cpp
	
mainHoteles.o: mainHoteles.cpp
	$(CC) $(CFLAGS) mainHoteles.cpp

habitacion.o: habitacion.cpp
	$(CC) $(CFLAGS) habitacion.cpp

reserva.o: reserva.cpp
	$(CC) $(CFLAGS) reserva.cpp

hotel.o: hotel.cpp
	$(CC) $(CFLAGS) hotel.cpp

ministerio.o: ministerio.cpp
	$(CC) $(CFLAGS) ministerio.cpp

clean:
	rm -rf *o