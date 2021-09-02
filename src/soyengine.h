#ifndef SOY_ENGINE_H
#define SOY_ENGINE_H

#include "soycore.h"
#include "soywin.h"
#include "soycanvas.h"
#include "soyfont.h"
#include "soydraw.h"
#include "soystring.h"
#include "soy3D.h"
#include "soytime.h"

typedef struct tag_appMemory {
	void* data;
	unsigned int size;
} appMemory;

typedef struct tag_soyApp {
  const char* name;
  flag running;
  flag clearBuffer;
  soyWindow window;
  soyCanvas canvas;
  soyCamera mainCamera;
  drawParams drawProps;
  pfUserFuncDelta userUpdate;
  pfUserFunc userInit;
  pfUserFunc userFree;
  appMemory memory;
  double deltaTime;
} soyApp;

soyApp* global_appPtr;

flag soy_app_allocate_virtual_memory(soyApp* app, unsigned int megabytes) {
  app->memory.data = soy_alloc(app->memory.data, Megabytes(megabytes));
  return TRUE;
}

flag soy_app_free_virtual_memory(soyApp* app) {
  soy_free(app->memory.data);
  return TRUE;
}

#define SOY_ENGINE_IMPLEMENTATION
#ifdef SOY_ENGINE_IMPLEMENTATION

/* TODO: input interface */

/* drawing interface */

flag draw_clear() {
  soy_draw_clear(&global_appPtr->drawProps);
  return TRUE;
}

flag draw_pixel(int x, int y) {
  soy_draw_pixel(&global_appPtr->drawProps, x, y);
  return TRUE;
}

flag draw_line(float x1, float y1, float x2, float y2) {  
  /* soy_draw_line(&global_appPtr->drawProps, x1, y1, x2, y2); */
  soy_draw_line_dds(&global_appPtr->drawProps, x1, y1, x2, y2);
  return TRUE;
}

flag draw_rect(int x1, int y1, int x2, int y2) {
 soy_draw_rect(&global_appPtr->drawProps,
      x1, y1, x2, y2);
  return TRUE;
}

flag draw_rect_fill(int x1, int y1, int x2, int y2) {
  soy_draw_rect_fill(&global_appPtr->drawProps, x1, y1, x2, y2);
  return TRUE;
}

flag draw_ellipse(int x, int y, int w, int h) {
 soy_draw_ellipse(&global_appPtr->drawProps,
      x, y, w, h);
  return TRUE;
}

flag draw_set_colour_pixel(soyPixel pixel) {
  soy_draw_set_colour(&global_appPtr->drawProps, pixel.r, pixel.g, pixel.b, pixel.a);
  return TRUE;
}

flag draw_set_colour(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  soy_draw_set_colour(&global_appPtr->drawProps, r, g, b, a);
  return TRUE;
}

flag draw_text(int x, int y, float scale, const char* text) {
  soy_font_set_scale(&global_appPtr->drawProps.font, scale);
  soy_draw_text(&global_appPtr->drawProps,
      x, y, text, soy_cstring_len(text, 2048), &global_appPtr->drawProps.font);
  return TRUE;
}

/* 3d interface */
flag create_model(soyModel* model, const char* filename, const char* name) {
  soy_3d_create_model(model, filename, name);
  return TRUE;
}

flag scale_projection_to_view(vec4* dest) {
    dest->x += 1.0f;
    dest->y += 1.0f;
    dest->x *= (float)global_appPtr->canvas.width*0.5f;
    dest->y *= (float)global_appPtr->canvas.height*0.5f;
  return TRUE;
}

flag draw_triangle_textured(int x1, int y1, float u1, float v1, float w1,
                            int x2, int y2, float u2, float v2, float w2,
                            int x3, int y3, float u3, float v3, float w3, soyBitmap* texture) {
  soy_draw_triangle_textured(&global_appPtr->drawProps,
      x1, y1, u1, v1, w1,
      x2, y2, u2, v2, w2,
      x3, y3, u3, v3, w3, texture);
  return TRUE;
}

flag draw_soy_triangle_textured(soyTri* tri, soyBitmap* texture) {
  soy_draw_triangle_textured(&global_appPtr->drawProps,
      tri->v1.points.x, tri->v1.points.y, tri->v1.UVs.u, tri->v1.UVs.v, tri->v1.UVs.w,
      tri->v2.points.x, tri->v2.points.y, tri->v2.UVs.u, tri->v2.UVs.v, tri->v2.UVs.w,
      tri->v3.points.x, tri->v3.points.y, tri->v3.UVs.u, tri->v3.UVs.v, tri->v3.UVs.w, texture);
  return TRUE;
}

