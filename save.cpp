#include </usr/local/include/opencv/cv.h>
#include </usr/local/include/opencv/highgui.h>
#include "/usr/local/include/opencv/cxcore.h"
#include <iostream>
#include<string>
using namespace std;

IplImage* save(IplImage* pImg, char *sring_src, int flag)
{
    if(flag==0)
    {
                string savingfile(sring_src);//实验后去除
                savingfile.erase(savingfile.find_last_of("."));
                string name="-Bidui.tif";
                savingfile+=name;
                cvSaveImage(savingfile.c_str(),pImg);
    }
    else
    {
                string savingfile(sring_src);//实验后去除
                cvSaveImage(savingfile.c_str(),pImg);
    }
    return NULL;
}

