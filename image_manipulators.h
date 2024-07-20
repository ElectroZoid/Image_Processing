#ifndef image_manipulators_H
#define image_manipulators_H

void grey_scale(unsigned char*** old_pixel,unsigned char*** new_pixel,int numRow,int numCol,int maxNum);

void edge_detection(unsigned char*** old_pixel,unsigned char*** new_pixel,int numRow,int numCol,int maxNum,int threshold);

#endif