#include<iostream>
#include "opencv2/highgui/highgui.hpp"

using namespace std;

int main(int argc , char** argv)
{

    CvCapture* captura = cvCreateCameraCapture(0);
    if (!captura){
        cout << "não foi possível carregar a camêra." << endl;
        return 0;
    }
    IplImage *frame;
    cout << "Pressione ESC para sair..." << endl;
    while((frame = cvQueryFrame(captura))!=NULL){
        cvShowImage("Vídeo",frame);
        char c =cvWaitKey(33);
        if(c==27)break;
    }
    cvReleaseCapture(&captura);
    cvDestroyAllWindows();
    return 0;
}
