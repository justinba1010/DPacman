#ifndef __pacman_s2help__
#define __pacman_s2help__
#define SECTORS 10

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

#endif
