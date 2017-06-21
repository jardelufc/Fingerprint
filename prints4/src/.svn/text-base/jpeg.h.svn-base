/****************************************************************/
/*								*/
/*		This header was created for use with		*/
/*		lossless jpeg decompression (designed		*/
/*		for 8 bit input precision)			*/
/*								*/
/*		File Name:     jpeg.h				*/
/*		developed by:  Craig Watson			*/
/*		date:          6 Nov 91				*/
/*								*/
/*		revisions/date: none				*/
/*								*/
/****************************************************************/


/*********************************/
/*variables used in decompression*/
/*********************************/

#define   MEMSIZE1    11        /*size memory needed for variable*/
#define   MEMSIZE2    10        /*size memory needed for variable*/
#define   LSBITMASK   0x0001    /*set and mask LSbit of 2 byte*/
#define   CATMASK     0x0100    /*mask used in categorize*/
#define   SHORTCODELENGTH  9    /*default value when searching for code length
				  in categorize*/
#define   FIRSTBIT    7 	/*first bit used in a byte*/
#define   NUMARGSDCP   2	/*number of input arguments*/
#define   BYTE         8	/*used to shift bytes*/
#define   BASE	       2        /*base in extend exponential operation*/
#define   SMALLESTDIFF -511     /*smallest possible difference pixel*/
#define   LARGESTDIFF  512      /*largest possble difference pixel*/


/*********************************/
/*structure used in decompression*/
/*********************************/

typedef struct hcode {			/*structure for huffman code table*/
   int size;
   unsigned int code;
} HUFFCODE;

typedef struct hcode *PTR_HUFFCODE;	/*ptr to huffman coding structure*/


/*****************************************************/
/*defines return type of jpeg decompression algorithm*/
/*****************************************************/

void jpegdecomp();			/*jpeg decompression*/
