#ifndef BMP_PROCESSING_H
#define BMP_PROCESSING_H

#include "transform.h"
#include <stdio.h>

enum bmp_read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS = 12,
    READ_INVALID_HEADER
};

enum bmp_write_status {
    WRITE_OK = 0,
    WRITE_ERROR
};

#pragma pack(push, 1)
struct bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bfOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

extern enum bmp_read_status from_bmp(FILE* in, struct image* img);
extern enum bmp_write_status to_bmp(FILE* out, struct image const* img);

#endif
