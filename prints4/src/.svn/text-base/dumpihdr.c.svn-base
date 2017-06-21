/************************************************************/
/*         File Name: Dumpihdr.c                            */
/*         Package:   NIST Standard Image Header            */
/*         Author:    Michael D. Garris                     */
/*         Date:      4/26/89                               */
/************************************************************/
#include <stdio.h>
#include <ihead.h>

/************************************************************/
/* Read in an image header from a given image file and      */
/* print it to standard output.                             */
/************************************************************/
main(argc,argv)
int argc;
char *argv[];
{
   FILE *fp;
   IHEAD *head,*readihdr();
   char *imagefile;

   procargs(argc,argv,&imagefile);
   /* open the image file */
   if((fp = fopen(imagefile,"r")) == NULL){
      fprintf(stderr,"Unable to open ihead file %s.\n",imagefile);
      exit(-1);
   }
   /* read in the header */
   head = readihdr(fp);
   /* close the image file */
   fclose(fp);
   /* dump the header info to standard output */
   printihdr(head,stdout);
   /* free the header structure */
   free(head);
}

procargs(argc,argv,filename)
int argc;
char *argv[],**filename;
{
   if(argc < 2){
      fprintf(stderr,"Usage: dumpihdr <image file>\n");
      exit(-1);
   }
   *filename = argv[1];
}
