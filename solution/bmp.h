#ifndef BMP_PROCESSING_H
#define BMP_PROCESSING_H

#include <stdint.h>
#include <stdio.h>

typedef struct {                                                                
  uint8_t b, g, r;                                                            
} pixel;

typedef struct {
  uint64_t width, height;
  pixel* data;
} image;

typedef struct __attribute__((packed)){
  char file_type[2];
  uint32_t file_size;
  uint32_t reserved_zero;
  uint32_t img_data_offset;
  uint32_t header_size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bits_per_pixel;
  uint32_t compression;
  uint32_t img_size;
  uint32_t pix_per_meter_hor;
  uint32_t pix_per_meter_ver;
  uint32_t number_of_colors;
  uint32_t number_of_important_colors;
} bmp_header;


typedef enum {
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  READ_OUT_OF_MEMORY
} read_status;

read_status from_bmp(FILE* file, image* img);

typedef enum {
  WRITE_OK = 0,
  WRITE_ERROR
} write_status;

write_status to_bmp(FILE* file, image* img);

#endif