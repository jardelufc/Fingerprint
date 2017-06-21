/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%     C o n v o l v e I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ConvolveImage() applies a custom convolution kernel to the image.
%
%  The format of the ConvolveImage method is:
%
%      Image *ConvolveImage(const Image *image,const unsigned int order,
%        const double *kernel,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o order: The number of columns and rows in the filter kernel.
%
%    o kernel: An array of double representing the convolution kernel.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
void ConvolveImage(BYTE *pcDataDest, BYTE *pcDataSrc, int nDiameter, BYTE cOrder, const int *kernel)
{
	int x,y, bSubDiameter, nSubOrder, value;
	BYTE *pdest, *psrc, *pOrigSource;
	int *pmask;

	if ((cOrder % 2) == 0) {
		return;
	}
	if (nDiameter < cOrder) {
		return;
	}
	nSubOrder = cOrder/2;

	nSubDiameter = nDiameter - (cOrder-1);
	pdest = pcDataDest + nDiameter*(nSubOrder+1);
	pOrigSource = pcDataSrc;
	for (y=0; y < SubDiameter; y++)
	{
		for (x=0; x < nSubDiameter; x++)
		{
			nValue = 0;
			pmask = kernel;
			psrc = pOrigSource;
			for (u=0; u < cOrder; u++)
			{
				for (v=0; v < cOrder; v++)
				{
					value += (*psrc)*(*pmask);
					pmask++;
				}
				psrc += (nDiameter-cOrder);
			}
			*pdest = value;
			pOrigSource++;
		}
		pdest += (cOrder);
	}
}
