#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <iostream>
using namespace std;

IplImage* contourimage(IplImage* pImg)
{
    IplImage* pContourImg=NULL;
    CvMemStorage * storage = cvCreateMemStorage(0);
    CvSeq* contour = 0;
    //int mode = CV_RETR_EXTERNAL;
    pContourImg = cvCreateImage(cvGetSize(pImg),
                                IPL_DEPTH_8U,
                                1);
    cvZero(pContourImg);
    cvFindContours( pImg, storage, &contour, sizeof(CvContour),
                    CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

    CvSeq* contours=0;
    double maxarea=0;
    for( ; contour != 0; contour = contour->h_next )
    {
        double tmparea=fabs(cvContourArea(contour,CV_WHOLE_SEQ));
        if(tmparea> 100)
        {
            if(tmparea > maxarea )
            {
                maxarea = tmparea ;
                cout<<maxarea<<endl;
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
                   -2,-1, 8, cvPoint(0,0));

    cvReleaseMemStorage(&storage);
    return pContourImg;
}
