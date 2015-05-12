#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>

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
        cvShowImage("Vídeo",frame);
        cvWriteFrame(videoescrito,frame);
        char c =cvWaitKey(33);
        if(c==27)break;
    }
    cvReleaseVideoWriter(&videoescrito);
    cvReleaseImage(&frame);
    cvReleaseCapture(&captura);
    cvDestroyAllWindows();
    return 0;
}


