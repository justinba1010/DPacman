/*
 */
#include <stdlib.h>
#include <simple2d.h>
#include <time.h>
#include "structs.c"
#include "defines.h"
#include "s2help.c"
#include "map.c"

S2D_Window *window;

Game game;
struct timespec currtime;

void update(void);
void render(void);
void load_ghosts(void);
void load_player(void);
void on_key(S2D_Event);
void draw_pacman(void);

int main(void) {
  load_player();
  load_ghosts();
  reset_map();
  srand(time(NULL));
  timespec_get(&currtime, TIME_UTC);
  window = S2D_CreateWindow("Pacman", WIDTH, HEIGHT, update, render, S2D_RESIZABLE);
  window->on_key = on_key;
  S2D_Show(window);
  S2D_FreeWindow(window);
  return 0;
}

void update(void) {
  long int tv_sec = currtime.tv_sec;
  long int tv_nsec = currtime.tv_nsec;
  timespec_get(&currtime, TIME_UTC);
  float diff = currtime.tv_sec - tv_sec;
  diff += 1e-9 * (currtime.tv_nsec - tv_nsec);
  // Player
  tile player_allowed[] = {o, O, e, E};
  if (update_pos(&(game.p), diff, player_allowed, 4)) {
  }
}
void render(void) {
  draw_map();
  draw_pacman();
}
void load_ghosts(void) {
}
void load_player(void) {
  game.p.x = 1.1 * WX;
  game.p.y = 1.1 * WY;
  update_graph_coords(&(game.p));
}
void on_key(S2D_Event e) {
  switch (e.type) {
    case S2D_KEY_DOWN:
    if (strcmp(e.key, "Up") == 0) {
      game.p.vx = 0.;
      game.p.vy = -SPEEDY;
    }
    if (strcmp(e.key, "DOWN") == 0) {
      game.p.vx = 0.;
      game.p.vy = SPEEDY;
    }
    if (strcmp(e.key, "Right") == 0) {
      game.p.vx = SPEEDX;
      game.p.vy = 0;
    }
    if (strcmp(e.key, "Left") == 0) {
      game.p.vx = -SPEEDX;
      game.p.vy = 0;
    }
  }
}
void draw_pacman(void) {
  float x = game.p.graphx*WX + WX/2.;
  float y = game.p.graphy*WY + WX/2.;
  draw_circ(x, y, PACSIZE, 1., 1., 0., 1.);
}

