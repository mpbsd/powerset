#include <stdio.h>
#include <stdlib.h>

#define N 4

int factorial(int);
int binomial(int, int);
int poweroftwo(int);
void allocate(int ****);
void initialize(int ***);
void display(int ***);

int main(void) {
  int ***powerset = NULL;

  allocate(&powerset);

  initialize(powerset);

  display(powerset);

  free(powerset);

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
    (*powerset)[i] = malloc(binomial(N, i) * sizeof(malloc(i * sizeof(int))));
    p = binomial(N, i);
    for (j = 0; j < p; ++j) {
      (*powerset)[i][j] = malloc(i * sizeof(int));
    }
  }
} /*}}}*/

void initialize(int ***powerset) { /*{{{*/
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int m = 0;
  int p = 0;

  powerset[0][0][0] = '*';

  for (i = 1; i < N; ++i) {
    if (i == 1) {
      for (j = 0; j < N; ++j) {
        powerset[1][j][0] = j;
      }
    } else {
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
  }

  for (i = 0; i < N; ++i) {
    powerset[N][0][i] = i;
  }
} /*}}}*/

void display(int ***powerset) { /*{{{*/
  int i = 0;
  int j = 0;
  int k = 0;
  int p = 0;

  printf("\n0: *\n");

  for (i = 1; i <= N; ++i) {
    printf("%d: ", i);
    p = binomial(N, i);
    for (j = 0; j < p; ++j) {
      if (i == 1) {
        printf("{%d}", powerset[i][j][0]);
      } else {
        for (k = 0; k < i; ++k) {
          if (k == 0) {
            printf("{%d", powerset[i][j][k]);
          } else if (k == i - 1) {
            printf(", %d}", powerset[i][j][k]);
          } else {
            printf(", %d", powerset[i][j][k]);
          }
        }
      }
      printf("%s", (j < p - 1) ? ", " : "\n");
    }
  }

} /*}}}*/
