
package com.inobulles.obiwac.aqua;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class View extends GLSurfaceView {
	public View(Context context) {
		super(context);

		setEGLConfigChooser(8, 8, 8, 0, 16, 0);
		setEGLContextClientVersion(2);
		setRenderer(new Renderer());

	}

	private static class Renderer implements GLSurfaceView.Renderer {
		public void onDrawFrame(GL10 gl) { Lib.step(); }
		public void onSurfaceChanged(GL10 gl, int width, int height) { Lib.resize(width, height); }
		public void onSurfaceCreated(GL10 gl, EGLConfig config) { Lib.init(MainActivity.assets); }

	}

}