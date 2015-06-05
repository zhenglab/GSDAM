/*
 * This function is equivalent to the Matlab function imfill(im,'holse').
 * A hole is a set of background pixels not connected to the edge of the image
 *
 * Input :
 *     imInput : input binary image
 * Output:
 *     imOutput: the binary image whose holes are filled
 *
 * Created by visionfans @ 2011.06.30
 *
 */
#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;


 cvMat* imFillHoles(Mat imInput)
{
    Mat imShow = Mat::zeros(imInput.size(),CV_8UC3); // for show result

    //
    // detect external contours
    //
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(imInput, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    //
    // fill external contours
    //
    if( !contours.empty() && !hierarchy.empty() )
    {
        for (int idx=0;idx < contours.size();idx++)
        {
            drawContours(imShow,contours,idx,Scalar::all(255),CV_FILLED,8);
        }
    }

    Mat imFilledHoles;
    cvtColor(imShow,imFilledHoles,CV_BGR2GRAY);
    imFilledHoles = imFilledHoles > 0;

    // release temp Mat
    imShow.release();

    return imFilledHoles;
}
