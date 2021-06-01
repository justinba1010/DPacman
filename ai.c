#ifndef __pacman_ai__
#define __pacman_ai__

#include <stdlib.h>
#include <map.c>
#define STACK_SIZE 256

typedef enum {R, L, U, D} direction;

direction stack[STACK_SIZE];
int stack_index = 0;
bool visited[ROWS][COLS];

void reset(void) {
  stack_index = 0;
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      visited[i][j] == false;
    }
  }
}

direction blinky(Positional *blinky, Positional *pacman) {
  reset();
  return dfs(blinky->graphx, blinky->graphy, pacman->graphx, pacman->graphy, ghost_allowed, g_a);
}

direction dfs(int x, int y, int x_t, int y_t, tile *t, int s) {
  if (x_t == x && y_t == y) {
    return stack[0];
  }
  // Right
  if (!visited[y][x+1] && legal(x + 1, y, t, s)) {
    visited[y][x+1] = true;
    stack[stack_index++] = R;
    return dfs(x+1, y, x_t, y_t);
  }
  stack_index--;
  // Left
  if (!visited[y][x-1] && legal(x - 1, y, t, s)) {
    visited[y][x-1] = true;
    stack[stack_index++] = L;
    return dfs(x-1, y, x_t, y_t);
  }
  stack_index--;
  // Down
  if (!visited[y + 1][x] && legal(x, y + 1, t, s)) {
    visited[y+1][x] = true;
    stack[stack_index++] = D;
    return dfs(x, y+1, x_t, y_t);
  }
  stack_index--;
  // Up
  if (!visited[y][x] && legal(x, y - 1, t, s)) {
    visited[y - 1][x] = true;
    stack[stack_index++] = R;
  }
  stack_index--;
}
#endif
