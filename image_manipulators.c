#include <stdio.h>
#include <math.h>

void grey_scale(unsigned char*** old_pixel,unsigned char*** new_pixel,int numRow,int numCol,int maxNum){

    for (int i=0;i<numRow;i++){
        for (int j=0;j<numCol;j++){
            int newval_pixel=(0.299*(old_pixel[i][j][0]))+(0.587*(old_pixel[i][j][1]))+(0.114*(old_pixel[i][j][2]));
            new_pixel[i][j][0]=new_pixel[i][j][1]=new_pixel[i][j][2]=newval_pixel;
        }
    }
}


void edge_detection(unsigned char*** old_pixel,unsigned char*** new_pixel,int numRow,int numCol,int maxNum,int threshold){

    grey_scale(old_pixel,new_pixel,numRow,numCol,maxNum);

    for (int i=1;i<numRow-1;i++){
        for (int j=1;j<numCol-1;j++){

            int val_x=(-1*new_pixel[i-1][j-1][0])+(-2*new_pixel[i][j-1][0])+(-1*new_pixel[i+1][j-1][0])+\
                    (1*new_pixel[i-1][j+1][0])+(2*new_pixel[i][j+1][0])+(1*new_pixel[i+1][j+1][0]);
            
            int val_y=(1*new_pixel[i-1][j-1][0])+(2*new_pixel[i-1][j][0])+(1*new_pixel[i-1][j+1][0])+\
                    (-1*new_pixel[i+1][j-1][0])+(-2*new_pixel[i+1][j][0])+(-1*new_pixel[i+1][j+1][0]);

            int val=sqrt(pow(val_x,2)+pow(val_y,2));

            if (val>threshold){
                new_pixel[i][j][0]=new_pixel[i][j][1]=new_pixel[i][j][2]=maxNum;
            }
            else{
                new_pixel[i][j][0]=new_pixel[i][j][1]=new_pixel[i][j][2]=0;
            }
        }
    }



}