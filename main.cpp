#include <iostream>
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
using namespace std;
typedef IplImage* IPL;

extern double computerfour(double,double,double,double,double *,double *,double *,double *);
extern IPL binary2(IplImage*,IPL);//��ֵ��������ĺ��������������кü���������Ҫ�����õ���һ����
extern IPL andbmp(IPL,IPL);
extern IPL contourimage(IPL);
extern IPL bidui(IPL,IPL);

int main(int argc, char* argv[])
{
    IPL src3=cvLoadImage(argv[1],0);//��ͼ���ļ��������ڴ棬�Զ�����ͼ�����ݽṹ������ڴ棬�ú���ִ����󽫷���һ��ָ��
    //IPL dst=0;
    IPL src = cvCreateImage( cvSize( src3 -> width+3, src3 -> height+3 ), IPL_DEPTH_8U, src3->nChannels);
    IPL src2=cvLoadImage(argv[1],1);
    IPL imagex=cvCloneImage(src);
    IPL imagey=cvCloneImage(src);
    IPL imagez=cvCloneImage(src);
    IPL imagexz=cvCloneImage(src);
    IPL imageyz=cvCloneImage(src);
    //IPL imgBF=cvCloneImage(src);
    IPL imagexzBF=cvCloneImage(src);
    IPL imageyzBF=cvCloneImage(src);

    //IPL imagebinaryY=cvCloneImage(src);
    //IPL imageXandY=cvCloneImage(src);
    //IPL src2=cvCloneImage(src);//x2��x��ֵ����
   /* CvSize dst_cvsize;
    dst_cvsize.width = 300;
    dst_cvsize.height =300;
    dst = cvCreateImage( dst_cvsize, src2->depth, src2->nChannels);
    cvResize(src2, dst, CV_INTER_LINEAR);
    string savingfile21(argv[1]);
    savingfile21.erase(savingfile21.find_last_of("."));
    savingfile21 += "-����ͼ.tif";
    cvSaveImage(savingfile21.c_str(),dst);*/
    //cvSaveImage("����.bmp",dst);



    /*int t1,t2,t3,t4,t5;

        printf("��ֵ�˲�1�Ĳ�����: \n");
        cin>>t1;
        //t1=atoi(argv[2]);

        printf("��ֵ�˲�2�Ĳ�����: \n");
        cin>>t2;
        //t2=atoi(argv[3]);

        printf("������Ĵ�����: \n");
        cin>>t3;
        //t3=atoi(argv[4]);

        printf("���͸�ʴ�Ĵ����ǣ�\n");
        cin>>t4;
        //t4=atoi(argv[5]);

        printf("������Ĵ����ǣ�\n");
        cin>>t5;
        //t5=atoi(argv[6]);*/

    int height=src->height, width=src->width;//�˴�ע�����ź�ȥ��
    double **c1;
    double **c2;
    double **c3;
    double **c4;
    double **xmap;
    double **ymap;
    double **zmap;
    double **xzmap;
    double **yzmap;
    //double **lengthmap;

    c1 = new double*[width];//x����ǵĽǶ�
    c2 = new double*[width];
    c3 = new double*[width];
    c4 = new double*[width];
    xmap=new double*[width];
    ymap=new double*[width];
    zmap=new double*[width];
    xzmap=new double*[width];
    yzmap=new double*[width];
    //lengthmap=new double*[width];//lengthmap��������ģ��Ӧ�ĻҶ�ͼ��

    /*string savingfile(argv[1]);//ʵ���ȥ��
    savingfile.erase(savingfile.find_last_of("."));
    savingfile += "-�Ҷ�ͼ.tif";
    cvSaveImage(savingfile.c_str(),src3);*///ʵ���ȥ��

    //cvSaveImage("Img�Ҷ�ͼ.tif",src);
    //cvSmooth(src , imgBF , CV_BILATERAL,-1,50,0,11);
    //cvSaveImage("ImgBF.bmp",imgBF);
   cvCopyMakeBorder( src3, src, cvPoint( 1, 1 ), IPL_BORDER_CONSTANT );

    for(int i=0; i<width; i++)
		{
		  c1[i] = new double[height];
		  c2[i] = new double[height];
		  c3[i] = new double[height];
		  c4[i] = new double[height];
		  xmap[i]=new double[height];
		  ymap[i]=new double[height];
          zmap[i]=new double[height];
          xzmap[i]=new double[height];
          yzmap[i]=new double[height];
          //lengthmap[i]=new double[height];

        }


    int x,y;
    CvScalar Ix0y0,Ix0y1,Ix1y1,Ix1y0;
    double w1,w2,w3,* w1_z,* w2_z,* w3_z,dis,* dis_z;//�ɲ�����ֻ����ָ�����͵ģ�


    for(y=0; y<height-1; y++)
    {
        for(x=0; x<width-1; x++)
        {
            Ix0y0=cvGet2D(src,y,x);
            Ix0y1=cvGet2D(src,(y+1),x);
            Ix1y1=cvGet2D(src,(y+1),(x+1));
            Ix1y0=cvGet2D(src,y,(x+1));
            w1_z=&w1;
            w2_z=&w2;
            w3_z=&w3;
            dis_z=&dis;
            computerfour(Ix0y0.val[0],Ix0y1.val[0],Ix1y0.val[0],Ix1y1.val[0],w1_z,w2_z,w3_z,dis_z);
            //�˺��������Ƿֱ����xyz����������нǴ�С
            c1[x][y]=w1;//w1�Ƿ���������x��ļнǣ�
            c2[x][y]=w2;
            c3[x][y]=w3;
            //c4[x][y]=dis;//dis�Ƿ�������ģ
        }
    }
double xmax,xmin,ymax,ymin,zmax,zmin;
    double c1yx,c2yx,c3yx;
    xmax=c1[0][0];
    xmin=c1[0][0];
    ymax=c2[0][0];
    ymin=c2[0][0];
    zmax=c3[0][0];
    zmin=c3[0][0];
    //dismax=c4[0][0];
    //dismin=c4[0][0];

    for(y=0; y<height-1; y++)

    {
        for(x=0; x<width-1; x++)

        {
            c1yx=c1[x][y];
            if (c1yx>xmax)
                xmax=c1yx;
            else {};

            if (c1yx<xmin)
                xmin=c1yx;
            else {};
            c2yx=c2[x][y];
            if (c2yx>ymax)
                ymax=c2yx;
            else {};
            if (c2yx<ymin)
                ymin=c2yx;
            else {};
                        c3yx=c3[x][y];
            if (c3yx>zmax)
                zmax=c3yx;
            else {};
            if (c3yx<zmin)
                zmin=c3yx;
            else {};




        }
    }
    for(y=0; y<height-1; y++)
    {
        for(x=0; x<width-1; x++)
        {
            xmap[x][y]=255*(c1[x][y]-xmin)/(xmax-xmin);
            ymap[x][y]=255*(c2[x][y]-ymin)/(ymax-ymin);
            zmap[x][y]=255*(c3[x][y]-zmin)/(zmax-zmin);
            cvSet2D(imagex,y,x,cvRealScalar(xmap[x][y]));
            cvSet2D(imagey,y,x,cvRealScalar(ymap[x][y]));
            cvSet2D(imagez,y,x,cvRealScalar(zmap[x][y]));

        }
    }

    /*string savingfile2(argv[1]);//ʵ���ȥ��
    savingfile2.erase(savingfile2.find_last_of("."));
    savingfile2 += "--x.tif";
    cvSaveImage(savingfile2.c_str(),imagex);

    string savingfile3(argv[1]);
    savingfile3.erase(savingfile3.find_last_of("."));
    savingfile3 += "-y.tif";
    cvSaveImage(savingfile3.c_str(), imagey);

    string savingfile4(argv[1]);
    savingfile4.erase(savingfile4.find_last_of("."));
    savingfile4 += "-z.tif";
    cvSaveImage(savingfile4.c_str(), imagez);*///ʵ���ȥ��

     //cvSaveImage("ImgX.tif",imagex);
     //cvSaveImage("ImgY.tif",imagey);
     //cvSaveImage("ImgZ.tif",imagez);



     for(y=0; y<height-1; y++)
    {
        for(x=0; x<width-1; x++)
        {
            xzmap[x][y]=sqrt(xmap[x][y]*xmap[x][y]+zmap[x][y]*zmap[x][y]);
            yzmap[x][y]=sqrt(ymap[x][y]*ymap[x][y]+zmap[x][y]*zmap[x][y]);
            cvSet2D(imagexz,y,x,cvRealScalar(xzmap[x][y]));
            cvSet2D(imageyz,y,x,cvRealScalar(yzmap[x][y]));
         }
    }
    /*string savingfile20(argv[1]);//ʵ���ȥ��
    savingfile20.erase(savingfile20.find_last_of("."));
    savingfile20 += "-XZ1.tif";
    cvSaveImage(savingfile20.c_str(), imagexz);
    string savingfile5(argv[1]);
    savingfile5.erase(savingfile5.find_last_of("."));
    savingfile5 += "-YZ1.tif";
    cvSaveImage(savingfile5.c_str(), imageyz);*///ʵ���ȥ��
     //cvSaveImage("ImgXZ1.tif",imagexz);
     //cvSaveImage("ImgYZ1.tif",imageyz);
    double xzmap_max=xzmap[0][0];
    double xzmap_min=xzmap[0][0];
    double yzmap_max=yzmap[0][0];
    double yzmap_min=yzmap[0][0];
    for(y=0; y<height-1; y++)
    {
        for(x=0; x<width-1; x++)
        {
            if (xzmap[x][y]>xzmap_max)
            {
                xzmap_max=xzmap[x][y];
            }
            else {}
            if (xzmap[x][y]<xzmap_min)
            {
                xzmap_min=xzmap[x][y];
            }
            else {}
            if (yzmap[x][y]>yzmap_max)
            {
                yzmap_max=yzmap[x][y];
            }
            else {}
            if (yzmap[x][y]<yzmap_min)
            {
                yzmap_min=yzmap[x][y];
            }
            else {}
        }
    }
    for(y=0; y<height-1; y++)
    {
        for(x=0; x<width-1; x++)
        {
            xzmap[x][y]=255*( (xzmap[x][y]-xzmap_min)/(xzmap_max-xzmap_min));
            yzmap[x][y]=255*( (yzmap[x][y]-yzmap_min)/(yzmap_max-yzmap_min));
            cvSet2D(imagexz,y,x,cvRealScalar(xzmap[x][y]));
            cvSet2D(imageyz,y,x,cvRealScalar(yzmap[x][y]));
            }
    }
    /*string savingfile6(argv[1]);//ʵ���ȥ��
    savingfile6.erase(savingfile6.find_last_of("."));
    savingfile6 += "-XZ2.tif";
    cvSaveImage(savingfile6.c_str(), imagexz);*///ʵ���ȥ��
     //cvSaveImage("Imgxz.tif",imagexz);
     cvSmooth(imagexz,imagexzBF,CV_BILATERAL,-1,1,40,20);
     /*string savingfile7(argv[1]);//ʵ���ȥ��
    savingfile7.erase(savingfile7.find_last_of("."));
    savingfile7 += "-xzBF.tif";
    cvSaveImage(savingfile7.c_str(), imagexzBF);*///ʵ���ȥ��
     //cvSaveImage("imagexzBF.tif",imagexzBF);
     /*string savingfile8(argv[1]);//ʵ���ȥ��
    savingfile8.erase(savingfile8.find_last_of("."));
    savingfile8 += "-YZ2.tif";
    cvSaveImage(savingfile8.c_str(), imageyz);*///ʵ���ȥ��
     //cvSaveImage("Imgyz.bmp",imageyz);
     cvSmooth(imageyz,imageyzBF,CV_BILATERAL,-1,1,40,20);
     /*string savingfile9(argv[1]);//ʵ���ȥ��
    savingfile9.erase(savingfile9.find_last_of("."));
    savingfile9 += "-yzBF.tif";
    cvSaveImage(savingfile9.c_str(), imageyzBF);*///ʵ���ȥ��
     //cvSaveImage("imageyzBF.tif",imageyzBF);
     for(int i=0; i<width; i++)
    {
        delete []c1[i];
        delete []c2[i];
        delete []c3[i];
        delete []c4[i];
        delete []xmap[i];
        delete []ymap[i];
        delete []zmap[i];
        delete []xzmap[i];
        delete []yzmap[i];
       // delete []lengthmap[i];
    }
    delete []c1;
    delete []c2;
    delete []c3;
    delete []c4;
    delete []xmap;
    delete []ymap;
    delete []zmap;
    delete []xzmap;
    delete []yzmap;
    //delete []lengthmap;

    /*IPL imgx_binary=cvCreateImage(cvGetSize(imagex),IPL_DEPTH_8U,1);
    //������һ����imagexͼ���Сһ�µĵ�ͨ��ͼ�������8��2��8�η�����ʾһ�����أ�����256ɫ��
    cvZero(imgx_binary);//cvZero�Ƕ�ͼ�����㣻
    imgx_binary=binary2(imagex,imgx_binary);//��ͼ��imagex�øĽ��Ĵ�򷨽��ж�ֵ�������ص���imgx_binary��
    cvSaveImage("imgx_binary.tif",imgx_binary);

    IPL imgy_binary=cvCreateImage(cvGetSize(imagey),IPL_DEPTH_8U,1);
    imgy_binary=binary2(imagey,imgy_binary);
    cvSaveImage("imgy_binary.tif",imgy_binary);

    IPL imgz_binary=cvCreateImage(cvGetSize(imagez),IPL_DEPTH_8U,1);
    imgz_binary=binary2(imagez,imgz_binary);
    cvSaveImage("imgz_binary.tif",imgz_binary);

    IPL imgandXb_Yb=andbmp(imgx_binary,imgy_binary);
    cvSaveImage("imgandxb_yb.tif",imgandXb_Yb);*/

    /*IPL imagexz_binary=cvCreateImage(cvGetSize(imagexz),IPL_DEPTH_8U,1);
    cvZero(imagexz_binary);
    imagexz_binary=binary2(imagexz,imagexz_binary);//��򷨶�ֵ����xz����ͶӰͼ��
    string savingfile(argv[1]);
    savingfile.erase(savingfile.find_last_of("."));
    savingfile += "-xzBinary.tif";
    cvSaveImage(savingfile.c_str(), imagexz_binary);
    //cvSaveImage("imgxz_binary.tif",imagexz_binary);

    IPL imageyz_binary=cvCreateImage(cvGetSize(imageyz),IPL_DEPTH_8U,1);
    imageyz_binary=binary2(imageyz,imageyz_binary);
    string savingfile(argv[1]);
    savingfile.erase(savingfile.find_last_of("."));
    savingfile += "-yzBinary.tif";
    cvSaveImage(savingfile.c_str(), imageyz_binary);
    //cvSaveImage("imgyz_binary.tif",imageyz_binary);

    IPL imgandxzb_yzb=andbmp(imagexz_binary,imageyz_binary);
    string savingfile(argv[1]);
    savingfile.erase(savingfile.find_last_of("."));
    savingfile += "-xzbANDyzb.tif";
    cvSaveImage(savingfile.c_str(), imageandxzb_yzb);
    //cvSaveImage("imgandxzb_yzb.tif",imgandxzb_yzb);*/

    IPL imagexzBF_binary=cvCreateImage(cvGetSize(imagexz),IPL_DEPTH_8U,1);
    cvZero(imagexzBF_binary);
    imagexzBF_binary=binary2(imagexzBF,imagexzBF_binary);//��򷨶�ֵ����xz����ͶӰͼ��
    /*string savingfile10(argv[1]);//ʵ���ȥ��
    savingfile10.erase(savingfile10.find_last_of("."));
    savingfile10 += "-xzBFBinary.tif";
    cvSaveImage(savingfile10.c_str(), imagexzBF_binary);*///ʵ���ȥ��
    //cvSaveImage("imgxzBF_binary.tif",imagexzBF_binary);

    IPL imageyzBF_binary=cvCreateImage(cvGetSize(imageyz),IPL_DEPTH_8U,1);
    imageyzBF_binary=binary2(imageyzBF,imageyzBF_binary);
    /*string savingfile11(argv[1]);//ʵ���ȥ��
    savingfile11.erase(savingfile11.find_last_of("."));
    savingfile11 += "-yzBFBinary.tif";
    cvSaveImage(savingfile11.c_str(), imageyzBF_binary);*///ʵ���ȥ��
    //cvSaveImage("imgyzBF_binary.tif",imageyzBF_binary);

    IPL imgandxzb_yzbBF=andbmp(imagexzBF_binary,imageyzBF_binary);
    /*string savingfile12(argv[1]);//ʵ���ȥ��
    savingfile12.erase(savingfile12.find_last_of("."));
    savingfile12 += "-xzbANDyzb.tif";
    cvSaveImage(savingfile12.c_str(), imgandxzb_yzbBF);*///ʵ���ȥ��
    //cvSaveImage("imgandxzb_yzbBF.tif",imgandxzb_yzbBF);


    IPL dilate_src=cvCloneImage(imgandxzb_yzbBF);
    IPL imagedilate=cvCloneImage(dilate_src);
    IPL imagekai=cvCloneImage(dilate_src);
    IPL imagebi=cvCloneImage(dilate_src);
    //IPL imageErode=cvCloneImage(dilate_src);
    //IPL imagesmoothG=cvCloneImage(dilate_src);
    IPL imagesmoothM=cvCloneImage(dilate_src);
    IPL imagesmoothM2=cvCloneImage(dilate_src);
    //IPL imagesmoothB=cvCloneImage(dilate_src);
    IplConvKernel *element=0;
    IplConvKernel *element2=0;
    IPL image_temp=cvCloneImage(dilate_src);
    cvSetZero(image_temp);

    //cvSmooth(imagedilate,imagesmoothB,CV_BILATERAL,-1,20,20,20);
    //cvSaveImage("imageSmoothB.bmp",imagesmoothB);
    cvSmooth(imagedilate,imagesmoothM,CV_MEDIAN,5,5);
    cvSmooth(imagesmoothM,imagesmoothM2,CV_MEDIAN,3,3);
    /*string savingfile13(argv[1]);//ʵ���ȥ��
    savingfile13.erase(savingfile13.find_last_of("."));
    savingfile13 += "-SmoothM.tif";
    cvSaveImage(savingfile13.c_str(), imagesmoothM2);*///ʵ���ȥ��
    //cvSaveImage("imageSmoothM.tif",imagesmoothM2);
    //cvSmooth(imagedilate,imagesmoothG,CV_GAUSSIAN,3,3,0,0); //��˹�˲�
    //cvSaveImage("imageSmoothG.bmp",imagesmoothG);

    element=cvCreateStructuringElementEx(3,3,1,1,CV_SHAPE_ELLIPSE);
    element2=cvCreateStructuringElementEx(2,2,0,0,CV_SHAPE_ELLIPSE);
    //cvErode(imagekai,imageErode,element,2);//���������ݶ�Ϊ��
	//cvSaveImage("imageErode.bmp",imageErode);
    //cvMorphologyEx(imagesmoothM2,imagekai,image_temp,element,CV_MOP_OPEN,3);
    //cvSaveImage("imagekai.bmp",imagekai);
    cvMorphologyEx(imagesmoothM2,imagebi,image_temp,element,CV_MOP_CLOSE,5);
    /*string savingfile14(argv[1]);//ʵ���ȥ��
    savingfile14.erase(savingfile14.find_last_of("."));
    savingfile14 += "-BI.tif";
    cvSaveImage(savingfile14.c_str(), imagebi);*///ʵ���ȥ��
    //cvSaveImage("imagebi.tif",imagebi);
   /* cvFloodFill(src3,cvPoint(0,0),cvScalar(255),cvScalarAll(0),cvScalarAll(0),NULL,4,NULL);
    string savingfile22(argv[1]);//ʵ���ȥ
    savingfile22.erase(savingfile22.find_last_of("."));
    savingfile22 += "-FF.tif";
    cvSaveImage(savingfile22.c_str(), src3);*///ʵ���ȥ��
    //element2=cvCreateStructuringElementEx(2,2,0,0,CV_SHAPE_RECT);
	cvDilate(imagebi,imagedilate,element2,5);//����
	/*string savingfile15(argv[1]);//ʵ���ȥ��
    savingfile15.erase(savingfile15.find_last_of("."));
    savingfile15 += "-dilate.tif";
    cvSaveImage(savingfile15.c_str(), imagedilate);*///ʵ���ȥ��
	//cvSaveImage("imagedilate.tif",imagedilate);
    IPL contour_src=contourimage(imagedilate);//��ȡ����������

    /*string savingfile16(argv[1]);
    savingfile16.erase(savingfile16.find_last_of("."));
    savingfile16 += "-Contour.tif";
    cvSaveImage(savingfile16.c_str(), contour_src);*/

   cvErode(contour_src,contour_src,element2,5);//����
    /*string savingfile17(argv[1]);
    savingfile17.erase(savingfile17.find_last_of("."));
    savingfile17 += "-Erode.tif";
    cvSaveImage(savingfile17.c_str(), contour_src);*/

    cvMorphologyEx(contour_src,imagekai,image_temp,element,CV_MOP_OPEN,3);//����
    /*string savingfile18(argv[1]);//ʵ���ȥ��
    savingfile18.erase(savingfile18.find_last_of("."));
    savingfile18 += "-Kai.tif";
    cvSaveImage(savingfile18.c_str(), imagekai);*///ʵ���ȥ��


    IPL imgBidui=bidui(src2,imagekai);
    string savingfile19(argv[1]);
    savingfile19.erase(savingfile19.find_last_of("."));
    savingfile19 += "-Bidui.tif";
    cvSaveImage(savingfile19.c_str(), imgBidui);




     cvReleaseImage(&imagex);
     cvReleaseImage(&imagey);
     cvReleaseImage(&imagez);
     //cvReleaseImage(&imgx_binary);
     //cvReleaseImage(&imgy_binary);
     //cvReleaseImage(&imgz_binary);
     //cvReleaseImage(&imgandXb_Yb);
     //cvReleaseImage(&imagexz_binary);
     //cvReleaseImage(&imageyz_binary);
     //cvReleaseImage(&imgandxzb_yzb);
     cvReleaseImage(&imagedilate);
     cvReleaseImage(&imagexzBF_binary);
     cvReleaseImage(&imageyzBF_binary);
     cvReleaseImage(&imgandxzb_yzbBF);
     cvReleaseImage(&imagesmoothM2);
     cvReleaseImage(&imagebi);
     cvReleaseImage(&contour_src);
     cvReleaseImage(&imagekai);
     cvReleaseImage(&imgBidui);


     //cvReleaseImage(&dst);





     return 0;
   }

