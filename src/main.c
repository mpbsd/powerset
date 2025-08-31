#include <stdio.h>
#include <stdlib.h>

#define N 5

int factorial(int);
int binomial(int, int);
int poweroftwo(int);
void allocate(int ****);
void setfree(int ****);
void initialize(int ***);
void elements(int ***, int, int);
void display(int ***);

int main(void) {
  int ***powerset = NULL;

  allocate(&powerset);
  initialize(powerset);
  display(powerset);
  setfree(&powerset);

  exit(EXIT_SUCCESS);
}

int factorial(int n) { /*{{{*/
  int f;
  for (f = 1; n > 0; --n) {
    f *= n;
  }
  return f;
} /*}}}*/

int binomial(int n, int p) { /*{{{*/
  return (n >= p) ? factorial(n) / (factorial(n - p) * factorial(p)) : 0;
} /*}}}*/

int poweroftwo(int n) { /*{{{*/
  int p;
  for (p = 1; n > 0; --n) {
    p *= 2;
  }
  return p;
} /*}}}*/

void allocate(int ****powerset) { /*{{{*/
  int i = 0;
  int j = 0;
  int p = 0;

  for (i = 0; i <= N; ++i) {
    p += sizeof(malloc(binomial(N, i) *
                       sizeof(malloc(((i == 0) ? 1 : i) * sizeof(int)))));
  }

  *powerset = malloc(p);

  for (i = 0; i <= N; ++i) {
    (*powerset)[i] = malloc(binomial(N, i) *
                            sizeof(malloc(((i == 0) ? 1 : i) * sizeof(int))));
    p = binomial(N, i);
    for (j = 0; j < p; ++j) {
      (*powerset)[i][j] = malloc(((i == 0) ? 1 : i) * sizeof(int));
    }
  }
} /*}}}*/

void setfree(int ****powerset) { /*{{{*/
  int i = 0;
  int j = 0;
  int b = 0;

  for (i = 0; i <= N; ++i) {
    b = binomial(N, i);
    for (j = 0; j < b; ++j) {
      free((*powerset)[i][j]);
    }
    free((*powerset)[i]);
  }

  free((*powerset));
} /*}}}*/

void initialize(int ***powerset) { /*{{{*/
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int m = 0;
  int p = 0;

  powerset[0][0][0] = '*';

  for (j = 0; j < N; ++j) {
    powerset[1][j][0] = j;
  }

  for (i = 2; i < N; ++i) {
    p = binomial(N, i - 1);
    j = 0;
    for (k = 0; k < p; ++k) {
      if (powerset[i - 1][k][i - 2] < N - 1) {
        for (l = powerset[i - 1][k][i - 2] + 1; l < N; ++l) {
          for (m = 0; m < i - 1; ++m) {
            powerset[i][j][m] = powerset[i - 1][k][m];
          }
          powerset[i][j++][i - 1] = l;
        }
      }
    }
  }

  for (i = 0; i < N; ++i) {
    powerset[N][0][i] = i;
  }
} /*}}}*/

void elements(int ***powerset, int i, int j) { /*{{{*/
  int k = 0;

  if (i == 0) {
    printf("{}");
  } else {
    for (k = 0; k < i; ++k) {
      printf("%s%d", (k == 0) ? "{" : ", ", powerset[i][j][k]);
    }
    printf("}");
  }
} /*}}}*/

void display(int ***powerset) { /*{{{*/
  int i = 0;
  int j = 0;
  int p = 0;

  printf("\n");

  for (i = 0; i <= N; ++i) {
    printf("%d: ", i);
    p = binomial(N, i);
    for (j = 0; j < p; ++j) {
      elements(powerset, i, j);
      printf("%s", (j < p - 1) ? ", " : "\n");
    }
  }

  printf("\n");
} /*}}}*/
