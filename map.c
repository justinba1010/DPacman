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

void reset_map() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      maze[i][j] = map[i][j];
    }
  }
}

bool update_graph_coords(Positional *p) {
  printf("WX: %f, WY: %f\n", WX, WY);
  printf("p->x: %f\n", p->x);
  printf("ahh: %f\n", p->x / WX);
  int i = (int)(float)(p->x / WX);
  int j = (p->y / WY);

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

bool update_pos(Positional *p, float diff, tile* t, int s) {
  // Updates position if it is a legal movement
  // Returns true if could not move
  float ox, oy;
  ox = p->x;
  oy = p->y;
  p->x += p->vx * diff;
  p->y += p->vy * diff;
  if (update_graph_coords(p)) {
    for (int i = 0; i < s; ++i) {
      if (maze[p->graphx][p->graphy] == t[i]) {
        printf("legal move\n");
        return false;
      }
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
