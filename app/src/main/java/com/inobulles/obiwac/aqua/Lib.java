
package com.inobulles.obiwac.aqua;

import android.content.res.AssetManager;

public class Lib {
	static {
		System.loadLibrary("native-lib");

	}

	public static native void init(AssetManager asset_manager);
	public static native void resize(int width, int height);
	public static native void step();
	public static native void event(int pointer_index, int pointer_type, int x, int y, int quit, int release);

}