/************************************************************/
/*         File Name: IHead.c                               */
/*         Package:   NIST Standard Image Header            */
/*                                                          */
/*         Contents:  Printihdr()                           */
/*                    Readihdr()                            */
/*		      Writeihdr()			    */
/************************************************************/
#include <stdio.h>
#include <math.h>
#include <ihead.h>

/************************************************************/
/*         Routine:   Printihdr()                           */
/*         Package:   NIST Standard Image Header            */
/*         Date:      4/26/89                               */
/************************************************************/
/************************************************************/
/* Printihdr() prints the contents of an ihead structure to */
/* the passed file pointer.                                 */
/************************************************************/
printihdr(head,fp)
IHEAD *head;
FILE *fp;
{
   int temp;

   fprintf(fp,"IMAGE FILE HEADER\n");
   fprintf(fp,"~~~~~~~~~~~~~~~~~\n");
   fprintf(fp,"Identity\t:  %s\n", head->id);
   fprintf(fp,"Header Size\t:  %d (bytes)\n",sizeof(IHEAD));
   fprintf(fp,"Date Created\t:  %s\n", head->created);
   fprintf(fp,"Width\t\t:  %s (pixels)\n",head->width);
   fprintf(fp,"Height\t\t:  %s (pixels)\n",head->height);
   fprintf(fp,"Bits per Pixel\t:  %s\n",head->depth);
   fprintf(fp,"Resolution\t:  %s (ppi)\n",head->density);
   fprintf(fp,"Compression\t:  %s (code)\n",head->compress);
   fprintf(fp,"Compress Length\t:  %s (bytes)\n",head->complen);
   fprintf(fp,"Scan Alignment\t:  %s (bits)\n",head->align);
   fprintf(fp,"Image Data Unit\t:  %s (bits)\n",head->unitsize);
   if(head->byte_order == HILOW)
      fprintf(fp,"Byte Order\t:  High-Low\n");
   else
      fprintf(fp,"Byte Order\t:  Low-High\n");
   if(head->sigbit == MSBF)
      fprintf(fp,"MSBit\t\t:  First\n");
   else
      fprintf(fp,"MSBit\t\t:  Last\n");
   fprintf(fp,"Column Offset\t:  %s (pixels)\n",head->pix_offset);
   fprintf(fp,"White Pixel\t:  %s\n",head->whitepix);
   if(head->issigned == SIGNED)
      fprintf(fp,"Data Units\t:  Signed\n");
   else
      fprintf(fp,"Data Units\t:  Unsigned\n");
   fprintf(fp,"Scan Order\t:  ");
   if(head->rm_cm == ROW_MAJ)
      fprintf(fp,"Row Major,\n");
   else
      fprintf(fp,"Column Major,\n");
   if(head->tb_bt == TOP2BOT)
      fprintf(fp,"\t\t   Top to Bottom,\n");
   else
      fprintf(fp,"\t\t   Bottom to Top,\n");
   if(head->lr_rl == LEFT2RIGHT)
      fprintf(fp,"\t\t   Left to Right\n");
   else
      fprintf(fp,"\t\t   Right to Left\n");

   if(*(head->parent) != 0){
      fprintf(fp,"Parent\t\t:  %s\n",head->parent);
      fprintf(fp,"X Origin\t:  %s (pixels)\n",head->par_x);
      fprintf(fp,"Y Origin\t:  %s (pixels)\n",head->par_y);
   }
}

/************************************************************/
/*         Routine:   Readihdr()                            */
/*         Author:    Michael D. Garris                     */
/*         Date:      4/26/89                               */
/************************************************************/
/************************************************************/
/* Readihdr() allocates and reads header information into an*/
/* ihead structure and returns the initialized structure.   */
/************************************************************/
IHEAD *readihdr(fp)
FILE *fp;
{
   IHEAD *head;
   char lenstr[SHORT_CHARS];
   int len;

   fread(lenstr,sizeof(char),SHORT_CHARS,fp);
   sscanf(lenstr,"%d",&len);
   if(len != IHDR_SIZE){
      fprintf(stderr,
         "Record Sync Error: Header not found or old format.\n");
      exit(-1);
   }
   head = (IHEAD *)malloc(sizeof(IHEAD));
   fread(head,sizeof(char),len,fp);
   return(head);
}


/************************************************************/
/*         Routine:   Writeihdr()                           */
/*         Author:    Michael D. Garris                     */
/*         Date:      2/08/90                               */
/************************************************************/
/************************************************************/
/* Writeihdr() writes the fixed length field and the header */
/* passed to the given file pointer.                        */
/************************************************************/
void writeihdr(fp,ihead)
FILE *fp;
IHEAD *ihead;
{
   int i;
   char lenstr[SHORT_CHARS];

   for (i = 0; i < SHORT_CHARS; i++)
      lenstr[i] = '\0';
   /* creates a string from of header size */
   sprintf(lenstr,"%d",sizeof(IHEAD));
   /* writes the length string in headerto the file */
   fwrite(lenstr,sizeof(char),SHORT_CHARS,fp);
   /* writes the given header to the file */
   fwrite(ihead,sizeof(IHEAD),1,fp);
}
