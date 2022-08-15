include main_objects.h
#
PROGRAM = thepainter
#
CC = g++
CFLAGS = -g -Wall\
-I.. -I../../common
#
all: $(PROGRAM)
#
$(PROGRAM): $(main_objects) ../thepainter.o
	$(CC) -o $@ $(main_objects)\
        ../thepainter.o\
        ../../common/io/io.o\
        ../../common/jpeg/jpeg.o\
        ../../common/math/math.o\
        ../../common/png/png.o\
        ../../common/tiff/tiff.o\
        ../../common/util/util.o\
        -ltiff\
        -lpng\
        -ljpeg\
        -lz\
        -lm
#
.c.o:
	$(CC) -c $(CFLAGS) $<
