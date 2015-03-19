#include <iostream>
#include </usr/local/include/opencv/cv.h>
#include </usr/local/include/opencv/highgui.h>
#include <stdio.h>
#include <string.h>
#include<string>

using namespace std;
typedef IplImage* IPL;

extern double computerfour(double,double,double,double,double *,double *,double *,double *);
extern IPL binary2(IplImage*,IPL);//二值化和相与的函数吕梁程序中有好几个，后面要留意用的哪一个；
extern IPL andbmp(IPL,IPL);
extern IPL contourimage(IPL);
extern IPL bidui(IPL,IPL);
extern IPL save(IPL,  char *,int);
extern int check(char*);


//image_g   image_x    image_y     image_z      image_xz        image_yz        image_o
//image_x_binary    image_y_binary      image_z_binary      image_xz_binary     image_yz_binary      image_xz_yz_binary
//imagexz     imageyz       imagexzBF       imageyzBF       imgandxzb_yzbBF
//imageSmooth     imageSmooth2          imagedialate    imagebi       imagerode       imagekai        contour_src
//imageBidui


int main(int argc, char* argv[])
{
    IPL src3=cvLoadImage(argv[1],0);//将图像文件加载至内存，自动分配图像数据结构所需的内存，该函数执行完后将返回一个指针
    IPL src = cvCreateImage( cvSize( src3 -> width+3, src3 -> height+3 ), IPL_DEPTH_8U, src3->nChannels);
    IPL src2=cvLoadImage(argv[1],1);
     IPL image_x=cvCloneImage(src);
     IPL image_y=cvCloneImage(src);
     IPL  image_z=cvCloneImage(src);
     IPL  image_xz=cvCloneImage(src);
     IPL   image_yz=cvCloneImage(src);
     IPL  image_xzBF=cvCloneImage(src);
      IPL  image_yzBF=cvCloneImage(src);

    //IPL imagebinaryY=cvCloneImage(src);
    //IPL imageXandY=cvCloneImage(src);
    //IPL src2=cvCloneImage(src);//x2是x二值化后；
   /* CvSize dst_cvsize;
    dst_cvsize.width = 300;
    dst_cvsize.height =300;
    dst = cvCreateImage( dst_cvsize, src2->depth, src2->nChannels);
    cvResize(src2, dst, CV_INTER_LINEAR);
    string savingfile21(argv[1]);
    savingfile21.erase(savingfile21.find_last_of("."));
    savingfile21 += "-缩放图.tif";
    cvSaveImage(savingfile21.c_str(),dst);*/
    //cvSaveImage("缩放.bmp",dst);



    /*int t1,t2,t3,t4,t5;

        printf("中值滤波1的参数是: \n");
        cin>>t1;
        //t1=atoi(argv[2]);

        printf("中值滤波2的参数是: \n");
        cin>>t2;
        //t2=atoi(argv[3]);

        printf("闭运算的次数是: \n");
        cin>>t3;
        //t3=atoi(argv[4]);

        printf("膨胀腐蚀的次数是：\n");
        cin>>t4;
        //t4=atoi(argv[5]);

        printf("开运算的次数是：\n");
        cin>>t5;
        //t5=atoi(argv[6]);*/

    int height=src->height, width=src->width;//此处注释缩放后去掉
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

    c1 = new double*[width];//x方向角的角度
    c2 = new double*[width];
    c3 = new double*[width];
    c4 = new double*[width];
    xmap=new double*[width];
    ymap=new double*[width];
    zmap=new double*[width];
    xzmap=new double*[width];
    yzmap=new double*[width];
    //lengthmap=new double*[width];//lengthmap法向量的模对应的灰度图像


//#########################################################

    //cvSaveImage("Img灰度图.tif",src);
    //cvSmooth(src , imgBF , CV_BILATERAL,-1,50,0,11);
    //cvSaveImage("ImgBF.bmp",imgBF);

//#########################################################


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
    double w1,w2,w3,* w1_z,* w2_z,* w3_z,dis,* dis_z;//可不可以只定义指针类型的？


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
            //此函数作用是分别求出xyz方向的三个夹角大小
            c1[x][y]=w1;//w1是法向量与与x轴的夹角；
            c2[x][y]=w2;
            c3[x][y]=w3;
            //c4[x][y]=dis;//dis是法向量的模
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
            cvSet2D(image_x,y,x,cvRealScalar(xmap[x][y]));
            cvSet2D(image_y,y,x,cvRealScalar(ymap[x][y]));
            cvSet2D(image_z,y,x,cvRealScalar(zmap[x][y]));

        }
    }




     for(y=0; y<height-1; y++)
    {
        for(x=0; x<width-1; x++)
        {
            xzmap[x][y]=sqrt(xmap[x][y]*xmap[x][y]+zmap[x][y]*zmap[x][y]);
            yzmap[x][y]=sqrt(ymap[x][y]*ymap[x][y]+zmap[x][y]*zmap[x][y]);
            cvSet2D(image_xz,y,x,cvRealScalar(xzmap[x][y]));
            cvSet2D(image_yz,y,x,cvRealScalar(yzmap[x][y]));
         }
    }



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
            cvSet2D(image_xz,y,x,cvRealScalar(xzmap[x][y]));
            cvSet2D(image_yz,y,x,cvRealScalar(yzmap[x][y]));
            }
    }



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


     cvSmooth(image_xz,image_xzBF,CV_BILATERAL,-1,1,40,20);
     cvSmooth(image_yz,image_yzBF,CV_BILATERAL,-1,1,40,20);


