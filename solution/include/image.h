#ifndef IMAGE_HEADER
#define IMAGE_HEADER

#include <stdint.h>

struct pixel { uint8_t b, g, r; };

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct image create_image(uint64_t width, uint64_t height);
void destroy_image(struct image* img);

uint8_t calc_image_padding(uint64_t width, uint8_t pixel_size);

#endif
