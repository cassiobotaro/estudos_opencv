#include <iostream>
#include "opencv2/highgui/highgui.hpp"

using namespace std;

int main()
{
    IplImage* imagem1 = cvLoadImage("cruzeiro_tux_2010_normal.png");
    IplImage* imagem2 = cvLoadImage("th_2013.png");
     CvSize tamanho = cvSize(
                              (int)imagem1->width,
                              (int)imagem1->height
                              );
     IplImage* resultado = cvCreateImage(tamanho,IPL_DEPTH_8U,3);
    cvAdd(imagem1,imagem2,resultado);
    IplImage* imagem3 = cvCloneImage(imagem1);
    cvAddS(imagem1,cvScalar(0,10,30,100) ,imagem3);
    cvShowImage("Resultado:",resultado);
    cvShowImage("Scalar:",imagem3);
    cvWaitKey();
    return 0;
}
