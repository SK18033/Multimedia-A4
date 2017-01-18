/***
Author : Kartik Sooji (ksooji)

Assignment 4 : Edge Detection 

***/

#include<stdio.h>
#include<stdlib.h>

int main()
{
	int height = 500 , width = 500 ;//raw image size
	int i = 0,j = 0, delta=60;
	unsigned char Data[height][width],RawData[height][width];

	FILE *fp,*fd;  //file descriptors
    fp=fopen("/home/ksooji/MM/A4/Sr1.raw","rb");  //open file
    if(!fp)
    {
        printf("ERROR!\n");
    }
    fread(RawData,sizeof(unsigned char),(height *width),fp);  //RawData is the image
    fclose(fp); //close fp file descriptor
	
	
	// Loop to collect the peak values of the gradients
	
    for ( i = 0; i < height - 1; i++){
		for( j = 0; j < width - 1 ; j++){	
			if(RawData[i][j] > 0 ){
				Data[i][j] = 0;
	            if(RawData[i][j] > 0){
	               
				   if(RawData[i][j] > RawData[i-1][j] && RawData[i][j] >= RawData[i+1][j] && RawData[i][j] > delta ||
	               	  RawData[i][j] < RawData[i-1][j] && RawData[i][j] <= RawData[i+1][j] && RawData[i][j] < -delta )
						Data[i][j] = 255;
	               
				   else if(RawData[i][j] > RawData[i][j-1] && RawData[i][j] >= RawData[i][j+1] && RawData[i][j] > delta ||
	               		   RawData[i][j] < RawData[i][j-1] && RawData[i][j] <= RawData[i][j+1] && RawData[i][j] < -delta )
						Data[i][j] = 255;
	           }
			}	

		}
	}

    fd=fopen("/home/ksooji/MM/A4/Edge_3x3.raw","wb");
    fwrite(Data,sizeof(unsigned char),sizeof(Data),fd);
    fclose(fd); //close fp file descriptor
    return 0;
}