#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"

int main(int argc , char** argv)
{
    CvCapture* captura = cvCreateFileCapture("../Lupi.AVI");
    if (!captura){
    printf("não foi possível carregar o vídeo.");
    return 0;
    }
     double fps = cvGetCaptureProperty(captura,CV_CAP_PROP_FPS);
    CvSize tamanho = cvSize(
                            (int)cvGetCaptureProperty(captura,CV_CAP_PROP_FRAME_WIDTH),
                            (int)cvGetCaptureProperty(captura,CV_CAP_PROP_FRAME_HEIGHT)
                            );
    CvVideoWriter* videoescrito = cvCreateVideoWriter("copia.avi",CV_FOURCC('M','J','P','G'),fps,tamanho,1);
    IplImage *frame;
    while((frame = cvQueryFrame(captura))!=NULL){
        IplImage* logpolar_frame = cvCreateImage(tamanho,IPL_DEPTH_8U,3);
        cvLogPolar(frame,logpolar_frame,cvPoint2D32f(frame->width/2,frame->height/2),40,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS+CV_WARP_INVERSE_MAP);
        cvWriteFrame(videoescrito,logpolar_frame);
        cvShowImage("Vídeo",frame);
    char c =cvWaitKey(33);
    if(c==27)break;
    }
    cvReleaseVideoWriter(&videoescrito);
    cvReleaseCapture(&captura);
    cvDestroyAllWindows();
    return 0;
}
