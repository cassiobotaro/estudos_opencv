#include <stdio.h>
#include <stdlib.h>
#include "opencv2/highgui/highgui.hpp"
#include "cv.h"
IplImage* doPyrDown(IplImage* in,int filter){
    assert(in->width%2 == 0 && in->height%2 == 0);
    IplImage* out= cvCreateImage(cvSize(in->width/2,in->height/2),in->depth,in->nChannels);
    cvPyrDown(in,out,filter);
    return (out);
}
IplImage* doCanny(IplImage* in,double lowThresh,double highThresh,double aperture){
    IplImage* versaoCinza = cvCreateImage(cvGetSize(in),IPL_DEPTH_8U,1);
    if(in->nChannels != 1 ){
        cvCvtColor(in,versaoCinza,CV_RGB2GRAY);
    }else
    {
        versaoCinza = in;
    }
    IplImage* out = cvCreateImage(cvGetSize(in),IPL_DEPTH_8U,1);
    cvCanny(versaoCinza,out,lowThresh,highThresh,aperture);
    return(out);
}

int main(int argc, char** argv)
{
    IplImage *imagem = cvLoadImage(argc>=2?argv[1]:"lena.jpg",CV_LOAD_IMAGE_ANYCOLOR);
    if(!imagem)
    {
        printf("Não foi possivel carregar sua imagem com sucesso.");
        return 0;
    }
    IplImage* imagemReduzida = doPyrDown(imagem,IPL_GAUSSIAN_5x5);
    IplImage* imagemCanny = doCanny(imagem,10,100,3);
    cvShowImage("imagem normal",imagem);
    cvShowImage("imagem reduzida",imagemReduzida);
    cvShowImage("imagem com efeito Canny",imagemCanny);
    cvWaitKey(0);
    cvReleaseImage(&imagem);
    cvReleaseImage(&imagemReduzida);
    cvReleaseImage(&imagemCanny);
    cvDestroyAllWindows();
    return 0;
}
