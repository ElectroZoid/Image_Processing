#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main(int argc, char **argv)
{   
    srand(time(NULL));
    char type[3];
    int numRow, numCol, maxNum;
    FILE *oldFile,*newFile;
    char buffer[5];

    oldFile = fopen(argv[1], "rb");

    if(oldFile == NULL) {
        fprintf(stderr, "Could not open file %s for reading in binary", argv[1]);
        return 0;
    }
    fscanf(oldFile, "%2s", type);
    type[2] = '\0';
    if(strcmp(type, "P6") != 0) {  //Make sure we have a P6 file
        printf("This file is not of type P6");
        return 0;
    }

    /*The max number that can represent a colour*/
    fscanf(oldFile, "%d", &numCol);
    fscanf(oldFile, "%d", &numRow);
    fscanf(oldFile, "%d", &maxNum);

    newFile=fopen("Treenew.ppm","wb");
    fprintf(newFile,"P6\n");
    fprintf(newFile,"%d %d\n",numCol,numRow);
    fprintf(newFile,"%d\n",maxNum);


    fseek(oldFile, 1, SEEK_CUR);

    unsigned char old[numRow][numCol][3];

    for (int i=0;i<numRow;i++){
        for (int j=0;j<numCol;j++){
            fread(old[i][j], 1, 3, oldFile);
            
            //b&w
            int newval=(0.299*(old[i][j][0]))+(0.587*(old[i][j][1]))+(0.114*(old[i][j][2]));
            old[i][j][0]=old[i][j][1]=old[i][j][2]=newval;
            
            //random colorful
            // old[i][j][0]=rand()%256;
            // old[i][j][1]=rand()%256;
            // old[i][j][2]=rand()%256;

            //random b&w
            // old[i][j][0]=old[i][j][1]=old[i][j][2]=rand()%maxNum;
            // fwrite(old[i][j],1,3,newFile);
        }
    }

    //edge detection

    unsigned char new[numRow][numCol][3];
    memset(new,0,sizeof(new));

    int threshold=100;

    for (int i=1;i<numRow-1;i++){
        for (int j=1;j<numCol-1;j++){

            int val_x=(-1*old[i-1][j-1][0])+(-2*old[i][j-1][0])+(-1*old[i+1][j-1][0])+\
                    (1*old[i-1][j+1][0])+(2*old[i][j+1][0])+(1*old[i+1][j+1][0]);
            
            int val_y=(1*old[i-1][j-1][0])+(2*old[i-1][j][0])+(1*old[i-1][j+1][0])+\
                    (-1*old[i+1][j-1][0])+(-2*old[i+1][j][0])+(-1*old[i+1][j+1][0]);

            int val=sqrt(pow(val_x,2)+pow(val_y,2));

            if (val>threshold){
                new[i][j][0]=new[i][j][1]=new[i][j][2]=maxNum;
            }


        }
    }

    for (int i=0;i<numRow;i++){
        for (int j=0;j<numCol;j++){
            fwrite(new[i][j],1,3,newFile);
        }
    } 
 
}