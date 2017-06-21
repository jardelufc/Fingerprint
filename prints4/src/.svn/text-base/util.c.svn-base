/************************************************************************/
/*		This package of subroutines contained in		*/
/*		"util.c" are designed for use with the 			*/
/*		software in this package.				*/
/*									*/
/*		File  Name:  util.c					*/
/*									*/
/*		Routines:    syserr()					*/
/*			     fatalerr()					*/
/*			     low_priority_abort()			*/
/*			     PixPerByte()				*/
/*			     SizeFromDepth()				*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

#define NEW_PRIORITY		(PRIO_MAX - 4)


/* LINTLIBRARY */

/*
 * Modified 12/19/90 by Stan Janet to dump core at low priority
 *	if environment variable ABORT is set
 */

void syserr(funcname, syscall, msg)
char *funcname, *syscall, *msg;
{
   extern int errno, sys_nerr;
   extern char *sys_errlist[], *getenv();
   int err;

   err = errno;

   (void) fflush(stdout);
   if(msg == NULL)
      (void) fprintf(stderr,"ERROR: %s: %s (%d",funcname,syscall,err);
   else
      (void) fprintf(stderr,"ERROR: %s: %s: %s (%d",funcname,syscall,msg,err);
   if(err > 0 && err < sys_nerr)
      (void) fprintf(stderr,"; %s)\n",sys_errlist[err]);
   else
      (void) fprintf(stderr,")\n");
   (void) fflush(stderr);

   if (getenv("ABORT") != NULL)
	low_priority_abort();

   exit(-1);
}


/* LINTLIBRARY */

/*
 * Stan Janet
 *
 * Modified 12/19/90 by Stan Janet to dump core at low priority if
 *	environment variable ABORT is set
 */

void fatalerr(s1,s2,s3)
char *s1, *s2, *s3;
{
extern char *getenv();

(void) fflush(stdout);
if (s2 == (char *) NULL)
	(void) fprintf(stderr,"ERROR: %s\n",s1);
else if (s3 == (char *) NULL)
	(void) fprintf(stderr,"ERROR: %s: %s\n",s1,s2);
else
	(void) fprintf(stderr,"ERROR: %s: %s: %s\n",s1,s2,s3);
(void) fflush(stderr);

if (getenv("ABORT") != (char *) NULL)
	low_priority_abort();

exit(1);
}


/* LINTLIBRARY */

/*
 * Stan Janet
 * December 12/19/90
 */

low_priority_abort()
{
extern int errno;
int p;

errno = 0;
p = getpriority(PRIO_PROCESS,0);
if ((p == -1) && errno)
	/* return value of -1 is ok unless errno changed */
	perror("fatalerr: getpriority failed");
else
	if ((p<NEW_PRIORITY) && (setpriority(PRIO_PROCESS,0,NEW_PRIORITY)<0))
		perror("fatalerr: setpriority failed");

(void) signal(SIGIOT,SIG_DFL);
(void) abort();
(void) pause();

exit(1);		/* should never get here */
}


/************************************************************/
/*         Routine:   PixPerByte()                          */
/*         Author:    Michael D. Garris                     */
/*                    Darrin Dimmick                        */
/*         Date:      3/07/90                               */
/*         Modifications:                                   */
/*           9/20/90    (Stan Janet) error message          */
/************************************************************/
/************************************************************/
/* PixPerByte() takes the pixel depth of an image and       */
/* returns the corresponding pixperbyte factor.             */
/************************************************************/
float PixPerByte(depth)
int depth;
{
   float pixperbyte;

   switch(depth){
   case 1:
      pixperbyte = 8.0;
      break;
   case 2:
      pixperbyte = 4.0;
      break;
   case 4:
      pixperbyte = 2.0;
      break;
   case 8:
      pixperbyte = 1.0;
      break;
   case 16:
      pixperbyte = 0.5;
      break;
   case 32:
      pixperbyte = 0.25;
      break;
   default:
      fatalerr("PixPerByte",
	"depth is not a power of 2 between 1 and 32 (inclusive)",
	NULL);
   }
   return pixperbyte;
}


/************************************************************/
/*         Routine:   SizeFromDepth()                       */
/*         Author:    Michael D. Garris                     */
/*                    Darrin Dimmick                        */
/*         Date:      2/20/90                               */
/*         Modifications:                                   */
/*           9/20/90   (Stan Janet) add ceil() [bug]        */
/************************************************************/
/************************************************************/
/* SizeFromDepth() takes the pixel width of an image scan   */
/* line along with the pixel height of the image, and using */
/* the argument "depth" computes the length of the image in */
/* bytes.                                                   */
/************************************************************/
int SizeFromDepth(pixwidth,pixheight,depth)
int pixwidth,pixheight,depth;
{
   int filesize;
   float pixperbyte,PixPerByte();

   pixperbyte = PixPerByte(depth);
   filesize = ((int) ceil(pixwidth/pixperbyte) * pixheight);
   return filesize;
}
