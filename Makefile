CC=arm-frc-linux-gnueabi-g++-4.9
#CC=g++
CSTRIP=arm-frc-linux-gnueabi-strip
CFLAGS=-Wall --sysroot=/usr/arm-frc-linux-gnueabi -mfpu=neon $(shell pkg-config --cflags opencv)
#-mfpu=neon
LIBS=$(shell pkg-config --libs --cflags opencv)

all: main

lib: CFLAGS += -shared -fPIC
lib: libvision.so

main: main.o CamFeed.o TargetDetector.o Viewer.o
	$(CC) $(CFLAGS) main.o CamFeed.o TargetDetector.o Viewer.o -o $@ $(LIBS)

example: libvision.so test.cpp
	$(CC) $(CFLAGS) -L. -o $@ test.cpp -lvision

libvision.so: CamFeed.o TargetDetector.o Viewer.o VisionLib.o
	$(CC) $(CFLAGS) CamFeed.o TargetDetector.o Viewer.o VisionLib.o -o $@ $(LIBS)

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp $(LIBS)

VisionLib.o: VisionLib.cpp
	$(CC) -c $(CFLAGS) VisionLib.cpp $(LIBS)

CamFeed.o: CamFeed.cpp
	$(CC) -c $(CFLAGS) CamFeed.cpp $(LIBS)

TargetDetector.o: TargetDetector.cpp
	$(CC) -c $(CFLAGS) TargetDetector.cpp $(LIBS)

Viewer.o: Viewer.cpp
	$(CC) -c $(CFLAGS) Viewer.cpp $(LIBS)

clean:
	rm -f *.o main *.so example

strip: main
	$(CSTRIP) main

lib/strip: lib
	$(CSTRIP) libvision.so