//#########################################################


    /*IPL imgx_binary=cvCreateImage(cvGetSize(imagex),IPL_DEPTH_8U,1);
    //创建了一个与imagex图像大小一致的单通道图像，深度是8（2的8次方来表示一个像素，就是256色）
    cvZero(imgx_binary);//cvZero是对图像清零；
    imgx_binary=binary2(imagex,imgx_binary);//将图像imagex用改进的大津法进行二值化，返回的是imgx_binary；
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
    imagexz_binary=binary2(imagexz,imagexz_binary);//大津法二值化，xz方向投影图像
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

//#########################################################


    IPL image_xzBF_binary=cvCreateImage(cvGetSize(image_xz),IPL_DEPTH_8U,1);
    cvZero(image_xzBF_binary);
    image_xzBF_binary=binary2(image_xzBF,image_xzBF_binary);//大津法二值化，xz方向投影图像


    IPL image_yzBF_binary=cvCreateImage(cvGetSize(image_yz),IPL_DEPTH_8U,1);
    image_yzBF_binary=binary2(image_yzBF,image_yzBF_binary);


    IPL img_andxzb_yzbBF=andbmp(image_xzBF_binary,image_yzBF_binary);



    IPL dilate_src=cvCloneImage(img_andxzb_yzbBF);
    IPL imagesmoothM=cvCloneImage(dilate_src);
    IPL imagesmoothM2=cvCloneImage(dilate_src);

    cvSmooth(dilate_src,imagesmoothM,CV_MEDIAN,5,5);
    cvSmooth(imagesmoothM,imagesmoothM2,CV_MEDIAN,3,3);

    IPL image_dilate=cvCloneImage(dilate_src);
    IPL image_kai=cvCloneImage(dilate_src);
    IPL image_bi=cvCloneImage(dilate_src);
    IPL image_temp=cvCloneImage(dilate_src);
    cvSetZero(image_temp);
//#########################################################
    //IPL imageErode=cvCloneImage(dilate_src);
    //IPL imagesmoothG=cvCloneImage(dilate_src);
//#########################################################

    IplConvKernel *element=0;
   IplConvKernel *element2=0;

    element=cvCreateStructuringElementEx(3,3,1,1,CV_SHAPE_ELLIPSE);
    element2=cvCreateStructuringElementEx(2,2,0,0,CV_SHAPE_ELLIPSE);


    //cvErode(imagekai,imageErode,element,2);//迭代次数暂定为；
	//cvSaveImage("imageErode.bmp",imageErode);
    //cvMorphologyEx(imagesmoothM2,imagekai,image_temp,element,CV_MOP_OPEN,3);
    //cvSaveImage("imagekai.bmp",imagekai);


//#########################################################

   /* cvFloodFill(src3,cvPoint(0,0),cvScalar(255),cvScalarAll(0),cvScalarAll(0),NULL,4,NULL);
    string savingfile22(argv[1]);//实验后去
    savingfile22.erase(savingfile22.find_last_of("."));
    savingfile22 += "-FF.tif";
    cvSaveImage(savingfile22.c_str(), src3);*///实验后去除
    //element2=cvCreateStructuringElementEx(2,2,0,0,CV_SHAPE_RECT);

//#########################################################



cvMorphologyEx(imagesmoothM2,image_bi,image_temp,element,CV_MOP_CLOSE,5);
cvDilate(image_bi,image_dilate,element2,5);//可用
IPL contour_src=contourimage(image_dilate);//提取出最大的轮廓
cvErode(contour_src,contour_src,element2,5);//可用
cvMorphologyEx(contour_src,image_kai,image_temp,element,CV_MOP_OPEN,3);//可用


//#########################################################

//    cvMorphologyEx(imagesmoothM2,image_bi,image_temp,element,CV_MOP_CLOSE,5);
//    IPL contour_src=contourimage(image_bi);//提取出最大的轮廓
//    cvMorphologyEx(contour_src,image_kai,image_temp,element,CV_MOP_OPEN,3);//可用

//#########################################################

//#####################################################3

//    for(int n=2;n<argc;n++)
//    {
//                char *image_path=argv[n];
//                if(!strcmp(image_path,"-g"))
//                           save(src3,argv[1],str_gray);
//                else if(!strcmp(image_path,"-x"))
//                            save(imagex,argv[1],str_x);
//                else if(!strcmp(image_path,"-xz"))
//                            save(imagexz,argv[1],str_xz);
//                else if(!strcmp(image_path,"-yz"))
//                            save(imageyz,argv[1],str_yz);
//               else if(!strcmp(image_path,"-y"))
//                            save(imagey,argv[1],str_y);
//                else if(!strcmp(image_path,"-z"))
//                            save(imagez,argv[1],str_z);
//                else if(!strcmp(image_path,"-o"))
//                            save(imgBidui,argv[1],str_o);
//                else
//                            save(imgBidui,argv[1],str_o);
//        }




        IPL   imgBidui=bidui(src2,image_kai);

