#ifndef __pacman_structs__
#define __pacman_structs__

typedef struct {
  float x;
  float y;
  float vx;
  float vy;
  int graphx;
  int graphy;
} Positional;

typedef struct {
  Positional p;
  void (*navigate)(Positional*);
} Ghost;

typedef struct {
  Positional p;
  int lives;
  bool chasing;
  int food_collected;
  Ghost ghosts[4];
} Game;

#endif

