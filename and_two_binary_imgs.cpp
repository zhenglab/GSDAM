//对两幅二值化Map图像进行与运算//

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace std;
typedef IplImage* IPL;

IPL and_two_binary_imgs(IPL src1,IPL src2)
{
    IPL bimage=cvCloneImage(src1);
    cvZero(bimage);
    int height=src1->height,width=src1->width;
    double src1temp,src2temp;
    
    for(int x=0; x<height; x++)
    {
        for(int y=0; y<width; y++)
        {
            src1temp=cvGet2D(src1,x,y).val[0];
            src2temp=cvGet2D(src2,x,y).val[0];
            if (src1temp==src2temp)
            {
                cvSet2D(bimage,x,y,cvRealScalar(src2temp));
            }
            else
            {
                cvSet2D(bimage,x,y,cvRealScalar(0));
            }
        }
    }
    return bimage;
}
