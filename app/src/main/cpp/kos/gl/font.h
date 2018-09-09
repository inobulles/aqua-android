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

texture_t create_texture_from_font(font_t font, unsigned long long text) {
	jbyte*    bytes   = NULL;
	texture_t texture = 0;

	jbyteArray error;
	jint       length;

	unsigned long long width  = get_font_width( font, text);
	unsigned long long height = get_font_height(font, text);

	if (width <= 0 || height <= 0) {
		error = NULL;

	} else {
		error  = (jbyteArray) CALLBACK(java_create_texture_from_font, callback_env->CallStaticObjectMethod, (jint) font, callback_env->NewStringUTF((const char*) text));
		bytes  = callback_env->GetByteArrayElements(error, 0);
		length = callback_env->GetArrayLength(error);
		callback_env->GetByteArrayRegion(error, 0, length, bytes);

	}

	if (error == NULL) {
		ALOGE("WARNING Java had a problem loading the font\n");

	}

	if (bytes != NULL) {
		texture = __texture_create((unsigned long long*) bytes, 32, width, height, (unsigned long long) false);
		callback_env->ReleaseByteArrayElements(error, bytes, 0);

	}

	return texture;

}

#endif
