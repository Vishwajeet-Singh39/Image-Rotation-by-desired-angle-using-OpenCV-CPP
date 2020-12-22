#include<iostream>
#include<opencv2/opencv.hpp>
#include<cmath>
using namespace std;
using namespace cv;
int main(){
    Mat img=imread("D:/Stuff/GitHub/Image-Rotation-by-desired-angle-using-OpenCV-CPP/goku.jpg");
    if(img.empty()){
        cout<<"Error";
    }
    double angle;
    int a;
    label:
    cout<<endl<<endl<<"         MENU        "<<endl
    <<"Enter 1 to Rotate the image by desired angle."<<endl
    <<"Enter 2 to Loop through all the rotations from 0 degree to 360 degree"<<endl
    <<"Enter 3 to exit"<<endl
    <<"Enter your choice: ";
    cin>>a;
    if(a==1){
        cout<<"Enter Angle: ";
        cin>>angle;
    }
    else if(a==2){
        angle=0;
    }
    else if(a==3){
        return 0;
    }
    else{
        cout<<"Invalid Choice";
        goto label;
    }
    do{
        double deg=angle*3.14/180;
        double w=(img.rows)*abs(sin(deg))+(img.cols)*abs(cos(deg));
        double h=(img.cols)*abs(sin(deg))+(img.rows)*abs(cos(deg));
        
        Mat res;
        Mat tgt(h,w,img.type());
        double x=(w-img.cols)/2;
        double y=(h-img.rows)/2;
        Mat m = (Mat_<double>(2,3) << 1, 0, x+(img.cols/2), 0, 1, y+(img.rows/2)); 
        warpAffine(img,res,m, Size(tgt.cols*4,tgt.rows*4)); 

        Point2d pt((img.cols/2)+x+(img.cols/2), (img.rows/2)+y+(img.rows/2));   
        Mat r = getRotationMatrix2D(pt,angle, 1.0);
        Mat result;
        warpAffine(res,res,r, Size(tgt.cols*4,tgt.rows*4));

        Mat n = (Mat_<double>(2,3) << 1, 0, -img.cols/2, 0, 1, -img.rows/2); 
        warpAffine(res,result,n, Size(tgt.cols,tgt.rows)); 
        imshow("Display (Press any key to close window)",result);
        waitKey(100);
        angle+=1;
    }
    while(angle<=360 && a==2);
    waitKey();
    destroyWindow("Display (Press any key to close window)");
    goto label;
}