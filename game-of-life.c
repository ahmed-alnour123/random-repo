#include <stdio.h>
#include <stdlib.h>

int **grid;
int lines;
int columns;

void print_grid() {
  for (int l = 0; l < lines; l++) {
    for (int c = 0; c < columns; c++) {
      putchar(grid[l][c]);
    }
  }
  putchar('\n');
}

int calc_nearby(int l, int c) {
  int counter = 0;
  for (int i = l - 1; i <= l + 1; i++) {
    for (int j = c - 1; j <= c + 1; j++) {
      if (i < 0 || i >= lines || j < 0 || j >= columns || (i == l && j == c))
        continue;
      counter += (grid[i][j] == '*');
    }
  }
  return counter;
}

void live() {
  int cache[lines][columns];

  for (int l = 0; l < lines; l++) {
    for (int c = 0; c < columns; c++) {
      switch (calc_nearby(l, c)) {
      case 0:
      case 1:
        // kill
        cache[l][c] = '.';
        break;
      case 2:
        // nothing
        cache[l][c] = grid[l][c];
        break;
      case 3:
        // live
        cache[l][c] = '*';
        break;
      default:
        // kill
        cache[l][c] = '.';
        break;
      }
    }
  }

  for (int l = 0; l < lines; l++) {
    for (int c = 0; c < columns; c++) {
      grid[l][c] = cache[l][c];
    }
  }
}

int main(int argc, char *argv[]) {
  lines = argc == 3 ? atoi(argv[1]) - 3 : 109;
  columns = argc == 3 ? atoi(argv[2]) : 26;
  printf("lines: %s, columns: %s\n", argv[1], argv[2]);
  grid = malloc(lines * sizeof(int *));

  if (grid == NULL) {
    puts("malloc fail exiting...");
    exit(1);
  }

  for (int l = 0; l < lines; l++) {
    grid[l] = malloc(columns * sizeof(int));
    if (grid[l] == NULL) {
      puts("malloc fail exiting...");
      exit(2);
    }
  }

  for (int l = 0; l < lines; l++) {
    for (int c = 0; c < columns; c++) {
      grid[l][c] = '.';
    }
  }

  // initial state
  grid[3][40] = '*';
  grid[4][40] = '*';
  grid[4][41] = '*';
  grid[5][40] = '*';
  /* grid[4][39] = '*'; */

  int n = 500;
start:
  print_grid();
  live();
  putchar('\n');
  if (n-- > 0) {
    if (getchar() != 'q')
      goto start;
  }
  return 0;
}
