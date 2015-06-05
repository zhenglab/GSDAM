//对进行完形态学开操作的二值图像和原始彩色图像进行与运算得到最终的结果//

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
typedef IplImage* IPL;

IPL and_template_original_imgs(IPL src1,IPL src2)
{
    int height,width,step,channels;
    int step2,channels2;
    int step3,channels3;
    int i,j,k;
    
    uchar *data;
    uchar *data2;
    uchar *data3;
    
    IPL img=cvCloneImage(src1);
    IPL img2=cvCloneImage(src2);
    
    IplImage * dstImg=cvCreateImage(cvGetSize(img),8,3);
    cvSetZero(dstImg);
    
    height=img->height;
    width=img->width;
    step=img->widthStep;//widthStep是指的图片中的每一行占用多少个字节
    channels=img->nChannels;
    data=(uchar *)img->imageData;
    
    step2=img2->widthStep;
    data2=(uchar *)img2->imageData;
    channels2=img2->nChannels;
    
    data3=(uchar *)dstImg->imageData;
    step3=dstImg->widthStep;
    channels3=dstImg->nChannels;
    
    for(i=0;i<height;i++){
        for(j=0;j<width;j++)
        {
            for(k=0;k<channels;k++)
            {
                if(data2[i*step2+j*channels2+k]!=0)
                {
                    data3[i*step3+j*channels3+k]=data[i*step+j*channels+k];//依次读取B、G、R 3个通道中的数据,将原图像src1的目标藻类部分数据赋给最终的目标图像dstimg，背景则默认黑色。
                }
            }
        }
    }
    
    cvReleaseImage(&img);
    cvReleaseImage(&img2);
    return dstImg;
}
