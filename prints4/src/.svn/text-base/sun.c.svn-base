/****************************************************************/
/* 	This group of subroutines are used in converting a NIST	*/
/*	Ihead raster image to a sun raster image.		*/
/*								*/
/*		File Name:  sun.c				*/
/*								*/
/*		Contents:   ReadSunColormap()			*/
/*			    fileroot()				*/
/*								*/
/****************************************************************/

#include <stdio.h>
#include <math.h>
#include <memory.h>

/************************************************************/
/*         Routine:   ReadSunColormap()                     */
/*         Author:    Michael D. Garris                     */
/*         Date:      3/07/90                               */
/************************************************************/
/************************************************************/
/* ReadSunColormap() loads into memory a sun raster color   */
/* map from the file mapfile.                               */
/************************************************************/
void ReadSunColormap(mapfile,map,maplength)
char *mapfile;
unsigned char **map;
int *maplength;
{
   FILE *fp;

   if((fp = fopen(mapfile,"r")) == NULL)
      syserr("ReadSunColormap","fopen",mapfile);
   fread(maplength,sizeof(int),1,fp);
   if(*maplength == 0)
      fatalerr("ReadSunColormap","Color map format error",mapfile);
   if(((*map) = (unsigned char *)malloc((*maplength))) == NULL)
      syserr("ReadSunColormap","malloc","map");
   fread((*map),sizeof(unsigned char),*maplength,fp);
   fclose(fp);
}


/************************************************************/
/*         Routine:   FileRoot()                            */
/*         Author:    Michael D. Garris                     */
/*         Date:      11/27/89                              */
/************************************************************/
/*************************************************************/
/* Fileroot() is a destructive procedure which takes a file  */
/* name and strips off the rightmost extension, if it exists.*/
/*************************************************************/

void fileroot(file)
char *file;
{
   char *cptr;

   cptr = file + strlen(file);
   while((cptr != file) && (*cptr != '.'))
      cptr--;
   if(*cptr == '.')
      *cptr = NULL;
}