flag draw_bitmap(int x, int y, int width, int height, soyBitmap* bitmap) {
  soy_draw_bitmap32(&global_appPtr->drawProps, x, y, (soyPixel*)bitmap->bytes, bitmap->width, bitmap->height, width, height);
  return TRUE;
}

flag draw_model(soyModel* model, soyCamera* cam, soyTransform* t, soyBitmap* texture, float depthBuffer[]) {
  int i;
  int l;
 
  soyTri triOrig;
  soyTri triWorld;
  soyTri triProj;
  vec4 normal, line1, line2;
  vec4 vCam; 
  vec4 vCamRay;
  mat4 worldMatrix;
  mat4 projectionMatrix; 
  vec4 vSun;
  soyMesh* meshHandle = &model->mesh;
  soyPixel newCol;
  soyTri curTri;
  soyTri* finalTris = NULL;
  int finalTriCount = 0;
  float sunDP = 0.0f;
  vCam.x = 0.0f; 
  vCam.y = 0.0f; 
  vCam.z = 0.0f; 
  vCam.w = 1.0f; 
  
  vSun.x = 0.0f;
  vSun.y = 1.0f;
  vSun.z = 0.0f;
  vSun.w = 1.0f;

  soy_3d_compute_world_matrix(t, &worldMatrix); 
  soy_3d_mat4_projection(&projectionMatrix, cam->nearClip, cam->farClip, cam->fieldOfView, cam->aspectRatio);
  
  finalTris = soy_alloc(finalTris, sizeof(soyTri)*model->mesh.triCount);
  for(i = 0; i < model->mesh.triCount; i++) { 
    triOrig = meshHandle->triangles[i];

    triWorld = triOrig;
    soy_3d_mat4_tri_multiply(&triWorld, &triOrig, &worldMatrix);
 
    soy_3d_vec4_subtract(&line1, &triWorld.v2.points, &triWorld.v1.points); 
    soy_3d_vec4_subtract(&line2, &triWorld.v3.points, &triWorld.v1.points); 
 
    soy_3d_vec4_cross_product(&normal, &line1, &line2);
    soy_3d_vec4_normalize(&normal, &normal); 
    soy_3d_vec4_subtract(&vCamRay, &triWorld.v1.points, &vCam); 

    if(soy_3d_vec4_dot_product(&normal, &vCamRay) < 0.0f) {
      
      /* TODO: lighting calculation */
      sunDP = soy_3d_vec4_dot_product(&normal, &vSun);
      sunDP+= 2.0f;
      sunDP /= 3.3f;
      if(sunDP > 1.0f) {sunDP = 1.0f;}
      if(sunDP < 0.0f) {sunDP = 0.0f;}
      newCol = global_appPtr->drawProps.colour;
      newCol.r *= sunDP;
      newCol.g *= sunDP;
      newCol.b *= sunDP;
      newCol.a = 255;
      
      /* projecting from world/view to projection space */
      triProj = triWorld;
      soy_3d_mat4_tri_multiply(&triProj, &triWorld, &projectionMatrix);
      
      /* correct the texture coordinates */
      triProj.v1.UVs.u = triProj.v1.UVs.u / triProj.v1.points.w;
      triProj.v2.UVs.u = triProj.v2.UVs.u / triProj.v2.points.w;
      triProj.v3.UVs.u = triProj.v3.UVs.u / triProj.v3.points.w;

      triProj.v1.UVs.v = triProj.v1.UVs.v / triProj.v1.points.w;
      triProj.v2.UVs.v = triProj.v2.UVs.v / triProj.v2.points.w;
      triProj.v3.UVs.v = triProj.v3.UVs.v / triProj.v3.points.w;

      triProj.v1.UVs.w = 1.0f / triProj.v1.points.w;
      triProj.v2.UVs.w = 1.0f / triProj.v2.points.w;
      triProj.v3.UVs.w = 1.0f / triProj.v3.points.w;

      triProj.v1.colour = newCol;
      triProj.v2.colour = newCol;
      triProj.v3.colour = newCol;
      
      /* normalize the projected vertices */
      soy_3d_vec4_divide_scalar(&triProj.v1.points, &triProj.v1.points, triProj.v1.points.w);
      soy_3d_vec4_divide_scalar(&triProj.v2.points, &triProj.v2.points, triProj.v2.points.w);
      soy_3d_vec4_divide_scalar(&triProj.v3.points, &triProj.v3.points, triProj.v3.points.w);

      /* scale them into view */
      soy_3d_scale_projection(&triProj, cam->width, cam->height); 
      
      finalTris[finalTriCount] = triProj;
      finalTriCount++;
    }
  }

  for(l = 0; l < finalTriCount; l++ ) {
      curTri = finalTris[l];
      
      draw_set_colour(curTri.v1.colour.r, curTri.v1.colour.g, curTri.v1.colour.b, 255);
      if(texture == NULL) {
 
      draw_line(
          curTri.v1.points.x,curTri.v1.points.y,curTri.v2.points.x,curTri.v2.points.y);
      draw_line(
          curTri.v2.points.x,curTri.v2.points.y,curTri.v3.points.x,curTri.v3.points.y);
      draw_line(
          curTri.v3.points.x,curTri.v3.points.y,curTri.v1.points.x,curTri.v1.points.y);
      
      } else {
        draw_soy_triangle_textured(&curTri, texture);
      }
      /*
      draw_set_colour(0,0,0,255);
            
      draw_line(
          curTri.v1.points.x,curTri.v1.points.y,curTri.v2.points.x,curTri.v2.points.y);
      draw_line(
          curTri.v2.points.x,curTri.v2.points.y,curTri.v3.points.x,curTri.v3.points.y);
      draw_line(
          curTri.v3.points.x,curTri.v3.points.y,curTri.v1.points.x,curTri.v1.points.y);
      */
  }
  
  soy_free(finalTris);
  return TRUE;
}

