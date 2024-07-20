#ifndef image_manipulators_H
#define image_manipulators_H


unsigned char*** create_list(int numRow,int numCol);

void free_list(unsigned char*** list,int numRow,int numCol);

void grey_scale(unsigned char*** old_pixel,unsigned char*** new_pixel,int numRow,int numCol,int maxNum);

void edge_detection(unsigned char*** old_pixel,unsigned char*** new_pixel,int numRow,int numCol,int maxNum,int threshold);

#endif