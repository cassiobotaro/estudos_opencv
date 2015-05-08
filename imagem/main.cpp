#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
    IplImage *imagem = cvLoadImage("lena.jpg",CV_LOAD_IMAGE_ANYCOLOR);
    if(!imagem)
    {
        printf("Não foi possivel carregar sua imagem com sucesso.");
        return 0;
    }
    cvShowImage("imagem",imagem);
    cvWaitKey(0);
    return 0;
}
