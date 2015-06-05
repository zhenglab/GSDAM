#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv/cxcore.h"
#include <iostream>
#include<string>

using namespace std;

IplImage* save(IplImage* pImg, char *sring_src, int flag)
{
    if(flag==0)
    {
        string savingfile(sring_src);
        savingfile.erase(savingfile.find_last_of("."));//擦除.后的文字
        string name="-final.tif";
        savingfile+=name;
        cvSaveImage(savingfile.c_str(),pImg);//路径
    }
    else
    {
        string savingfile(sring_src);
        cvSaveImage(savingfile.c_str(),pImg);
        cout << sring_src <<":   "   << "Done" <<endl;
    }
    return NULL;
}

