/*
 * Reid Bixler
 * rmb3yz
 * CS 2150 Post-Lab 9 linkedlist.c
 * November 21 ,2014
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int i;
  int *p;
  int x = 0;
  printf("Enter how many values to input: ");
  scanf("%d", &i);

  p = (int *) malloc(sizeof (int) * i);
  
  for (int j=1; j<=i; ++j){
    printf("Enter value ");
    printf("%d", j);
    printf(": ");
    scanf("%d", &x) ;
    p[j-1] = x;
  }

   for (int k=1; k<=i; ++k){
     int l = i - k;
     printf("%d\n", p[l]);
  }

  free(p);

  return 0;
}
