#include <stdio.h>
#include <stdlib.h>
#include "opencv2/highgui/highgui.hpp"

int main()
{
    IplImage* imagem1 = cvLoadImage("imagem.jpg",CV_LOAD_IMAGE_COLOR);
    IplImage* imagem2 = cvLoadImage("imagem2.jpg",CV_LOAD_IMAGE_COLOR);
    CvSize size = cvGetSize(imagem1);
    IplImage* resultado = cvCreateImage(size,IPL_DEPTH_8U,3);
    IplImage* resultado2 = cvCreateImage(size,IPL_DEPTH_8U,3);
    cvAbsDiff(imagem1,imagem2,resultado);
    cvAbsDiffS(resultado,resultado2,cvScalar(0,0,255,0));//vermelho
    cvShowImage("Resultado:",resultado);
   cvShowImage("Scalar:",resultado2);
    cvWaitKey(0);
    return 0;
}
