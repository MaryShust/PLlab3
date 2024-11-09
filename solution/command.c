#include "command.h"
#include <stdint.h>
#include <stdlib.h>

image none(image source) {
    image result;
    result.width = source.width;
    result.height = source.height;
    result.data = malloc(result.width * result.height * sizeof(pixel));
    for (size_t i = 0; i < source.height; ++i) {
        for (size_t j = 0; j < source.width; ++j) {
            result.data[j + i * source.width] = source.data[j + i * source.width];
        }
    }
    return result;
}

image cw90(image source) {
    image result;
    result.width = source.height;
    result.height = source.width;
    result.data = malloc(result.width * result.height * sizeof(pixel));
    for (size_t i = 0; i < source.height; ++i) {
        for (size_t j = 0; j < source.width; ++j) {
            result.data[j * result.width + i] = source.data[i * source.width + (source.width - j - 1)];
        }
    }
    return result;
}

image ccw90(image source) {
    image result;
    result.width = source.height;
    result.height = source.width;
    result.data = malloc(result.width * result.height * sizeof(pixel));
    for (size_t i = 0; i < source.height; ++i) {
        for (size_t j = 0; j < source.width; ++j) {
            result.data[j * result.width + (result.width - i - 1)] = source.data[i * source.width + j];
        }
    }
    return result;
}

image fliph(image source) {
    image result;
    result.width = source.width;
    result.height = source.height;
    result.data = malloc(result.width * result.height * sizeof(pixel));
    for (size_t i = 0; i < ((result.height + 1) / 2); ++i) {
        for (size_t j = 0; j < result.width; ++j) {
            size_t top_index = i * result.width + j;
            size_t bottom_index = (result.height - i - 1) * result.width + j;
            pixel temp = source.data[top_index];
            result.data[top_index] = source.data[bottom_index];
            result.data[bottom_index] = temp;
        }
    }
    return result;
}


image flipv(image source) {
    image result;
    result.width = source.width;
    result.height = source.height;
    result.data = malloc(result.width * result.height * sizeof(pixel));
    for (size_t i = 0; i < result.height; ++i) {
        for (size_t j = 0; j < ((result.width + 1) / 2); ++j) {
            size_t left_index = i * result.width + j;
            size_t right_index = i * result.width + (result.width - j - 1);
            pixel temp = source.data[left_index];
            result.data[left_index] = source.data[right_index];
            result.data[right_index] = temp;
        }
    }
    return result;
}

