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
    CvVideoWriter* videoescrito = cvCreateVideoWriter("copia.avi",CV_FOURCC('M','J','P','G'),fps,tamanho,0);
    IplImage *frame;
    while((frame = cvQueryFrame(captura))!=NULL){
    IplImage* imagemgray = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
    cvCvtColor(frame,imagemgray,CV_RGB2GRAY);
    cvWriteFrame(videoescrito,imagemgray);
    cvShowImage("Vídeo",frame);
    cvShowImage("Preto e Branco",imagemgray);
    char c =cvWaitKey(33);
    if(c==27)break;
    }
    cvReleaseVideoWriter(&videoescrito);
    cvReleaseCapture(&captura);
    cvDestroyAllWindows();
    return 0;
}

