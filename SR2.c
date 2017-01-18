/***
Author : Kartik Sooji (ksooji)

Assignment 4 : Edge Detection 

***/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	int height = 500 , width = 500 ;//raw image size
	int x= 0, y=0, i = 0,j = 0,sum=0;
	unsigned char RawData[height][width], gData_x[height][width], gData_y[height][width], gData[height][width];

	const int size_x = 5, size_y = 5;
	int Sobel_x[5][5] = {{ -1, -2, 0, 2, 1}, { -2, -4, 0, 4, 2}, { -4, -8, 0, 8, 4}, { -2, -4, 0, 4, 2}, { -1, -2, 0, 2, 1}};
	int Sobel_y[5][5] = {{-1, -2, -4, -2, -1}, { -2, -4, -8, -4, -2}, { 0, 0, 0, 0, 0}, { 2, 4, 8, 4, 2}, { 1, 2, 4, 2, 1}};

	
	FILE *fp,*fd;  //file descriptors
    fp=fopen("/home/ksooji/MM/A4/bikes.raw","rb");  //open file
    if(!fp)
    {
        printf("ERROR!\n");
    }
    fread(RawData,sizeof(unsigned char),(height *width),fp);  //RawData is the image
    fclose(fp); //close fp file descriptor

	// Applying Horizontal of 5*5

	for (j = 2; j <= height - 2; j++) {
		for ( i = 2; i <= width - 2; i++) {
			sum = 0;
			for (y = 0; y < size_y; y++) {
				for ( x = 0; x < size_x; x++) {
					sum += RawData[y + j - 1][x + i - 1] * Sobel_x[y][x];
				}
				gData_x[j][i] = (sum / 128 ) ; 
			}
		}
	}
	
	
	// Applying Verical filter of 5*5
	
	for (j = 2; j <= height - 2; j++) {
		for ( i = 2; i <= width - 2; i++) {
			sum = 0;
			for (y = 0; y < size_y; y++) {
				for ( x = 0; x < size_x; x++) {
					sum += RawData[y + j - 1][x + i - 1] * Sobel_y[y][x];
				}
				gData_y[j][i] = (sum / 128) ; 
			}
		}
	}
	
	for (j = 1; j <= height - 1; j++) {
		for ( i = 1; i <= width - 1; i++) {	
			gData[j][i] = sqrt ( (gData_x[j][i] * gData_x[j][i]) + (gData_y[j][i] * gData_y[j][i]));
		}
	}

    fd=fopen("/home/ksooji/MM/A4/Sr2.raw","wb");
    fwrite(gData,sizeof(unsigned char),sizeof(gData),fd);
    fclose(fd); //close fp file descriptor
    return 0;
}