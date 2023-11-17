#include "utils.h"

void scale_image(ALLEGRO_BITMAP *image, float x, float y, float resize)
{
    al_draw_scaled_bitmap(image, 0, 0,
                          al_get_bitmap_width(image),
                          al_get_bitmap_height(image),
                          x, y,
                          al_get_bitmap_width(image) * resize,
                          al_get_bitmap_height(image) * resize, 0); // desenha nave vermelha
}
