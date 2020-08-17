#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char outputfn[20];
    int i = 0;
    int counter = 0;
    FILE *outputJPEG = NULL;
    unsigned char tempArray[512];
    if (argc < 2)
    {
        printf("Please provide name of image.\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r"); //reads inputted file
    if (file == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }
    //iterate through file looking for signature jpeg starters 512 bytes at a time
    while (fread (tempArray, 512, 1, file) > 0)
    {
        if ((tempArray[0] == 0xff) && (tempArray[1] == 0xd8) && (tempArray[2] == 0xff) && ((tempArray[3] >= 0xe0) && (tempArray[3] <= 0xef)))
        {
            //when it finds, create a new file (naming it i.jpeg where i starts from 000)
            if (outputJPEG == NULL)
            {
                sprintf(outputfn, "%03d.jpg", counter);
                counter ++;
                outputJPEG = fopen(outputfn, "w");
                //add the bytes into the file 512 bytes at a time
                fwrite(tempArray, 512, 1, outputJPEG);

            }
            else
            {
                fclose(outputJPEG);
                sprintf(outputfn, "%03d.jpg", counter);
                counter ++;
                outputJPEG = fopen(outputfn, "w");
                //add the bytes into the file 512 bytes at a time
                fwrite(tempArray, 512, 1, outputJPEG);
            }
        }
        else
            {
                if (outputJPEG != NULL)
                {
                    fwrite(tempArray, 512, 1, outputJPEG);
                }
            }
    }
    fclose(file);
    fclose(outputJPEG);
}
