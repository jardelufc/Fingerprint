/************************************************************/
/*         File Name: Ihdr2sun.c                            */
/*         Package:   NIST Ihead to Sun Rasterfile          */
/*         Author:    Michael D. Garris                     */
/*         Date:      3/08/90                               */
/*                                                          */
/*         Modified 1/4/91 by Stan Janet:                   */
/*		exit(0) called if successful                */
/*		check fwrite return values                  */
/*         Modified 2/4/91 by Stan Janet:                   */
/*		"-o file" option added                      */
/*         Modified 2/6/91 by Stan Janet:                   */
/*		lint compliance                             */
/*		unlink sunfile on write error               */
/************************************************************/

#include <stdio.h>
#include <strings.h>
#include <rasterfile.h>
#include <ihead.h>

#define BUFSIZE		80
#define DEFAULTMAP	"gray.map"
#define SUNEXT		".ras"

/************************************************************/
/* Converts an NIST ihead image to a sun rasterfile.        */
/************************************************************/
main(argc,argv)
int argc;
char *argv[];
{
   int width,height,depth,filesize,maplength;
   struct rasterfile rasterhdr;
   char *filename, *mapfile, *outfile, sunfile[BUFSIZE];
   unsigned char *data, *map;
   IHEAD *ihead;
   FILE *fp;

   procargs(argc,argv,&filename,&mapfile,&outfile);

   ReadIheadRaster(filename,&ihead,&data,&width,&height,&depth);
   if((depth != 1) && (depth != 8)){
      (void) fprintf(stderr,"Pixel depth of %d is not currently supported.\n",
              depth);
      exit(-1);
   }

   rasterhdr.ras_magic = RAS_MAGIC;
   rasterhdr.ras_width = width;
   rasterhdr.ras_height = height;
   rasterhdr.ras_depth = depth;
   filesize = SizeFromDepth(width,height,depth);
   rasterhdr.ras_length = filesize;
   rasterhdr.ras_type = RT_STANDARD;

   if (depth == 8) {
      if (mapfile == (char *) NULL)
	mapfile = DEFAULTMAP;
      ReadSunColormap(mapfile, &map, &maplength);
      rasterhdr.ras_maplength = maplength;
      rasterhdr.ras_maptype = RMT_EQUAL_RGB;
   } else {
      maplength = 0;
      rasterhdr.ras_maplength = maplength;
      rasterhdr.ras_maptype = RMT_NONE;
   }

   if (outfile == (char *) NULL) {
	(void) strcpy(sunfile, filename);
	fileroot(sunfile);
	(void) strcat(sunfile, SUNEXT);
   } else
	(void) strcpy(sunfile, outfile);

   if ((fp = fopen(sunfile,"w")) == (FILE *) NULL) {
	(void) fprintf(stderr,"Unable to open file %s\n",sunfile);
	exit(-1);
   }

(void) fwrite((char *)&rasterhdr,1,sizeof(struct rasterfile),fp);

if (maplength != 0) {
	(void) fwrite((char *)map, 1, maplength, fp);
	free((char *) map);
}

(void) fwrite((char *)data,1,rasterhdr.ras_length,fp);

if (ferror(fp)) {
	(void) unlink(sunfile);
	fatalerr("ihdr2sun",sunfile,"write error");
}

(void) fclose(fp);

free((char *) ihead);
free((char *) data);

exit(0);
}


 
procargs(argc,argv,filename,mapfile,outfile)
int argc;
char *argv[], **filename, **mapfile, **outfile;
{
int c;
extern int getopt(), optind;
extern char *optarg;

*outfile = (char *) NULL;
*mapfile = (char *) NULL;

while ((c = getopt(argc,argv,"o:")) != EOF)
  switch (c) {
	case 'o':	*outfile = optarg;
			break;
	default:	usage();
  }

switch (argc - optind) {
  case 1:
	*filename = argv[optind];
	break;
  case 2:
	*filename = argv[optind];
	*mapfile = argv[optind+1];
	break;
  default:
	usage();
} /* switch */
}


usage()
{
(void) fprintf(stderr,"Usage:  ihdr2sun [-o outfile] <ihead file> [map file]\n");
exit(1);
}
