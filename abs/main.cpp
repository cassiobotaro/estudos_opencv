#include <iostream>
#include "opencv2/highgui/highgui.hpp"

using namespace std;

int main()
{
    IplImage* imagem1 = cvLoadImage("cruzeiro_tux_2010_normal.png");
    IplImage* imagem2 = cvLoadImage("th_2013.png");
    IplImage* resultado = cvCloneImage(imagem1);
    IplImage* resultado2 = cvCloneImage(imagem1);
    cvAbsDiff(imagem1,imagem2,resultado);
    cvAbsDiffS(resultado,resultado2,cvScalar(100,0,0,0));
    cvShowImage("Resultado:",resultado);
    cvShowImage("Scalar:",resultado2);
    cvWaitKey();
    return 0;
}
