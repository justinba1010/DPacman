#ifndef __pacman_map__
#define __pacman_map__


typedef enum {
  W, G, o, O, e, E, u} tile;
const tile map[ROWS][COLS] = {
  //       Q         H         Q
  {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
  {W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
  {W,o,W,o,W,W,W,W,W,o,W,W,W,W,W,o,W,o,W},
  {W,o,o,o,o,o,o,o,W,o,W,o,o,o,o,o,o,o,W},
  {W,W,o,W,W,o,W,o,o,o,o,o,W,o,W,W,o,W,W},
  {W,W,o,W,W,o,W,o,o,o,o,o,W,o,W,W,o,W,W},
  {o,o,o,o,o,o,W,o,W,W,W,o,W,o,o,o,o,o,o},
  {W,W,o,W,W,o,W,o,W,G,W,o,W,o,W,W,o,W,W},
  {W,W,o,W,W,o,W,o,W,G,W,o,W,o,W,W,o,W,W},
  {W,o,o,o,o,o,W,o,o,o,o,o,W,o,o,o,o,o,W},
  {W,o,W,W,W,o,W,o,W,W,W,o,W,o,W,W,W,o,W},
  {W,o,o,o,o,o,o,o,W,W,W,o,o,o,o,o,o,o,W},
  {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
};

tile maze[ROWS][COLS];

tile player_allowed[] = {o, O, e, E};
int p_a = 4;
tile ghost_allowed[] = {o, O, e, E, G};
int g_a = 5;

void reset_map() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      maze[i][j] = map[i][j];
    }
  }
}

float random_sign() {
  return (float)((rand() & 2) - 1);
}

bool change_direction(Positional *p, float speedx, float speedy) {
  printf("%f\n", random_sign());
  if (p->vx != 0.) {
    p->vx = 0.;
    p->vy = random_sign() * speedy;
  } else {
    p->vx = random_sign() * speedx;
    p->vy = 0.;
  }
}

bool update_graph_coords(Positional *p) {
  int i = (int)(float)(p->x / WX);
  int j = (p->y / WY);

  if (i < 0 || i >= COLS) {
    i += COLS;
    i %= COLS;
    p->graphx = i;
    p->x = (i == 0) ? 0 : COLS * WX;
  }
  if (j < 0 || j >= COLS) {
    j += ROWS;
    j %= ROWS;
    p->graphy = j;
    p->y = (j == 0) ? 0 : ROWS * WY;
  }

  printf("%d, %d\n", i, j);

  if (p->graphx != i || p->graphy != j) {
    printf("Changed\n");
    p->graphx = i;
    p->graphy = j;
    return true;
  }
  return false;
}

void draw_map(void) {
  for (int i = 0; i < COLS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      float x = i * WX;
      float y = j * WY;
      switch(maze[j][i]) {
        case W:
          draw_rect(
              x, y,
              x + WX, y + WY,
              0., 0., 1., 1.
              );
          break;
        case o:
          draw_circ(x + WX/2., y + WY/2., 1.5, 1.0, 1.0, 1.0, 1.0);
          break;
        case O:
          draw_circ(x + WX/2., y + WY/2., 2.5, 1.0, 1.0, 1.0, 1.0);
        default:
          break;
      }
    }
  }
}

bool legal(int x, int y, tile *t, int s) {
  if (x >= COLS || x < 0 || y >= ROWS || y < 0) {
    return  false;
  }
  for (int i = 0; i < s; ++i) {
    if (maze[y][x] == t[i]) {
      return true;
    }
  }
  return false;
}

bool update_pos(Positional *p, float diff, tile* t, int s) {
  // Updates position if it is a legal movement
  // Returns true if could not move
  float ox, oy;
  ox = p->x;
  oy = p->y;
  p->x += p->vx * diff;
  p->y += p->vy * diff;
  if (update_graph_coords(p)) {
    if (p->graphx < 0 || p->graphy < 0 || p->graphx >= COLS || p->graphy >= ROWS) {
      return true;
    }
    if (legal(p->graphx, p->graphy, t, s)) {
      return false;
    }
  } else {
    return false;
  }

  p->x = ox;
  p->y = oy;
  update_graph_coords(p);
  return true;
}



#endif
