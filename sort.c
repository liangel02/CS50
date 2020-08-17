#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

int array[] = {6,18, 3, 2, 5, 7, 12, 1};
int arraySize = sizeof(array) / sizeof(int);
bool sortPairs (int start, int end, int *pivot);
void swap(int *a, int *b);


int main (void)
{
    int i = 0;
            for (i = 0; i < arraySize; i++)
        {
            printf ("%d, ", array[i]);
        }
        printf("\n");
    if (sortPairs(0, arraySize, &array[0]))
    {
        for (i = 0; i < arraySize; i++)
        {
            printf ("%d, ", array[i]);
        }
        printf("\n");
    }
}

bool sortPairs (int start, int end, int *pivot)
{
    //sort pairs depending on what is in preferences
    int i = start, j = end;
    if (start == end)
    {
        return true;
    }
    while (true)
    {
        j--;
        while (i < end)
        {
            if (array[i] < *pivot) //find num that is less than pivot
            {
                break;
            }
            else
            {
                i++;
            }
        }
        while (j > start)
        {
            if (array[j] > *pivot) //find num that is greater than pivot
            {
                break;
            }
            else
            {
                j--;
            }
        }
        if (i > j)
        {
            break;
        }
        swap(&array[i], &array[j]); //swap the 2
        i++;
    }

    if ((j > start) && (i == end))
    {
        swap(pivot, &array[j]); //swap final j with pivot, pivot is now in sorted position
    }
    else if ((i != end) && (j != start))
    {
        swap(pivot, &array[j]); //swap final j with pivot, pivot is now in sorted position
    }
    //quick sort left half
    sortPairs(start, j, &array[start]);
    //quick sort right half
    sortPairs(j + 1, end, &array[j+1]);
    return true;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}