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
        
    /* If name of output file is not specified,
        new name of file would be oldfile_name+OUT+.ppm */
    
    if (argc==3){
        char newFile_name[strlen(argv[1])+4];
        int j=0;
        for (int i=0;i<strlen(argv[1]);i++){
            if (argv[1][i]=='.'){
                newFile_name[j++]='O';
                newFile_name[j++]='u';
                newFile_name[j++]='t';
                newFile_name[j++]=argv[1][i];
            }
            else{
                newFile_name[j++]=argv[1][i];
            }
        }
        newFile_name[j]='\0';
        newFile=fopen(newFile_name,"wb");        
    }
    else{
        newFile=fopen(argv[2],"wb");
    }

    fprintf(newFile,"P6\n");
    fprintf(newFile,"%d %d\n",numCol,numRow);
    fprintf(newFile,"%d\n",maxNum);


    fseek(oldFile, 1, SEEK_CUR);

    unsigned char ***old_pixel=(unsigned char***)malloc(sizeof(unsigned char**)*numRow);
    unsigned char ***new_pixel=(unsigned char***)malloc(sizeof(unsigned char**)*numRow);
    for (int i=0;i<numRow;i++){
        old_pixel[i]=(unsigned char**)malloc(sizeof(unsigned char*)*numCol);
        new_pixel[i]=(unsigned char**)malloc(sizeof(unsigned char*)*numCol);
        for (int j=0;j<numCol;j++){
            old_pixel[i][j]=(unsigned char*)calloc(3,sizeof(unsigned char));
            new_pixel[i][j]=(unsigned char*)calloc(3,sizeof(unsigned char));
        }
    }

    for (int i=0;i<numRow;i++){
        for (int j=0;j<numCol;j++){
            fread(old_pixel[i][j], 1, 3, oldFile);
            
            //b&w
            int newval=(0.299*(old_pixel[i][j][0]))+(0.587*(old_pixel[i][j][1]))+(0.114*(old_pixel[i][j][2]));
            old_pixel[i][j][0]=old_pixel[i][j][1]=old_pixel[i][j][2]=newval;
            
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

    // unsigned char new[numRow][numCol][3];
    // memset(new,0,sizeof(new));

    int threshold=100;

    for (int i=1;i<numRow-1;i++){
        for (int j=1;j<numCol-1;j++){

            int val_x=(-1*old_pixel[i-1][j-1][0])+(-2*old_pixel[i][j-1][0])+(-1*old_pixel[i+1][j-1][0])+\
                    (1*old_pixel[i-1][j+1][0])+(2*old_pixel[i][j+1][0])+(1*old_pixel[i+1][j+1][0]);
            
            int val_y=(1*old_pixel[i-1][j-1][0])+(2*old_pixel[i-1][j][0])+(1*old_pixel[i-1][j+1][0])+\
                    (-1*old_pixel[i+1][j-1][0])+(-2*old_pixel[i+1][j][0])+(-1*old_pixel[i+1][j+1][0]);

            int val=sqrt(pow(val_x,2)+pow(val_y,2));

            if (val>threshold){
                new_pixel[i][j][0]=new_pixel[i][j][1]=new_pixel[i][j][2]=maxNum;
            }


        }
    }

    for (int i=0;i<numRow;i++){
        for (int j=0;j<numCol;j++){
            fwrite(new_pixel[i][j],1,3,newFile);
        }
    } 
 
}