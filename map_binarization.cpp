//大津法阈值方法二值化Map//

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
typedef IplImage* IPL;

IPL map_binarization(IPL pimg,IPL img)
{
    img=cvCloneImage(pimg);
    
    int i, j, k, height, width, num, gray;
    float n[256];
    float p[256];
    height = img->height;
    width = img->width;
    num = height * width;
    CvScalar s;
    
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
            s=cvGet2D(img, i, j);//统计每个灰度级在整幅图像中的个数
            gray=s.val[0];
            n[gray]++;
        }
    }
    float u = 0;
    for(i=0; i<256; i++)
    {
        p[i] = n[i] / num;//计算每个灰度在整幅图像中的比例
        u = i * p[i] + u;
    }
    float w0=0, w1=0, u0=0, u1=0, tmp0=0, tmp1=0;//设定可以将一个图像灰度级分为两类的阈值,一个为前景，一个为背景
    float o2[256];
    
    for(k=1; k<256; k++)
    {
        w0=0;
        tmp0=0;
        for(i=1;i<=k;i++)
        {
            w0 += p[i];//w0=\sum{i=0到k} pi
            tmp0 = i * p[i] + tmp0;
            
        }
        if(w0 != 0)
            u0 = tmp0 / w0;//u0=(\sum i*pi)/w0 前景的平均灰度
        else
            u0 = 0;
        
        w1=0;
        tmp1=0;
        for(i=k+1; i<256; i++)
        {
            w1+=p[i];//w1=\sum{i=k+1到l-1} pi
            tmp1 = i * p[i] +tmp1;
        }
        if (w1 != 0)
            u1 = tmp1 / w1;//u1=(\sum{i=k+1到l-1} i*pi)/w1 背景的平均灰度
        else
            u1 = 0;
        o2[k] =w0 * w1 * (u1 - u0) * (u1 -u0);//类间方差为sigb^2=w0w1/(u1-u0)^2,论文中判别规则为sigb^2/sigt^2，前景和背景图象的方差：g=w0*(u0-u)*(u0-u)+w1*(u1-u)*(u1-u)=w0*w1*(u0-u1)*(u0-u1),此公式为方差公式。
        
    }
    float max=0, threshold=0;
    for(i=1; i<256; i++)
    {
        if(o2[i]>max)
        {
            max = o2[i];
            threshold = i;//找到使判别准则值最大的灰度值k
        }
        else
            continue;
    }
    
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
    
    //二值化后，灰度值大于阈值的为白色，小于阈值的为黑色
    return img;
}
