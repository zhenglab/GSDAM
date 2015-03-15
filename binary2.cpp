#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
typedef IplImage* IPL;
IPL binary2(IPL pimg,IPL img)
{
    img=cvCloneImage(pimg);

    //const char * outfile = outfile2.c_str();
	int i, j, k, height, width, num, gray;
	float n[256];
	float p[256];
	height = img->height;
	width = img->width;
//	cout<<height<<" "<<width<<endl;
	num = height * width;
//	cout<<num<<endl;
	CvScalar s;
/*------------------------------------------------------------------*/

	float smax=0, smin=255, dmax=255, dmin=0;
	CvScalar sa, da;

	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			sa = cvGet2D(img, i, j);
			if(smax < sa.val[0])
				smax = sa.val[0];
			if(smin>sa.val[0])
				smin = sa.val[0];
		}
	}
//	cout<<" max:"<<smax<<" min:"<<smin<<endl;
	float a, b;
	a = (dmax-dmin)/(smax-smin);
       	b = (smax*dmin - dmax*smin)/(smax - smin);
//	cout<<" a:"<<a<<" b:"<<b<<endl;
	if(a>1)
	{
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			sa = cvGet2D(img, i, j);//i是行，j是列；
			da.val[0] = a *  sa.val[0] + b;
			cvSet2D(img, i, j, da);
		}
	}
	}
/*------------------------------------------------------------------*/
	for(i=1; i<256; i++)
	{
		n[i] = 0;
		p[i] = 0;
	}

	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			s=cvGet2D(img, i, j);
			gray=s.val[0];
			n[gray]++;
		}
	}
	float u = 0;
	for(i=0; i<256; i++)
	{
		p[i] = n[i] / num;
		u = i * p[i] + u;
	}
//	cout<<" u:"<<u<<endl;
	float w0=0, w1=0, u0=0, u1=0, tmp0=0, tmp1=0;
	float o2[256];

	for(k=1; k<256; k++)
	{
		w0=0;
		tmp0=0;
		for(i=1;i<=k;i++)
		{
			w0 += p[i];
			tmp0 = i * p[i] + tmp0;

		}
		if(w0 != 0)
			u0 = tmp0 / w0;
		else
			u0 = 0;

//		cout<<"k:"<<k<<" tmp0:"<<tmp0;
//		cout<<" w0:"<<w0<<" u0:"<<u0;

		w1=0;
		tmp1=0;
		for(i=k+1; i<256; i++)
		{
			w1+=p[i];
			tmp1 = i * p[i] +tmp1;
		}
		if (w1 != 0)
			u1 = tmp1 / w1;
		else
			u1 = 0;
//		cout<<" tmp1:"<<tmp1<<" w1:"<<w1<<" u1:"<<u1;
		o2[k] =w0 * w1 * (u1 - u0) * (u1 -u0);//此处与论文公式不符；
//		cout<<" o2["<<k<<"]:"<<o2[k]<<endl;


	}
	float max=0, threshold=0;
	for(i=1; i<256; i++)
	{
		if(o2[i]>max)
		{
			max = o2[i];
			threshold = i;
		}
		else
			continue;
	}

//	cout<<" threshold:"<<threshold<<endl;
/*------------------------------------------------------------*/
       CvScalar black = cvScalar(0, 0, 0);
       CvScalar white = cvScalar(255, 255, 255);
       	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			s=cvGet2D(img, i, j);
			if(s.val[0] > threshold)
				cvSet2D(img, i, j, white);
			else
				cvSet2D(img, i, j, black);
		}
	}

//二值化后，好像是灰度值大于阈值的为黑色，小于阈值的为白色，为什么？
   //cvSaveImage(outfile,img);
return img;
}
