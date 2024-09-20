#include <stdio.h>

#define MAX_ARR 100

/*there is no perceivable performance difference between the two versions
 * of binsearch()
 * both ~ 3ms
 */

int binsearch(int x, int v[], int n);
int new_binsearch(int x, int v[], int n);

int main(void) {
    int x = 14;
    int v[] = {2, 3, 7, 11, 13, 14, 20, 23, 51};
    int n = 9;

    //printf("%d\n", binsearch(x, v, n));
    printf("%d\n", new_binsearch(x, v, n));
}

int new_binsearch(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;
    mid = (low + high) / 2;//initial value of mid
    while (low <= high && x != v[mid]) {
        if (x < v[mid])
            high = mid - 1;
        else 
            low = mid + 1;
    
        mid = (low + high) / 2;//calculate new mid
    }

    if (x == v[mid])
        return mid;
    else
        return -1;
}

int binsearch(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
