#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "image_manipulators.h"

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
        }
    }

    if (argv[argc-1][0]=='1'){
        grey_scale(old_pixel,new_pixel,numRow,numCol,maxNum);       
    }
    else if (argv[argc-1][0]=='2'){
        edge_detection(old_pixel,new_pixel,numRow,numCol,maxNum,100);
    }


    for (int i=0;i<numRow;i++){
        for (int j=0;j<numCol;j++){
            fwrite(new_pixel[i][j],1,3,newFile);
        }
    } 
 
}