//
// Created by obiwac on 19.07.18.
//

#ifndef ANDROID_BMP_H
#define ANDROID_BMP_H

#include <stdint.h>
#include <string.h>
#include "../lib/structs.h"
#include "../../native-lib.h"
#include "../../asm/asm.h"

#pragma pack(push, 1)

typedef struct {
	uint16_t magic;
	uint32_t file_size;

	uint16_t reserved_1;
	uint16_t reserved_2;

	uint32_t offset;

} bitmap_header_t;

typedef struct {
	uint32_t size;

	int32_t width;
	int32_t height;

	uint16_t planes;
	uint16_t bpp;

	uint32_t compression_type;
	uint32_t image_bytes;

	int64_t pixels_per_meter_x;
	int64_t pixels_per_meter_y;

	uint32_t colour_count;
	uint32_t important_colours;

} bitmap_info_header_t;

#pragma pack(pop)

unsigned long long bmp_support(void) {
	return 1;

}

#define BMP_MAGIC 0x4D42
static const char* bmp_load_default_path = "test.bmp";

void bmp_load(unsigned long long ____this, unsigned long long _path) {
	bitmap_image_t* __this = (bitmap_image_t*) ____this;

	if (!(*((char*) _path))) {
		_path = (unsigned long long) bmp_load_default_path;
		printf("WARNING Empty path in %s (setting path to `%s`)\n", __func__, (char*) _path);

	}

	unsigned long long bytes;

	char* buffer;
	char* original;

	GET_PATH((char*) _path);

	if (load_asset_bytes(path, &buffer, &bytes)) {
		printf("WARNING Image file could not be opened (probably wrong path `%s`)\n", path);
		return;

	} else {
		original = buffer;

	}

	bitmap_header_t header;
	bitmap_info_header_t info_header;

	header = *((bitmap_header_t*) buffer);
	buffer += sizeof(bitmap_header_t);

	if (header.magic != BMP_MAGIC) {
		printf("WARNING File is not valid bitmap image\n");
		mfree(original, bytes);
		return;

	}

	info_header = *((bitmap_info_header_t*) buffer);

	__this->image_size = info_header.image_bytes / sizeof(unsigned long long);
	__this->bpp = (unsigned long long) info_header.bpp;

	__this->width  = (unsigned long long) info_header.width;
	__this->height = (unsigned long long) info_header.height;

	buffer  = original;
	buffer += header.offset;

	unsigned char*     char_data  = (unsigned char*) buffer;
	unsigned long long components = __this->bpp / 8;

	__this->data             = (unsigned long long*) malloc(info_header.image_bytes);
	unsigned long long pitch = (unsigned long long)  info_header.width * components;

	unsigned long long i;
	for (i = 0; i < info_header.image_bytes; i += components) {
		unsigned long long flipped_i = (__this->height - (i / (__this->width * components)) - 1) * pitch + ((i / components) %  __this->width) * components;

		if (__this->bpp == 32) {
			unsigned char a = char_data[i];
			unsigned char r = char_data[i + 1];
			unsigned char g = char_data[i + 2];
			unsigned char b = char_data[i + 3];

			((char*) __this->data)[flipped_i]     = b;
			((char*) __this->data)[flipped_i + 1] = g;
			((char*) __this->data)[flipped_i + 2] = r;
			((char*) __this->data)[flipped_i + 3] = a;

		} else {
			((char*) __this->data)[flipped_i]     = char_data[i + 2];
			((char*) __this->data)[flipped_i + 1] = char_data[i + 1];
			((char*) __this->data)[flipped_i + 2] = char_data[i];

		}

	}

	free(original);

}

void bmp_free(unsigned long long ____this) {
	bitmap_image_t* __this = (bitmap_image_t*) ____this;
	free(__this->data);

}

#endif