soyTransform soy_transform(float x, float y, float z) {
  soyTransform trans;
  trans.position.x = x;
  trans.position.y = y;
  trans.position.z = z;
  trans.rotation.x = 0;
  trans.rotation.y = 0;
  trans.rotation.z = 0;
  trans.scale.x = 1;
  trans.scale.y = 1;
  trans.scale.z = 1;
  return trans;
}

flag transform_move(soyTransform* t, float x, float y, float z) {
  t->position.x = x;
  t->position.y = y;
  t->position.z = z;
  return TRUE;
}

flag transform_rotate(soyTransform* t, float x, float y, float z) {
  t->rotation.x = x;
  t->rotation.y = y;
  t->rotation.z = z;
  return TRUE;
}

flag transform_scale(soyTransform* t, float x, float y, float z) {
  t->scale.x = x;
  t->scale.y = y;
  t->scale.z = z;
  return TRUE;
}

flag free_model(soyModel* model) {
  soy_3d_free_model(model);
  return TRUE;
}

/* drawing presets */
flag draw_frame(soyApp* app) {
    char deltaText[64];
	draw_set_colour(10, 15, 20, 255);
	draw_rect_fill(0,0, app->canvas.width-1, SOY_DEFAULT_TITLEBAR_SIZE);
	
    draw_set_colour(20, 30, 40, 255);
	draw_rect(0,0, app->canvas.width-1, SOY_DEFAULT_TITLEBAR_SIZE);
	draw_rect(0, 0, app->canvas.width-1, app->canvas.height-1);
	
	draw_set_colour(255,255,255,255);
	draw_text(5, 5, 1, app->name);
	
    sprintf(deltaText, "dt: %.3f", app->deltaTime);
    draw_set_colour(255, 255, 0, 255);
    draw_text(8, 24, 1, deltaText);
	return TRUE;
}


/* TODO: fx interface */

flag create_bitmap(soyBitmap* bitmap, const char* filename) {
  if(filename == NULL) { return FALSE; }
  soy_bitmap_create(bitmap, filename);
  return TRUE;
}

flag free_bitmap(soyBitmap* bitmap) {
  soy_bitmap_free(bitmap);
  return TRUE;
}

/* TODO: gui interface */
/* TODO: sound interface */
/* TODO: file interface */
/* TODO: entity interface */
/* TODO: math interface */

#else
#error must #define SOY_ENGINE_IMPLEMENTATION in order to access high level [soy engine] functions!
#endif

/* TODO: main engine interface */

flag draw_param_func(int param) {
  soyWindow* win = &global_appPtr->window;
  soyCanvas* can = &global_appPtr->canvas;
  Sleep(param);
  soy_window_blit_pixels(win, can->memory, can->width, can->height, can->pixelSize);
  return TRUE;
}

flag user_functions(soyApp* app, pfUserFunc initFunc, pfUserFuncDelta updateFunc, pfUserFunc freeFunc) {
  app->userInit = initFunc;
  app->userUpdate = updateFunc;
  app->userFree = freeFunc;
  return TRUE;
}


flag stop_application(soyApp* app) {
  app->running = FALSE;
  return TRUE;
}

flag quit_application() {
  soy_window_quit();
  return TRUE;
}

flag default_update_func(double delta) {
  Sleep(100);
  return TRUE;
}

flag default_init_func() {
  Sleep(100);
  return TRUE;
}

