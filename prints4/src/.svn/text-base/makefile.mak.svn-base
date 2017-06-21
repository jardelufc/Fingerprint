HDIR = .
IDIR = $(HDIR)
INCLUDES = -I$(IDIR)

CFLAGS = -O3 $(INCLUDES)

LIBS= -lm

DEFS = $(IDIR)/ihead.h \
	$(IDIR)/jpeg.h 

all: dumpihdr ihdr2sun ihdr2raw

dumpihdr: dumpihdr.o ihead.o $(IDIR)/ihead.h
	cc -O3 -o dumpihdr dumpihdr.o ihead.o $(LIBS)

ihdr2raw: ihdr2raw.o rasterio.o util.o ihead.o $(IDIR)/ihead.h
	cc -O3 -o ihdr2raw ihdr2raw.o rasterio.o util.o ihead.o -lm

ihdr2sun: ihdr2sun.o ihead.o rasterio.o util.o sun.o $(DEFS)
	cc -O3 -o ihdr2sun ihdr2sun.o ihead.o rasterio.o util.o sun.o $(LIBS)

dumpihdr.o: dumpihdr.c $(IDIR)/ihead.h
ihead.o: ihead.c $(IDIR)/ihead.h
rasterio.o: rasterio.c $(DEFS)
util.o: util.c $(DEFS)
ihdr2sun.o: ihdr2sun.c $(DEFS)
sun.o: sun.c
