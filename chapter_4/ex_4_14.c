#include <stdio.h>

#define swap(t, x, y) { t temp; temp = x, x = y, y = temp; }

int main()
{
    int x = 2;
    int y = 4;
  
    swap(int, x, y);
    
    printf("x, y swapped = %d %d\n", x, y);
    return 0;
}
