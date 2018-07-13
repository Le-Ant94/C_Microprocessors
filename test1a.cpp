#include "mbed.h"
#include "stdint.h"

void sort_up(uint32_t num[], int length)
{
    int x = 0, y = 0, temp;
    
    for (x = 0; x < length - 1; x++)
    {
        for (y = 0; y < (length - x - 1); y++)
        {
            if (num[y] > num[y + 1])
            {
                temp = num[y];
                num[y] = num[y + 1];
                num[y + 1] = temp;
            }
        }
    }
}

