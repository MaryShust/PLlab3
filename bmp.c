#include "bmp.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bmp_header* read_bmp_header(FILE* file) {
  bmp_header* header = malloc(sizeof(bmp_header));
  fread(header, sizeof(*header), 1, file);
  return header;
}

read_status from_bmp(FILE* file, image* img) {
    bmp_header* header = read_bmp_header(file);
    if (header == NULL) {
        return READ_INVALID_HEADER;
    }
    if (header->file_type[0]!= 'B' || header->file_type[1]!= 'M') {
        free(header);
        return READ_INVALID_SIGNATURE;
    }
    if (header->bits_per_pixel!= 24) {
        free(header);
        return READ_INVALID_BITS;
    }
    img->width = header->width;
    img->height = header->height;
    img->data = calloc(img->width * img->height, sizeof(pixel));
    if (fseek(file, header->img_data_offset, SEEK_SET)!= 0) {
        free(header);
        free(img->data);
        return READ_INVALID_SIGNATURE;
    }
    size_t row_size = img->width * sizeof(pixel);
    size_t padding = (4 - (row_size % 4)) % 4;
    for (size_t i = 0; i < img->height; ++i) {
        if (fread(img->data + i * img->width, sizeof(pixel), img->width, file)!= img->width) {
            free(header);
            free(img->data);
            return READ_INVALID_BITS;
        }
        if (fseek(file, (long)padding, SEEK_CUR) != 0) {
            free(header);
            free(img->data);
            return READ_INVALID_BITS;
        }
    }
    free(header);
    return READ_OK;
}

bmp_header* createBmpHeader(image* img) {
  bmp_header* header = (bmp_header*)malloc(sizeof(bmp_header));

  header->file_type[0] = 'B';
  header->file_type[1] = 'M';
  header->reserved_zero = 0;
  header->img_data_offset = sizeof(bmp_header);
  header->header_size = header->img_data_offset - 14;
  header->width = img->width;
  header->height = img->height;
  header->planes = 1;
  header->bits_per_pixel = 24;
  header->compression = 0;
  header->img_size = img->height * img->width * sizeof(pixel) 
    + img->height * (img->width % 4);
  header->pix_per_meter_hor = 2835;
  header->pix_per_meter_ver = 2835;
  header->number_of_colors = 0;
  header->number_of_important_colors = 0;
  header->file_size = header->img_data_offset + header->img_size;

  return header;
}

write_status to_bmp(FILE* file, image* img) {
  bmp_header* header = createBmpHeader(img);
  if (fwrite(header, sizeof(bmp_header), 1, file) != 1) {
    free(header);
    return WRITE_ERROR;
  }
  
  uint64_t num_bytes = img->width * img->height * sizeof(pixel);

  uint64_t pad = img->width % 4;
  if (pad == 0) {
    if (fwrite(img->data, num_bytes, 1, file) != 1) {
      free(header);
      return WRITE_ERROR;
    }
  }
  else {
    uint64_t data_size = img->width * img->height * sizeof(pixel) + img->height * pad;
    uint8_t* data = (uint8_t*)calloc(1, data_size);
    uint64_t h, w, cur_pad, cur_pix;
    for (h = 0; h < img->height; h++) {
      cur_pad = h * pad;
      for (w = 0; w < img->width; w++) {
        cur_pix = h * img->width + w;
        *((pixel*) (data + sizeof(pixel) * cur_pix + cur_pad)) = img->data[cur_pix];
      }
    }
    fwrite(data, data_size, 1, file);
    free(data);
  }
  fflush(file);
  return WRITE_OK;
}










