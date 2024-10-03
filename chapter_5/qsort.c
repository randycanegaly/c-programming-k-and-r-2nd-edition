#include <stdio.h>


void swap(int v[], int i, int j) {
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort (int v[], int left, int right) {
    int i, last;
    
    if(left >= right)
        return;
    swap(v, left, (left + right)/2);//this puts pivot (was middle) in the 0th position
    last = left;//set last = 0
    for (i = left+1; i <= right; i++)//walk from pos 1 to the end
        if (v[i] < v[left])
            swap(v, ++last, i);
    
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

int main(void) {
    int str[5];
    str[0] = 2;
    str[1] = 4;
    str[2] = 3;
    str[3] = 5;
    str[4] = 1;

    qsort(str, 0, 4);
    for (int i = 0; i < 5; i++) {
        printf("%d\n", str[i]);
    }
}
