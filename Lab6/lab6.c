#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
int img[2000][2000][3], gray[2000][2000], yiq[2000][2000][3];

int main()
{
    srand(time(0));
    struct timeval TimeValue_Start;
    struct timezone TimeZone_Start;
    struct timeval TimeValue_Final;
    struct timezone TimeZone_Final;
    long time_start, time_end;
    double time_overhead;

    int t, Height, Width;
    printf("Enter number of threads you want to use : ");
    scanf("%d", &t);
    char filename[20];
    printf("Enter file to use with its Width and Height: ");
    scanf(" %s %d %d", filename, &Width, &Height);

    FILE *file;
    file = fopen(filename, "r");

    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
            fscanf(file, "%d %d %d", &img[i][j][0], &img[i][j][1], &img[i][j][2]);
    }

    int i, j;
    gettimeofday(&TimeValue_Start, &TimeZone_Start);
#pragma omp parallel for private(i, j) collapse(2) num_threads(t)
    for (i = 0; i < Height; i++)
    {
        for (j = 0; j < Width; j++)
        {
            gray[i][j] = img[i][j][0] * 0.21 + img[i][j][1] * 0.72 + img[i][j][2] * 0.07;
        }
    }

    for (i = 0; i < Height; i++)
    {
        for (j = 0; j < Width; j++)
        {
            yiq[i][j][0] = ((float)img[i][j][0] * 0.299) + ((float)img[i][j][1] * 0.587) + ((float)img[i][j][2] * 0.114);
            yiq[i][j][1] = ((float)img[i][j][0] * 0.596) - ((float)img[i][j][1] * 0.275) - ((float)img[i][j][2] * 0.321);
            yiq[i][j][2] = ((float)img[i][j][0] * 0.212) - ((float)img[i][j][1] * 0.523) + ((float)img[i][j][2] * 0.311);
        }
    }

    gettimeofday(&TimeValue_Final, &TimeZone_Final);
    time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
    time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
    time_overhead = (time_end - time_start) / 1000000.0;
    printf("Time taken : %lf seconds\n", time_overhead);

    file = fopen("gray.pgm", "wb");
    fprintf(file, "P2 ");
    fprintf(file, "%d %d 255\n", Width, Height);

    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            fprintf(file, "%d ", gray[i][j]);
        }
        fprintf(file, "\n");
    }

    file = fopen("yiq.ppm", "wb");
    fprintf(file, "P6 ");
    fprintf(file, "%d %d 255\n", Width, Height);
    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            fprintf(file, "%d %d %d ", yiq[i][j][0], yiq[i][j][1], yiq[i][j][2]);
        }
        fprintf(file, "\n");
    }

    return 0;
}
