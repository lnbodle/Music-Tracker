#include <stdio.h>

float remap(float index, float low1, float high1, float low2, float high2)
{
    return low2 + (index - low1) * (high2 - low2) / (high1 - low1);
}

size_t increase_index(size_t index, size_t size)
{

    if (index >= size - 1)
    {
        index = 0;
    }
    else
    {
        index++;
    }

    return index;
}

size_t decrease_index(size_t index, size_t size)
{
    if (index <= 0)
    {
        index = size - 1;
    }
    else
    {
        index--;
    }
    
    return index;
}