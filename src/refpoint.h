#ifndef __REFPOINT_H
#define __REFPOINT_h

#include <defs.h>

float * ComputeOrientedImage (float *pcDataSrcx,float *pcDataSrcy, int nHeight,int nWidth, int w);
void GenerateTemplate (BYTE *pcTemplate, int nDiameter);
//float *SmoothOrientedImage (float *pO, int nHeight,int nWidth, int nOrder);
int FindRefPoint (int *xc, int *yc,float *pO, int nHeight, int nWidth, BYTE *pcTemplate);
int *PlaceMarkAtXY (BYTE *pcDataSrc, int nHeight,int nWidth, int nX, int nY);
float *ConvolveImage(BYTE *pcDataSrc, int nDiameter, int nOrder, int *kernel);
float *SmoothOrientedImage(float *pcDataSrc, int nDiameter, int nOrder);


#endif

