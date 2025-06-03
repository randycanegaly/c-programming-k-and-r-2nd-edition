#include <stdio.h>
#include <string.h>

void qsort(char *v[], int left, int right);
void writestrings(char *v[]);

int main(void) {
  char *test[] = {"ghi", "qrs", "abc", "lmn"};

  qsort(test, 0, 3);

  printf("result:\n");
  writestrings(test);
}

void qsort(char *v[], int left, int right) {
  printf("entering qsort() -- left: %d, right %d\n", left, right);
  writestrings(v);

  int i, last;
  i = 0;
  void swap(char *v[], int i, int j);

  if (left >= right) {
    printf("base case: left: %d, right %d\n", left, right);
    return;
  }

  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if (strcmp(v[i], v[left]) < 0) {
      // printf("%s is less than %s, will swap\n", v[i], v[left]);
      ++last;
      printf("left: %d, last: %d, i: %d\n", left, last, i);
      swap(v, last, i);
    }
  }
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
  if (i != j) {
    printf("will actually swap: i: %d, j: %d\n", i, j);
    writestrings(v);
  }
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;

  if (i != j) {
    printf("after the actual swap:\n");
    writestrings(v);
  }
}

void writestrings(char *v[]) {
  for (int i = 0; i < 4; i++) {
    printf("%s\n", v[i]);
  }
}
