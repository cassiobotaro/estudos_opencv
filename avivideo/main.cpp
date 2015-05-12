#include <stdio.h>
#include <stdlib.h>
#include "opencv2/highgui/highgui.hpp"

using namespace std;

int main(int argc , char** argv)
{
    CvCapture* captura = cvCreateFileCapture("../Lupi.AVI");
    if (!captura){
        printf("não foi possível carregar o vídeo.");
        return 0;
    }
    IplImage *frame;
    while((frame = cvQueryFrame(captura))!=NULL){
        cvShowImage("Vídeo",frame);
        char c =cvWaitKey(33);
        if(c==27)break;
    }
    cvReleaseCapture(&captura);
    cvDestroyAllWindows();
    return 0;
}
