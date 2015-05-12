#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
CvCapture* captura = NULL;
int posicao_slider = 0;
void onTrackbarSlide(int pos){
    cvSetCaptureProperty(captura,CV_CAP_PROP_POS_FRAMES,pos);
}
int main(int argc , char** argv)
{
    captura = cvCreateFileCapture("../Lupi.AVI");
    if (!captura){
        printf("não foi possível carregar o vídeo.");
        return 0;
    }
    cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);
    int frames = (int)cvGetCaptureProperty(captura,CV_CAP_PROP_FRAME_COUNT);
    if(frames!=0){
        cvCreateTrackbar("posicao","Video",&posicao_slider,frames,onTrackbarSlide);
    }
    IplImage *frame;
    while((frame = cvQueryFrame(captura))!=NULL){
        cvShowImage("Video",frame);
        char c =cvWaitKey(33);
        if(c==27)break;
    }
    cvReleaseCapture(&captura);
    cvDestroyAllWindows();
    return 0;
}

