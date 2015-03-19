#include <iostream>
#include </usr/local/include/opencv/cv.h>
#include </usr/local/include/opencv/highgui.h>
using namespace std;
typedef IplImage* IPL;
IPL bidui(IPL src1,IPL src2)
{
  //const char * inputfile1 = inputfile12.c_str();
  //const char * inputfile2 = inputfile22.c_str();
  //const char * outfile = outfile2.c_str();
  //IplImage * img=0;
  //IplImage * img2=0;
    int height,width,step,channels;
  int step2,channels2;//height2,width2,s
   int step3,channels3;//height3,width3,
  int i,j,k;
  CvScalar s1,s2;
      s1.val[0] = 0.000000;
	s2.val[0] = 255.000000;
  uchar *data;
  uchar *data2;
  uchar *data3;
  //cvNamedWindow("src",0);
  //cvNamedWindow("conter",0);
  //cvNamedWindow("dst",0);
 IPL img=cvCloneImage(src1);
 IPL img2=cvCloneImage(src2);
 //IPL img3=cvCloneImage(src1);
 //cvSetZero(img3);

 IplImage * dstImg=cvCreateImage(cvGetSize(img),8,3);
 cvSetZero(dstImg);

  height=img->height;
  width=img->width;
  step=img->widthStep;
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
		  {       if(data2[i*step2+j*channels2+k]!=0)
			  {
			  data3[i*step3+j*channels3+k]=data[i*step+j*channels+k];
			  }
		  }
		  }
     	  }
	  //cvShowImage("src",img);

 //cvShowImage("conter",img2);
//cvShowImage("dst",dstImg);
//cvSaveImage(outfile,dstImg);
 //cvWaitKey(0);
  //cvDestroyWindow("src");
  //cvDestroyWindow("conter");
  //cvDestroyWindow("dst");
  cvReleaseImage(&img);
 cvReleaseImage(&img2);
 return dstImg;
}
