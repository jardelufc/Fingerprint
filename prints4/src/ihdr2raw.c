#include<ihead.h>
#include<stdio.h>


main(argc,argv)
   int argc;
   char **argv;
{
   IHEAD *head;
   FILE *fpout;
   unsigned char *data;
   int width, height, depth;
   int i;

   if(argc != 3)
      fatalerr(argv[0],"Usage: ihdr2raw <ihd file> <raw file>",NULL);

   ReadIheadRaster(argv[1],&head,&data,&width,&height,&depth);

   if((fpout = fopen(argv[2],"w")) == NULL)
      syserr(argv[0],"fopen","fpout");

   i = fwrite(data,sizeof(unsigned char),(width*height),fpout);
   if(i != (width*height))
      syserr(argv[0],"fwrite","i");
   fclose(fpout);
}
