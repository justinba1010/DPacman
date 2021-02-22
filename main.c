#include <simple2d.h>
#include <time.h>

S2D_Window *window;

#define WIDTH 310
#define HEIGHT 280
#define W_W 10
#define W_V 10
#define SECTORS 10
#define SPEED 25.
#define GSPEED 22.

typedef struct {
  float x;
  float y;
  float vx;
  float vy;
  int lives;
  bool chasing;
  int food_collected;
} Pacman;


void on_key(S2D_Event e);
void random_direction(float *x, float *y);
/* Tile
 * w: wall
 * G: ghost pen gate
 * P: Portal
 * p: empty path
 * o: pill
 * e: eaten pill
 * O: big pill
 * E: eaten big pill
 */ 

typedef enum {W, G, P, u, o, e, O, E} tile;

tile maze[28][31] = { 
  {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W},
  {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
  {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
  {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
  {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
  {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,W,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
  {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,W,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
  {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,u,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
  {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,W,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
  {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,W,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
  {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,W,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
  {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
  {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
  {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
  {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
  {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
  {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W}
};

struct timespec currtime, ghosttime;
int lastvalidx, lastvalidy;
Pacman pacman;

typedef struct {
  float x;
  float y;
  float lastvalidx;
  float lastvalidy;
  float vx;
  float vy;
  float r;
  float g;
  float b;
} Ghost;

Ghost ghosts[4];

void draw_rect(float x, float y, float x1, float y1, float r, float g, float b, float a) {
  float diffx = x1 - x;
  float diffy = y1 - y;
  S2D_DrawQuad(
      x, y,
      r, g, b, a,
      x + diffx, y,
      r, g, b, a,
      x + diffx, y + diffy,
      r, g, b, a,
      x, y + diffy,
      r, g, b, a);
}

void draw_circ(float x, float y, float rad, float r, float g, float b, float a) {
  S2D_DrawCircle(x, y, rad, SECTORS, r, g, b, a);
}

void map(void) {
  float x,y;
  for (int j = 0; j < 31; ++j) {
    for (int i = 0; i < 28; ++i) {
      int x = i * W_W;
      int y = j * W_V;
      switch (maze[i][j]) {
        case W:
          draw_rect(x, y, x+W_W, y + W_V, 0.0, 0.0, 0.75, 1.);
          break;
        case o:
          draw_circ(x + W_W/2., y + W_V/2., 1., 1.0, 1.0, 1.0, 1.0);
          break;
        case O:
          draw_circ(x + W_W/2, y +W_V/2., 2.5, 1.0, 1.0, 1.0, 1.0);
          break;
        case G:
          break;
        case P:
          break;
      }
    }
  }
}


void blinky(void) {
  struct timespec xt;
  timespec_get(&xt, TIME_UTC);
  float diff = difftime(xt.tv_sec, ghosttime.tv_sec);
  diff += 1e-9*(xt.tv_nsec - ghosttime.tv_nsec);
  int px = round(pacman.x/W_W) * W_W;
  int py = round(pacman.y/W_V) * W_V;
  timespec_get(&ghosttime, TIME_UTC);
  for (int i = 0; i < 4; ++i) {
    ghosts[i].x += diff * ghosts[i].vx;
    ghosts[i].y += diff * ghosts[i].vy;
    int x = round(ghosts[i].x/W_W) * W_W;
    int y = round(ghosts[i].y/W_V) * W_V;
    if (px == x && py == y) {
      // TODO Collision
    }
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
      int h = x / W_W;
      int j = y / W_V;
      switch (maze[h][j]) {
        case W:
          ghosts[i].x = ghosts[i].lastvalidx;
          ghosts[i].y = ghosts[i].lastvalidy;
          random_direction(&ghosts[i].vx, &ghosts[i].vy);
          break;
        case P:
          ghosts[i].x = ghosts[i].lastvalidx;
          ghosts[i].y = ghosts[i].lastvalidy;
          break;
        default:
          ghosts[i].lastvalidx = ghosts[i].x;
          ghosts[i].lastvalidy = ghosts[i].y;
          break;
      }
    } else {
      random_direction(&ghosts[i].vx, &ghosts[i].vy);
      ghosts[i].x = ghosts[i].lastvalidx;
      ghosts[u].y = ghosts[i].lastvalidy;
    }
    draw_circ(x + W_W/2., y + W_V/2., 4.0, ghosts[i].r, ghosts[i].g, ghosts[i].b, 1.);
  }
}

void player(void) {
  struct timespec xt;
  timespec_get(&xt, TIME_UTC);
  float diff = difftime(xt.tv_sec, currtime.tv_sec);
  diff += 1e-9*(xt.tv_nsec - currtime.tv_nsec);

  float newx, newy;
  timespec_get(&currtime, TIME_UTC);
  pacman.x += diff * pacman.vx;
  pacman.y += diff * pacman.vy;
  float x = round(pacman.x/W_W)*W_W;
  float y = round(pacman.y/W_V)*W_V;

  int x_ = (int) x;
  int y_ = (int) y;

  if (x_ >= 0 && x_ < WIDTH && y_ >= 0 && y_ < HEIGHT) {
    int i = x / W_W;
    int j = y / W_V;
    switch (maze[i][j]) {
      case W:
        pacman.x = lastvalidx;
        pacman.y = lastvalidy;
        pacman.vx = 0.;
        pacman.vy = 0.;
        break;
      case o:
        lastvalidx = pacman.x;
        lastvalidy = pacman.y;
        maze[i][j] = 'e';
        break;
      case O:
        lastvalidx = pacman.x;
        lastvalidy = pacman.y;
        maze[i][j] = 'E';
        break;
      case P:
        pacman.x = pacman.x > 140 ? 10: 260;
        break;
      default:
        lastvalidx = pacman.x;
        lastvalidy = pacman.y;

    }
  } else {
    pacman.x = lastvalidx;
    pacman.y = lastvalidy;
    pacman.vx = 0.;
    pacman.vy = 0.;
  }
  x = round(pacman.x/W_W)*W_W;
  y = round(pacman.y/W_V)*W_V;
  x_ = (int) x;
  y_ = (int) y;
  draw_circ(x + W_W/2., y + W_V/2., 4., 1., 1., 0., 1.);
}

void player_update(void) {
}

void render(void) {
  map();
  player();
  blinky();
}

void update(void) {
  player_update();
}

void random_direction(float *x, float *y) {
  printf("%d\n", rand() % 4);
  switch (rand() % 4) {
    case 0:
      *x = GSPEED;
      *y = 0.;
      break;
    case 1:
      *x = -GSPEED;
      *y = 0.;
      break;
    case 2:
      *x = 0.;
      *y = GSPEED;
      break;
    case 3:
      *x = 0.;
      *y = -GSPEED;
      break;
  }
}

void load_ghosts(void) {
  float startx = WIDTH/2. - 20;
  float starty = HEIGHT/2. + 20;
  for (int i = 0; i < 4; ++i) {
    ghosts[i].r = 0.;
    ghosts[i].g = 0.;
    ghosts[i].b = 0.;
    ghosts[i].lastvalidx = startx;
    ghosts[i].lastvalidy = starty;
    random_direction(&ghosts[i].vx, &ghosts[i].vy);
  }
  ghosts[0].x = WIDTH/2. - 20;
  ghosts[0].y = HEIGHT/2. + 20;
  ghosts[1].x = WIDTH/2. - 20;
  ghosts[1].y = HEIGHT/2. + 20;
  ghosts[2].x = WIDTH/2. - 20;
  ghosts[2].y = HEIGHT/2. + 20;
  ghosts[3].x = WIDTH/2. - 20;
  ghosts[3].y = HEIGHT/2. + 20;
  ghosts[0].r = 1.;
  ghosts[1].g = 1.;
  ghosts[2].r = 0.8;
  ghosts[2].b = 0.3;
  ghosts[3].r = 0.7;
  ghosts[3].b = 1.;
}

int main(void) {
  load_ghosts();
  srand(time(NULL));
  pacman.x = 5;
  pacman.y = 5;
  timespec_get(&currtime, TIME_UTC);
  timespec_get(&ghosttime, TIME_UTC);
  window = S2D_CreateWindow("Pacman", HEIGHT, WIDTH, update, render, S2D_RESIZABLE);
  window->icon = "";
  window->on_key = on_key;
  S2D_Show(window);
  S2D_FreeWindow(window);
  return 0;
}


void on_key(S2D_Event e) {
  switch (e.type) {
    case S2D_KEY_DOWN:
      if (strcmp(e.key, "Up") == 0) {
        pacman.vx = 0.;
        pacman.vy = -SPEED;
      }
      if (strcmp(e.key, "Down") == 0) {
        pacman.vx = 0.;
        pacman.vy = SPEED;
      }
      if (strcmp(e.key, "Right") == 0) {
        pacman.vx = SPEED;
        pacman.vy = 0.;
      }
      if (strcmp(e.key, "Left") == 0) {
        pacman.vx = -SPEED;
        pacman.vy = 0.;
      }
  }
}
