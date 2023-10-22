#include <stdio.h>
#include <stdlib.h>
#include <FreeImage.h>
#include <mpi.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int countPixels(BYTE *data, int width, int height, BYTE targetPixelValue) {
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (data[i * width + j] == targetPixelValue) {
                count++;
            }
        }
    }
    return count;
}

void create(FIBITMAP *image, FIBITMAP **outputImage, char *filename, int height, int width) {
    if (image == NULL) {
        printf("Invalid image.\n");
        return;
    }

    *outputImage = FreeImage_Allocate(width, height, 8, 0, 0, 0);

    if (*outputImage == NULL) {
        printf("Failed to allocate output image.\n");
        return;
    }

    for (int i = 0; i < height; i++) {
        BYTE *scanline = FreeImage_GetScanLine(*outputImage, i);
        BYTE *inputScanline = FreeImage_GetScanLine(image, i);

        for (int j = 0; j < width; j++) {
            scanline[j] = inputScanline[j];
        }
    }

    if (FreeImage_Save(FIF_BMP, *outputImage, filename, BMP_DEFAULT)) {
        printf("Reconstructed image saved successfully.\n");
    } else {
        printf("Failed to save the reconstructed image.\n");
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    FIBITMAP *image = NULL;
    FIBITMAP *outputImage = NULL;
    if (rank == 0) {
        image = FreeImage_Load(FIF_JPEG, "/home/dmacs-5/Documents/mtech_2023/Image Processing/DSC_0263.JPG", 0);
        if (!image) {
            fprintf(stderr, "Failed to load the image.\n");
            MPI_Finalize();
            return 1;
        }
        int width = FreeImage_GetWidth(image);
        int height = FreeImage_GetHeight(image);
        create(image, &outputImage, "/home/dmacs-5/Documents/mtech_2023/Image Processing/output.bmp", height, width);
        MPI_Bcast(&width, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&height, 1, MPI_INT, 0, MPI_COMM_WORLD);
        int localwidth = width / size;
        int localheight = height;
        BYTE *localdata = (BYTE *)malloc(localwidth * localheight);

        // Calculate the start and end columns for this rank
        int startCol = rank * localwidth;
        int endCol = (rank + 1) * localwidth;

        // Create a local image part for this rank
        FIBITMAP *localImage = FreeImage_Allocate(localwidth, localheight, 24, 0, 0, 0);

        for (int x = 0; x < localwidth; x++) {
            for (int y = 0; y < localheight; y++) {
                RGBQUAD pixel;
                FreeImage_GetPixelColor(image, startCol + x, y, &pixel);
                FreeImage_SetPixelColor(localImage, x, y, &pixel);
            }
        }

        // Save the local image part for this rank
        char localFilename[50];
        snprintf(localFilename, sizeof(localFilename), "local_image_%d.bmp", rank);

        if (FreeImage_Save(FIF_BMP, localImage, localFilename, BMP_DEFAULT)) {
            printf("Saved partitioned image for rank %d as %s\n", rank, localFilename);
        } else {
            printf("Failed to save the partitioned image for rank %d\n", rank);
        }

        FreeImage_Unload(localImage);

        char hostname[256];
        gethostname(hostname, sizeof(hostname));
        printf("Rank %d is running on host %s\n", rank, hostname);

        MPI_Scatter(FreeImage_GetBits(image), localwidth * localheight, MPI_UNSIGNED_CHAR, localdata,
                    localwidth * localheight, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
        BYTE targetPixelValue = 255;
        int localPixelCount = countPixels(localdata, localwidth, localheight, targetPixelValue);
        int totalPixelCount = 0;
        MPI_Reduce(&localPixelCount, &totalPixelCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            printf("Total number of white pixels: %d\n", totalPixelCount);
        }

        char path_of_destination[256];
        snprintf(path_of_destination, sizeof(path_of_destination), "/home/");
        if (access(path_of_destination, F_OK) != 0) {
            mkdir(path_of_destination, 0777);
        }

        BYTE *collectedImage = NULL;
        if (rank == 0) {
            collectedImage = (BYTE *)malloc(width * height * sizeof(BYTE));
        }

        MPI_Gather(localdata, localwidth * localheight, MPI_UNSIGNED_CHAR, collectedImage,
                   localwidth * localheight, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

        printf("------------------------\n");

        if (rank == 0) {
            char outputFilename[] = "new_reconstructed_image.bmp";
            create(image, &outputImage, outputFilename, height, width);
            free(collectedImage);
            FreeImage_Unload(image);
        }

        free(localdata);
    }

    MPI_Finalize();
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include<FreeImage.h>
// // #include<mpi.h>
// // #include<unistd.h>
// // #include<sys/stat.h>
// // #include <sys/types.h>

// // int countPixels(BYTE *data,int width,int height,BYTE targetPixelValue){
// //     int count =0;
// //     for (int i = 0; i < height; i++)
// //     {
// //      for (int j = 0; j < width; j++)
// //      {
// //       if(data[i*width+j] == targetPixelValue){
// //         count++;
// //       }  /* code */
// //      }
// //         /* code */
// //     }
// //     return count;
    
// // }
// // // void readFile(const char *filename,BYTE* data, int count){
// // //     int j =0;
// // //     FILE *file = fopen(filename,"r");
// // //     if(file==NULL){
// // //         perror("Error opening the file");
// // //         // return NULL;
// // //     }
// // //     else{
// // //         for (int i = 0; i < count; i++)
// // //         {
// // //          if(fscanf(file,"%hhu",&data[i])==1){
// // //             j++;
// // //             if(j<count){
// // //                 int separate;
// // //                 if(fscanf(file,"%d",&separate)!=1 || separate != ' ')
// // //                     break;
// // //             }
// // //          }   /* code */
// // //         }
// // //           fclose(file);
// // //     }
  
// // // }

// // // void writeFile(char* filename,BYTE* data,int count){
// // //     FILE *file1 = fopen(filename,"w");
// // //     if(file1==NULL){
// // //         perror("Error!! Empty file");
// // //     }
// // //     else{
// // //         for (int i = 0; i < count; i++)
// // //         {
// // //          fprintf(file1, "%d" ,data[i]);
// // //          if(i<count-1){
// // //             fprintf(file1, " ");
// // //          }   /* code */
// // //         }
// // //         fclose(file1);
// // //     }
// // // }

// // // void create(BYTE *data,char*filename,int height,int width){
// // //     FIT_BITMAP *image = FreeImage_Allocate(width,height,8,0,0,0);

    
// // //     if (image == NULL) {
// // //         printf("Failed to allocate image.\n");
// // //         return;
// // //     }

// // //     for (int i = 0; i < height; i++) {
// // //         BYTE* scanline = FreeImage_GetScanLine(image, i);
// // //         for (int j = 0; j < width; j++) {
// // //             scanline[j] = data[i * width + j];
// // //         }
// // //     }

// // //     if (FreeImage_Save(FIF_BMP, image, filename, BMP_DEFAULT)) {
// // //         printf("Reconstructed image saved successfully.\n");
// // //     } else {
// // //         printf("Failed to save the image.\n");
// // //     }

// // //     FreeImage_Unload(image);
// // // }
// // void create(FIBITMAP *image, FIBITMAP **outputImage, char *filename,int height,int width) {
// //     if (image == NULL) {
// //         printf("Invalid image.\n");
// //         return;
// //     }

// //     // int width = FreeImage_GetWidth(image);
// //     // int height = FreeImage_GetHeight(image);

// //     *outputImage = FreeImage_Allocate(width, height, 8, 0, 0, 0);

// //     if (*outputImage == NULL) {
// //         printf("Failed to allocate output image.\n");
// //         return;
// //     }

// //     for (int i = 0; i < height; i++) {
// //         BYTE *scanline = FreeImage_GetScanLine(*outputImage, i);
// //         BYTE *inputScanline = FreeImage_GetScanLine(image, i);

// //         for (int j = 0; j < width; j++) {
// //             scanline[j] = inputScanline[j];
// //         }
// //     }

// //     if (FreeImage_Save(FIF_BMP, *outputImage, filename, BMP_DEFAULT)) {
// //         printf("Reconstructed image saved successfully.\n");
// //     } else {
// //         printf("Failed to save the reconstructed image.\n");
// //     }
// // }

// int main(int argc,char *argv[]){
//     MPI_Init(&argc,&argv);
//     int rank,size;
//     MPI_Comm_rank( MPI_COMM_WORLD , &rank);
//     MPI_Comm_size( MPI_COMM_WORLD , &size);
    
//     FIBITMAP* image = NULL;
//     FIBITMAP *outputImage = NULL;
//     if(rank==0){
//         image = FreeImage_Load(FIF_JPEG,"/home/dmacs-5/Documents/mtech_2023/Image Processing/DSC_0263.JPG",0);
//         if(!image){
//             fprintf(stderr,"Failed to load the image.\n");
//             MPI_Finalize();
//             return 1;
//         }
//         int width = FreeImage_GetWidth(image);
//         int height = FreeImage_GetHeight(image);
//         create(image,&outputImage,"/home/dmacs-5/Documents/mtech_2023/Image Processing/output.bmp",height,width);
//         MPI_Bcast( &width , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
//         MPI_Bcast( &height , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
//         int localwidth = width/size;
//         int localheight = height;
//         BYTE* localdata =(BYTE*)malloc(localwidth*localheight);
//          for (int r = 0; r < size; r++) {
//             //     RGBQUAD pixel;
//                     FreeImage_GetPixelColor(image, startCol + x, y, &pixel);
//                 // Calculate the start and end columns for this rank
//             int startCol = r * localwidth;
//             int endCol = (r + 1) * localwidth;
            
//             // Create a local image part for this rank
//             FIBITMAP* localImage = FreeImage_Allocate(localwidth, localheight, 24, 0, 0, 0);
            
//             for (int x = 0; x < localwidth; x++) {
//                 for (int y = 0; y < localheight; y++) {
//                     FreeImage_SetPixelColor(localImage, x, y, &pixel);
//                 }
//             }
            
//             // Save the local image part for this rank
//             char localFilename[50];
//             snprintf(localFilename, sizeof(localFilename), "local_image_%d.bmp", r);
            
//             if (FreeImage_Save(FIF_BMP, localImage, localFilename, BMP_DEFAULT)) {
//                 printf("Saved partitioned image for rank %d as %s\n", r, localFilename);
//             } else {
//                 printf("Failed to save the partitioned image for rank %d\n", r);
//             }
            
//             FreeImage_Unload(localImage);
//         }
    
//         char hostname[256];
//         gethostname(hostname,sizeof(hostname));
//         printf("Rank %d is running on host %s\n",rank,hostname);
//         MPI_Scatter( FreeImage_GetBits(image) , localwidth*localheight , MPI_UNSIGNED_CHAR , localdata , localwidth*localheight , MPI_UNSIGNED_CHAR , 0 , MPI_COMM_WORLD);
//         BYTE targePixelValue = 255;
//         int localPixelCount = countPixels(localdata,localwidth,localheight,targePixelValue);
//         int totalPixelCount = 0;
//         MPI_Reduce(&localPixelCount,&totalPixelCount,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
//         if(rank==0){
//             printf("Total number of white pixels: %d\n", totalPixelCount);
//         }
//         char path_of_destination[256];
//         snprintf(path_of_destination,sizeof(path_of_destination),"/home/");
//         if(access(path_of_destination,F_OK)!=0){
//             mkdir(path_of_destination,0777);
//         }

//          BYTE *collectedImage = NULL;
//         if (rank == 0) {
//             collectedImage = (BYTE *)malloc(width * height * sizeof(BYTE));
//         }

//         MPI_Gather(
//             localImage,
//             localPixelCount,
//             MPI_BYTE
//             collectedImage,
//             localPixelCount,
//             MPI_BYTE,
//             0,
//             MPI_COMM_WORLD
//         );

//         printf("--------------------\n");
//         // Create the final image on rank 0
//         // if (rank == 0) {
//         //     create(image,&outputImage,"/home/dmacs-5/Documents/mtech_2023/Image Processing/output2.bmp");
//         //     free(collectedImage);
//         // }
//         if (rank == 0) {
//              char outputFilename[] = "reconstructed_image.bmp";
//              create(image,collectedImage, outputFilename,height,width);
//              free(collectedImage);
//              FreeImage_Unload(image);
//             }

//         // FreeImage_Unload(image);
//         // FreeImage_Unload(outputImage);
//         free(localdata);
//     }   
//     MPI_Finalize();
// return 0;
// }
