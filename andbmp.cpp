#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;
typedef IplImage* IPL;
IPL andbmp(IPL src1,IPL src2)
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
    /*for( int x=0; x<height; x++)
    {
        for( int y=0; y<width; y++)
        {
            src1temp=cvGet2D(bimage,x,y).val[0];
            if (src1temp==0)
            {
                cvSet2D(bimage,x,y,cvRealScalar(255));
            }
            else
            {
                cvSet2D(bimage,x,y,cvRealScalar(0));
            }


        }
    }*/
    return bimage;
}
