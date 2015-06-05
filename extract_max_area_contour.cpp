//求取图像的多个轮廓并选择最大区域的轮廓输出//

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv/cxcore.h"
#include <iostream>
using namespace std;

IplImage* extract_max_area_contour(IplImage* pImg)
{
    IplImage* pContourImg=NULL;
    CvMemStorage * storage = cvCreateMemStorage(0);//为0时内存块默认大小为64k
    CvSeq* contour = 0;
    pContourImg = cvCreateImage(cvGetSize(pImg),IPL_DEPTH_8U,1);
    cvZero(pContourImg);
    cvFindContours( pImg, storage, &contour, sizeof(CvContour),
                   CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));//pimg需要为单通道灰度图像，CV_RETR_LIST返回所有轮廓，CV_CHAIN_APPROX_SIMPLE为Contour approximation method
    CvSeq* contours=0;
    double maxarea=0;
    for( ; contour != 0; contour = contour->h_next )//选择最大轮廓输出
    {
        double tmparea=fabs(cvContourArea(contour,CV_WHOLE_SEQ));//计算轮廓区域
        if(tmparea> 100)
        {
            if(tmparea > maxarea )
            {
                maxarea = tmparea ;
                contours=contour;
            }
            else
                continue;
        }
        else
            continue;
    }
    cvDrawContours(pContourImg, contours,
                   cvScalarAll(255), cvScalarAll(255),
                   -2,-1, 8, cvPoint(0,0));//绘制轮廓
    
    cvReleaseMemStorage(&storage);
    return pContourImg;
}