flag default_free_func() {
  Sleep(100);
  return TRUE;
}

flag open_application(soyApp* app, int width, int height, int resolution, const char* title) {
  double delta = 0;
  double secTimer = 0;
  double usrTimer = 0;
  double timestep = 1000.0/60.0;
  int resX = 0;
  int resY = 0;
  int prevW = 0;
  int prevH = 0;
  int realFrames = 0;
  int userFrames = 0;
  soyCanvas* canvas;
  soyWindow* window;
  soyBitmap fontAtlas;
  soyFont font;
 
  soyTimer timerAll, timerFrame;
  resX = soy_window_desktop_res_x();
  resY = soy_window_desktop_res_y();
  if(app == NULL) {
    return ERROR;
  }
  ENDL;
  SLOG1("-< Soy Engine App [%s] START >-\n\n", title);
 
  canvas = &app->canvas;
  window = &app->window;
    
  soy_time_init(&timerFrame);
  soy_time_init(&timerAll);
  soy_time_start(&timerFrame);
  soy_time_start(&timerAll);
  soy_window_create(&app->window, WIN32_NATIVE, width, height, resX/2-width/2, resY/2-height/2, title);
  soy_canvas_create(&app->canvas, width, height, resolution);
  soy_bitmap_create(&fontAtlas, "Assets/Fonts/SOYFONT1.bmp");
  soy_font_set_atlas(&font, &fontAtlas, 16);
  soy_font_set_kerning(&font, 5);
  soy_3d_camera_init(&app->mainCamera, canvas->width, canvas->height);
 
  prevW = width;
  prevH = height;
  app->running = TRUE;
  app->clearBuffer = TRUE;
  app->name = title;
  app->deltaTime = 0;
  app->drawProps.memory = canvas->memory;
  app->drawProps.memWidth = canvas->width;
  app->drawProps.memHeight = canvas->height;
  app->drawProps.colour = soy_pixel(0, 0, 0, 255);
  app->drawProps.drawCb = draw_param_func;
  app->drawProps.font = font;
  global_appPtr = app;
  
  if(app->userUpdate == NULL) { 
    app->userUpdate = default_update_func;
  }
  if(app->userInit == NULL) { 
    app->userInit = default_init_func;
    app->userFree = default_free_func;
    app->userUpdate = default_update_func;
  }
  if(app->userFree == NULL) { 
    app->userInit = default_init_func;
    app->userInit = default_free_func;
    app->userInit = default_update_func;
  }
  ENDL;
  SLOG("~ User Initialization ~\n\n");
  app->userInit(0);
  ENDL;
  SLOG("~ End User Initialization ~\n\n");

  soy_time_end(&timerFrame);
  SLOG1("-< Initialized in %f miliseconds. Starting main loop... >-\n\n", soy_time_delta(&timerFrame));
  while(app->running) {
    soy_time_start(&timerFrame);
    soy_window_poll_events(window);
    
    delta = soy_time_delta(&timerFrame);
    app->deltaTime = delta;
    secTimer += delta;
    usrTimer += delta;
 
    if(prevW != window->width || prevH != window->height) {
      soy_canvas_resize(&app->canvas, window->width, window->height, resolution);
    }
    prevW = window->width;
    prevH = window->height;
    app->drawProps.memory = canvas->memory;
    app->drawProps.memWidth = canvas->width;
    app->drawProps.memHeight = canvas->height;
  
    if(usrTimer > timestep) {
      if(app->clearBuffer) { soy_draw_clear(&app->drawProps); }
      app->userUpdate(timestep);
      draw_frame(app);
      soy_window_blit_pixels(window, canvas->memory, canvas->width, canvas->height, resolution);
      userFrames++;
      usrTimer = 0.0;
    }
   
    if(secTimer > 1000.0) {
      SLOG2("-< Frames (engine): %d | Frames (user): %d >-\n", realFrames, userFrames);
      realFrames = 0;
      userFrames = 0;
      secTimer = 0.0;
    }

    realFrames++;
    soy_time_end(&timerFrame);
  }
  
  ENDL;
  SLOG("~ User Free ~\n\n");
  app->userFree(0);
  ENDL;
  SLOG("~ End User Free ~\n\n");

  soy_canvas_free(&app->canvas);
  soy_window_close(&app->window);
  soy_bitmap_free(&fontAtlas);
  soy_time_end(&timerAll);
  ENDL;
  SLOG1("-< Soy Engine App [%s] END >-\n", title);
  SLOG1("-< Seconds of runtime: %f >-\n\n", soy_time_delta(&timerAll)/1000.0f);
  return TRUE;
}

#endif