int flag;
if(argc==2)
{
            flag=0;
            save(imgBidui,argv[1],flag);
}

else
{
            flag=1;
            for(int n=2;n<argc;n+=2)
            {
                        if(check(argv[n]))
                        {
                                    //char *image_path=argv[n+1];
                                    if(check(argv[n+1]))
                                    {
                                                if (!strcmp(argv[n],"-g"))
                                                {
                                                        cout << argv[n+1] <<":   " ;
                                                        save(src3,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                                else if(!strcmp(argv[n],"-x"))
                                                {
                                                        cout << argv[n+1] <<":   "  ;
                                                        save(image_x,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                                else if(!strcmp(argv[n],"-xz"))
                                                {
                                                        cout << argv[n+1] <<":   " ;
                                                        save(image_xz,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                                else if(!strcmp(argv[n],"-yz"))
                                                {
                                                        cout << argv[n+1] << ":   " ;
                                                        save(image_yz,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                                else if(!strcmp(argv[n],"-y"))
                                                {
                                                        cout << argv[n+1] <<":   "  ;
                                                        save(image_y,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                                else if(!strcmp(argv[n],"-z"))
                                                {
                                                        cout << argv[n+1] <<":   " ;
                                                        save(image_z,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                                else if(!strcmp(argv[n],"-o"))
                                                {
                                                        cout << argv[n+1] <<":   " ;
                                                        save(imgBidui,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                                else if(!strcmp(argv[n],"-k"))
                                                {
                                                        cout << argv[n+1] <<":   " ;
                                                        save(image_kai,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                                else if(!strcmp(argv[n],"-b"))
                                                {
                                                        cout << argv[n+1] <<":   " ;
                                                        save(image_bi,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                                else if(!strcmp(argv[n],"-c"))
                                                {
                                                        cout << argv[n+1] <<":   " ;
                                                        save(contour_src,argv[n+1],flag);
                                                        cout << "Done" <<endl;
                                                }
                                        }
                                       else
                                              cout << argv[n+1]  <<":   "<<"Wrong Format" <<endl;
                            }
                            else
                                    cout << argv[n]  <<":   " <<"Error Option" <<endl;
            }
}
//#########################################################


//#########################################################


//       IPL imgBidui=bidui(src2,image_kai);
//
//
//    if(argc==2)
//                save(imgBidui,argv[1],str_o);
//    else
//    {
//            for(int n=2;n<argc;n+=2)
//            {
//                    char *image_path=argv[n+1];
//                    if (!strcmp(argv[n],"-g"))
//                            save_exact(src3,image_path);
//                    else if(!strcmp(argv[n],"-x"))
//                            save_exact(image_x,image_path);
//                    else if(!strcmp(argv[n],"-xz"))
//                                save_exact(image_xz,image_path);
//                    else if(!strcmp(argv[n],"-yz"))
//                                save_exact(image_yz,image_path);
//                    else if(!strcmp(argv[n],"-y"))
//                                save_exact(image_y,image_path);
//                    else if(!strcmp(argv[n],"-z"))
//                                save_exact(image_z,image_path);
//                    else if(!strcmp(argv[n],"-o"))
//                                save_exact(imgBidui,image_path);
//                    else
//                                save_exact(imgBidui,image_path);
//            }
//    }
//

//#########################################################


//
//    IPL imgBidui=bidui(src2,imagekai);
//    //string savingfile19(argv[1]);
//    string savingfile19(argv[1]);
//    savingfile19.erase(savingfile19.find_last_of("."));
//    savingfile19 += "-Bidui.tif";
//   cvSaveImage(savingfile19.c_str(), imgBidui);


//#########################################################





     cvReleaseImage(&image_x);
     cvReleaseImage(&image_y);
     cvReleaseImage(&image_z);
     //cvReleaseImage(&imgx_binary);
     //cvReleaseImage(&imgy_binary);
     //cvReleaseImage(&imgz_binary);
     //cvReleaseImage(&imgandXb_Yb);
     //cvReleaseImage(&imagexz_binary);
     //cvReleaseImage(&imageyz_binary);
     //cvReleaseImage(&imgandxzb_yzb);
     cvReleaseImage(&image_dilate);
     cvReleaseImage(&image_xzBF_binary);
     cvReleaseImage(&image_yzBF_binary);
     cvReleaseImage(&img_andxzb_yzbBF);
     cvReleaseImage(&imagesmoothM2);
     cvReleaseImage(&image_bi);
     cvReleaseImage(&contour_src);
     cvReleaseImage(&image_kai);
     cvReleaseImage(&imgBidui);

//      }
     //cvReleaseImage(&dst);





     return 0;
   }

