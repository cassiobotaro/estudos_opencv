#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "cv.h"
#include <iostream>


/*
Programa para detecão de movimento
Programa: main.c
Vídeo default : Lupi.AVI
Autor(es):
Sílvia Grasiella Moreira Almeida(autora original do código)
Cássio Oliveira Botaro(revisão)
*/

int main(int argc,char** argv)
{
    CvMemStorage * storage = cvCreateMemStorage(0);
    CvSeq * contour = 0;
    int mode = CV_RETR_CCOMP;
    int filter = CV_GAUSSIAN_5x5;
    //captura o vídeo
    CvCapture* capture = cvCreateFileCapture("../Lupi.AVI");  //captura o vídeo escolhido
    if (!capture)
    {
        printf("não foi possível carregar o vídeo");
        return 0;
    }                                 //caso vídeo não seja capturado retorne erro
    IplImage* frame = cvQueryFrame(capture);  //captura o primeiro frame do vídeo
    IplImage* frameGray = cvCreateImage(cvGetSize(frame), 8, 1 );//cria estrutura para conversão do frame para cinza cvCreateImage(tamnho,depth,nº canais)
    cvCvtColor(frame,frameGray,CV_RGB2GRAY);//tranforma em preto e branco o frame
    IplImage* frameAntGrayP = cvCreateImage(cvSize(frame->width/2,frame->height/2),8,1);//cria estrtura para reduzir o frame e guardar como frame anterior
    cvPyrDown(frameGray,frameAntGrayP, filter);//reduz o frame preto e branco  em metade do tamnho usando filtro CV_GAUSSIAN_5X5
    double fps = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS); //variavél fps(frames por segundo) que captura o numero de frames por segundo do vídeo
    CvSize tamanho = cvSize(
       (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH),
       (int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT)
                     );//variavel tamanho onde é armazenada o tamanho do vídeo
    CvVideoWriter* videoescrito = cvCreateVideoWriter("movimento.avi",CV_FOURCC('M','J','P','G'),fps,tamanho,1);//cria estrutura para armazenar grvação do vídeo de nome movimento.avi
    while((frame = cvQueryFrame(capture))!= NULL)                                                 //  enquanto a captura de frames continuar verdadeira
    {
        cvCvtColor(frame, frameGray, CV_RGB2GRAY);                                                  //converte o frame em preto e branco
        IplImage* frameGrayP = cvCreateImage(cvSize(frame->width/2,frame->height/2),8,1);           //reduz o frame
        cvPyrDown(frameGray,frameGrayP, filter);
        IplImage* diferenca = cvCreateImage(cvSize(frame->width/2,frame->height/2),8,1);
        cvAbsDiff(frameGrayP,frameAntGrayP,diferenca);                                              //retira a diferença entre o frame atual e anterior
        IplImage*  threshold = cvCreateImage(cvSize(frame->width/2,frame->height/2),8,1);
        cvThreshold(diferenca, threshold, 50,150 , CV_THRESH_BINARY );                              //filtra imagem usando a diferença como parametro
        IplImage*contourImg = cvCreateImage(cvGetSize(diferenca), IPL_DEPTH_8U, 3);
        contourImg = (IplImage*)cvClone(frameGrayP);
        frameAntGrayP = frameGrayP;
        cvReleaseImage( &diferenca );
        cvFindContours(threshold, storage, &contour, sizeof(CvContour), mode, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));//procura contornos em imagem
        cvDrawContours(contourImg, contour, CV_RGB(255, 0, 0), CV_RGB(255, 0, 0), 1, 5, 5,cvPoint(0,0));//desenha contornos em imagem
        /*
        Declaração de variáveis para desenhar elipses na imagem que utiliza a diferença filtrada para fornecer pontos de detecção de movimento
        */
        int step = threshold->widthStep/sizeof(uchar);
        uchar* data = (uchar *)threshold->imageData;

        int i,j;
        CvPoint pt1;
        pt1.x = 100;
        pt1.y = 100;
        CvSize sz;
        sz.width =5;
        sz.height=10;
        double angle = 1.0;
        int line_type = CV_AA;
        //varre a matriz de dados e desenha elipses em pontos de detecção de movimento
        for (i=0; i<threshold->height; i++)
        {
            for (j = 0; j<threshold->width; j++)
            {
                if (data[i*step+j*threshold->nChannels] > 0)//se for detectado movimento
                {
                    pt1.x = j*2;
                    pt1.y = i*2;
                    cvEllipse( frame, pt1, sz, angle, angle - 360, angle + 20, CV_RGB(255,0,0), 1, line_type, 0 );//desenha a elipse no frame principal
                } //end if data
            } // end for j
        }// end for i
        cvWriteFrame(videoescrito,frame);//grava o frame com detecção feita
        cvShowImage( "Detecta - Menor Resolução", contourImg);//exibe frame com imagem preto e branco e com contorno
        cvShowImage( "Detecta - Tamanho Original", frame);//exibe o vídeo marcando os pontos com elipses
        char c = cvWaitKey(33);
        if(c==27)break;//se tecla for esc saia da exibição
    }
    cvReleaseVideoWriter(&videoescrito);//libera memória de vídeo gravado
    return 0;//fim do programa
}
