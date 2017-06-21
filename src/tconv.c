#include <defs.h>
#include <refpoint.h>
#include <ihead.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>


// Operador de sobel na direção y
int kernely[3][3] = 	{
								{-1, 0, 1},
								{-2, 0, 2},
								{-1, 0, 1}
							};
// Operador de sobel na direção x							
int kernelx[3][3] = 	{
								{-1, -2, -1},
								{0, 0, 0},
								{1, 2, 1}
							};

int main(int argc, char **argv)
{
	char szName [20], szCommand[100];
	IHEAD *head;
	float *pcDataDestx, *pcDataDesty;
	BYTE *data, *pdata;
	int nRet;
	float *pOrientedImage, *pSmoothedOrientedImage;
	int width, height, depth;
	BYTE acTemplate[10];
	int i,xc,yc, nWidth, nHeight;

	memset (acTemplate,0,10);
	GenerateTemplate (acTemplate, 2*15);
	printf("\n");

	for(i=0;i<10;i++)
		printf("%d ",acTemplate[i]);
	printf("\n");

	if (pcDataDesty==NULL || pcDataDestx==NULL) {
		printf ("Malloc Error\n");
		exit(1);
	}
	ReadIheadRaster(argv[1],&head,&data,&width,&height,&depth);
	/*pdata = data;
	for(i=0;i<(512*512);i++,pdata++)
		if(*pdata>124)
			*pdata = 0xFF;
	writeihdrfile("imx2.pct",head,data);
   	system("./cjpegb 100 jpg imx2.pct");*/
	
	
	printf ("width=%d heigth=%d\n", width, height);
	// Calcula o gradiente na direção y utilizando o operador de sobel
	pcDataDesty=ConvolveImage(data, width, 3, &kernely[0][0]);
	// Calcula o gradeiente na direção x utilizando o operador de sobel
	pcDataDestx=ConvolveImage(data, width, 3, &kernelx[0][0]);
	// Divide a imagem em blocos que não se sobrepõem e calcula a orientação de cada bloco
	pOrientedImage = ComputeOrientedImage(pcDataDestx,pcDataDesty, 512-2,512-2, 15);
	nWidth= (512-2)/15;
	nHeight=(512-2)/15;
	//pSmoothedOrientedImage = SmoothOrientedImage (pOrientedImage, nWidth,nHeight, 5);
	pSmoothedOrientedImage=SmoothOrientedImage(pOrientedImage, nWidth, 5);
	
	nWidth -=4;
	nHeight-=4;
	FindRefPoint (&xc, &yc,pSmoothedOrientedImage, nWidth, nHeight, acTemplate);
	PlaceMarkAtXY (data,512,512,xc,yc);
	printf("\n\nxc = %d yc = %d\n\n",xc, yc);
	writeihdrfile("imx1.pct",head,data);
   	system("./cjpegb 100 jpg imx1.pct");
	return 1;
}

	//writeihdrfile("imsobely.pct",head,pcDataDesty);
   	//system("./cjpegb 100 jpg imsobely.pct");
	//writeihdrfile("imsobelx.pct",head,pcDataDestx);
   	//system("./cjpegb 100 jpg imsobelx.pct");

