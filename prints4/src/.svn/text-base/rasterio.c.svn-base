/****************************************************************/
/*	   This package of subroutines are used for reading	*/
/*	   and writing an image using the NIST Ihead format.	*/
/*								*/
/*		File Name:  rasterio.c				*/
/*								*/
/*		Contents:   ReadIheadRaster()			*/
/*			    writeihdrfile()			*/
/*								*/
/****************************************************************/

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <ihead.h>
#include <jpeg.h>

/************************************************************/
/*         Routine:   ReadIheadRaster()                     */
/*         Author:    Michael D. Garris                     */
/*         Date:      4/28/89                               */
/*         Modifications:                                   */
/*           8/90 Stan Janet                                */
/*                     only malloc 1 buffer if data is not  */
/*                        compressed                        */
/*                     free() up temp buffer                */
/*           9/20/90 Stan Janet                             */
/*                     check return codes                   */
/*           1/11/91 Stan Janet                             */
/*                     put filename in error messages       */
/************************************************************/
/************************************************************/
/* ReadIheadRaster() reads in a "iheadered" raster file and */
/* returns an ihead structure, raster data, and integer file*/
/* specs.                                                   */
/************************************************************/
void ReadIheadRaster(file,head,data,width,height,depth)
char *file;
IHEAD **head;
unsigned char **data;
int *width,*height,*depth;
{
   FILE *fp;
   IHEAD *readihdr();
   IHEAD *ihead;
   int outbytes, comp, filesize, complen, n;
   unsigned char *indata, *outdata;

   /* open the image file */
   fp = fopen(file,"r");
   if (fp == NULL)
      syserr("ReadIheadRaster",file,"fopen failed");

   /* read in the image header */
   *head = readihdr(fp);
   ihead = *head;

   n = sscanf((*head)->compress,"%d",&comp);
   if (n != 1)
      fatalerr("ReadIheadRaster",file,"sscanf failed on compress field");

   /* convert string fields to integers */
   n = sscanf((*head)->depth,"%d",depth);
   if (n != 1)
      fatalerr("ReadIheadRaster",file,"sscanf failed on depth field");
   n = sscanf((*head)->width,"%d",width);
   if (n != 1)
      fatalerr("ReadIheadRaster",file,"sscanf failed on width field");
   n = sscanf((*head)->height,"%d",height);
   if (n != 1)
      fatalerr("ReadIheadRaster",file,"sscanf failed on height field");
   n = sscanf((*head)->complen,"%d",&complen);
   if (n != 1)
      fatalerr("ReadIheadRaster",file,"sscanf failed on complen field");

   /* allocate a raster data buffer */
   filesize = SizeFromDepth(*width,*height,*depth);
   outdata = (unsigned char *) malloc(filesize);
   if(outdata == NULL)
      syserr("ReadIheadRaster",file,"malloc (outdata)");

   /* read in the raster data */
   if(comp == UNCOMP) {   /* file is uncompressed */
      n = fread(outdata,1,filesize,fp);
      if (n != filesize) {
         (void) fprintf(stderr,
		"ReadIheadRaster: %s: fread returned %d (expected %d)\n",
		file,n,filesize);
         exit(1);
      } /* IF */
   } else {
      indata = (unsigned char *) malloc(complen);
      if (indata == NULL)
	syserr("ReadIheadRaster",file,"malloc (indata)");
      n = fread(indata,1,complen,fp); /* file compressed */
      if (n != complen) {
         (void) fprintf(stderr,
		"ReadIheadRaster: %s: fread returned %d (expected %d)\n",
		n,complen);
         exit(1);
      } /* IF */
   }

   switch (comp) {
      case UNCOMP:
        *data = outdata;
      break;
      default:
         fatalerr("ReadIheadRaster",file,"Invalid compression code");
      break;
   }
   /* close the image file */
   (void) fclose(fp);
}


/************************************************************/
/*         Routine:   Writeihdrfile()                       */
/*         Author:    Michael D. Garris                     */
/*         Date:      4/26/89                               */
/*         Modifications:                                   */
/*           9/20/90   (Stan Janet) check return codes      */
/*           2/20/91   (MDG) compression capability         */
/************************************************************/
/************************************************************/
/* Writeihdrfile() writes a ihead structure and correspon-  */
/* ding image data to the specified file.                   */
/************************************************************/
void writeihdrfile(file,head,data)
char *file;
IHEAD *head;
unsigned char *data;
{
   FILE *fp;
   char lenstr[SHORT_CHARS];
   int i,width,height,depth,code,filesize,n;

   /* reopen the image file for writing */
   fp = fopen(file,"w");
   if (fp == NULL)
      syserr("writeihdrfile","fopen",file);

   n = sscanf(head->width,"%d",&width);
   if (n != 1)
      fatalerr("writeihdrfile","sscanf failed on width field",NULL);
   n = sscanf(head->height,"%d",&height);
   if (n != 1)
      fatalerr("writeihdrfile","sscanf failed on height field",NULL);
   n = sscanf(head->depth,"%d",&depth);
   if (n != 1)
      fatalerr("writeihdrfile","sscanf failed on depth field",NULL);
   n = sscanf(head->compress, "%d", &code);
   if (n != 1)
      fatalerr("writeihdrfile","sscanf failed on compression code field",NULL);

   filesize = SizeFromDepth(width,height,depth);

   if(code == UNCOMP){
      sprintf(head->complen, "%d", 0);
      writeihdr(fp,head);
      n = fwrite(data,1,filesize,fp);
      if (n != filesize)
         syserr("writeihdrfile", "fwrite", file);
   }
   else{
      fatalerr("writeihdrfile","Unknown compression",NULL);
   }

   /* closes the new file */
   (void) fclose(fp);
}
