#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <string>
using namespace std;
typedef IplImage* IPL;

const   double   PI=3.1415926;


double f1_1,f1_2,f1_3,f2_1,f2_2,f2_3,g1_1,g1_2,g1_3,g2_1,g2_2,g2_3,h1_1,h1_2,h1_3,h2_1,h2_2,h2_3,m1_1,m1_2,m1_3,m2_1,m2_2,m2_3;
double sf_1,sf_2,sf_3,sg_1,sg_2,sg_3,sh_1,sh_2,sh_3,sm_1,sm_2,sm_3;
double v1_1,v1_2,v1_3,v2_1,v2_2,v2_3,v_1,v_2,v_3;
double computerfour(double p1,double p2,double p3,double p4,double * w_1,double * w_2,double * w_3,double * dis)
{
    f1_1=1; f1_2=0; f1_3=p3-p1;
	f2_1=0; f2_2=1; f2_3=p2-p1;

	sf_1=f1_2*f2_3-f1_3*f2_2; //x方向矢量
	sf_2=f1_3*f2_1-f1_1*f2_3; //y方向矢量
    sf_3=f1_1*f2_2-f1_2*f2_1; //z方向矢量
    //以上为点1,2,3组成的面的法线矢量，(左上角1，右上角2，左下角3，右下角4)
	g1_1=0;  g1_2=-1;  g1_3=p1-p2;
	g2_1=1;  g2_2=0;   g2_3=p4-p2;

	sg_1=g1_2*g2_3-g1_3*g2_2;
    sg_2=g1_3*g2_1-g1_1*g2_3;
    sg_3=g1_1*g2_2-g1_2*g2_1;
	//点1,2,4,组成的面的法线矢量
	h1_1=-1; h1_2=0;  h1_3=p2-p4;
	h2_1=0;  h2_2=-1; h2_3=p3-p4;

	sh_1=h1_2*h2_3-h1_3*h2_2;
    sh_2=h1_3*h2_1-h1_1*h2_3;
    sh_3=h1_1*h2_2-h1_2*h2_1;
	//点4,2,3,组成的面的法线矢量

    m1_1=0;  m1_2=1; m1_3=p4-p3;
    m2_1=-1; m2_2=0; m2_3=p1-p3;

	sm_1=m1_2*m2_3-m1_3*m2_2;
    sm_2=m1_3*m2_1-m1_1*m2_3;
    sm_3=m1_1*m2_2-m1_2*m2_1;
	//点1,4,3,组成的面的法线矢量

    v1_1=sf_1+sh_1;v1_2=sf_2+sh_2;v1_3=sf_3+sh_3;
    v2_1=sg_1+sm_1;v2_2=sg_2+sm_2;v2_3=sg_3+sm_3;

	v_1=(v1_1+v2_1)/4;v_2=(v1_2+v2_2)/4;v_3=(v1_3+v2_3)/4;
	double dis2=sqrt(v_1*v_1+v_2*v_2+v_3*v_3);
	*dis=dis2;

	double w_12=360*acos(v_1/dis2)/(2*PI);
	double w_22=360*acos(v_2/dis2)/(2*PI);
	double w_32=360*acos(v_3/dis2)/(2*PI);

	*w_1=w_12;
	*w_2=w_22;
	*w_3=w_32;

	return 0;
}
