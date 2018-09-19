//
// Created by obiwac on 22.07.18.
//

#ifndef ANDROID_FONT_H
#define ANDROID_FONT_H

font_t new_font(unsigned long long _path, unsigned long long size) {
	unsigned long long bytes;
	char* buffer;

	GET_PATH((const char*) _path);

	if (load_asset_bytes(path, &buffer, &bytes)) {
		ALOGE("WARNING Font file could not be opened (probably wrong path `%s`)\n", path);

	} else {
		free(buffer);

	}

	jint error = CALLBACK_INT(java_new_font, (jint) (((float) size / _UI64_MAX) * (float) video_width()), callback_env->NewStringUTF(path));

	if (error < 0) {
		ALOGE("WARNING Java had a problem loading the font\n");

	}

	return (font_t) error;

}

unsigned long long get_font_width( font_t font, unsigned long long text) { return (unsigned long long) CALLBACK_INT(java_get_font_width,  (jint) font, callback_env->NewStringUTF((const char*) text)); }
unsigned long long get_font_height(font_t font, unsigned long long text) { return (unsigned long long) CALLBACK_INT(java_get_font_height, (jint) font, callback_env->NewStringUTF((const char*) text)); }

void font_remove(font_t font) {
	CALLBACK_VOID(java_font_remove, font);

}

JNIEnv*    most_recent_text_env   = nullptr;
jbyteArray most_recent_byte_array = nullptr;

jbyte*  most_recent_text_bitmap       = nullptr;
jsize   most_recent_text_bitmap_bytes = 0;

unsigned long long most_recent_text_width;
unsigned long long most_recent_text_height;

texture_t most_recent_text_texture = 0;

texture_t create_texture_from_font(font_t font, unsigned long long text) {
	texture_t texture = 0;
	jint      error   = 1;

	unsigned long long width  = get_font_width (font, text);
	unsigned long long height = get_font_height(font, text);

	if (!(width <= 0 || height <= 0)) {
		most_recent_text_width  = width;
		most_recent_text_height = height;

		error = CALLBACK_INT(java_create_texture_from_font, (jint) font, callback_env->NewStringUTF((const char*) text));

	}

	if (error) {
		ALOGE("WARNING Java had a problem loading the font\n");

	} else {
		texture = most_recent_text_texture;
		//most_recent_text_env->ReleaseByteArrayElements(most_recent_byte_array, most_recent_text_bitmap, 0);

	}

	return texture;

}

#endif
