#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"

int main(int argc, char** argv)
{
    IplImage *imagem = cvLoadImage("lena.jpg",CV_LOAD_IMAGE_ANYCOLOR);
    if(!imagem)
    {
        printf("Não foi possivel carregar sua imagem com sucesso.");
        return 0;
    }
    IplImage* imagemsmooth = cvCreateImage(cvGetSize(imagem),IPL_DEPTH_8U,3);
    cvSmooth(imagem,imagemsmooth,CV_GAUSSIAN,0,0,4,0);
    cvShowImage("imagem normal",imagem);
    cvShowImage("imagem transformada",imagemsmooth);
    cvWaitKey(0);
    cvReleaseImage(&imagem);
    cvReleaseImage(&imagemsmooth);
    cvDestroyAllWindows();
    return 0;
}
