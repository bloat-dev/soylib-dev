#ifndef SOY_3D_H
#define SOY_3D_H

#include "soycore.h"
#include "soyfile.h"

typedef struct tag_texCoord {
  float u;
  float v;
  float w;
} texCoord;

typedef struct tag_vec3 {
  float x;
  float y;
  float z;
} vec3;

typedef struct tag_vec4 {
  float x;
  float y;
  float z;
  float w;
} vec4;

typedef struct tag_vec2i {
  int x;
  int y;
} vec2i;

typedef struct tag_vec3i {
  int x;
  int y;
  int z;
} vec3i;

typedef struct tag_vec4i {
  int x;
  int y;
  int z;
  int w;
} vec4i;

typedef struct tag_mat2 {
  float m[2][2];
} mat2;

typedef struct tag_mat3 {
  float m[3][3];
} mat3;

typedef struct tag_mat4 {
  float m[4][4];
} mat4;

typedef struct tag_soyVert {
  vec4 points;
  vec4 normals;
  texCoord UVs;
  soyPixel colour;
} soyVert;

typedef struct tag_soyIndices {
  vec3i vertIndices;
  vec3i uvIndices;
  vec3i normalIndices;
} soyIndices;

typedef struct tag_soyTri {
  soyVert v1;
  soyVert v2;
  soyVert v3;
} soyTri;

typedef struct tag_soyTransform {
  vec3 position;
  vec3 rotation;
  vec3 scale;
} soyTransform;

typedef enum enum_triFormat {
  V,
  VT,
  VTN,
  VN
} triFormat;

typedef struct tag_soyMesh {
  soyTri* triangles;
  int triCount;
  triFormat triForm;
  flag initialized;
  const char* name;
} soyMesh;

typedef struct tag_soyModel {
  soyMesh mesh;
  int ID;
  int fileSize;
  const char* filename;
  flag alive;
} soyModel;

typedef struct tag_soyCamera {
  vec3 position;
  vec3 rotation;
  mat4 mat;
  int width;
  int height;
  float fieldOfView;
  float aspectRatio;
  float nearClip;
  float farClip;
} soyCamera;

typedef struct tag_triArray {
  soyTri* tris;
  int size;
  int count;
} triArray;

vec4i soy_3d_vec4_to_vec4i(vec4* v, int perc) {
  vec4i res;
  res.x = v->x*perc;
  res.y = v->y*perc;
  res.z = v->z*perc;
  res.w = v->w*perc;
  return res;
}

vec4 soy_3d_vec4i_to_vec4(vec4i* v,int perc) {
  vec4 res;
  res.x = v->x>>perc;
  res.y = v->y>>perc;
  res.z = v->z>>perc;
  res.w = v->w>>perc;
  return res;
}

soyTri null_tri();

flag tri_array_create(triArray* a) {
  a->tris = NULL;
  a->tris = soy_alloc(a->tris, sizeof(soyTri)*3);
  if (a->tris == NULL) {
      SLOG("Problem creating tri array\n");
      return FALSE;
  }
  a->tris[0] = null_tri();
  a->tris[1] = null_tri();
  a->tris[2] = null_tri();
  a->size = 3;
  a->count = 0;
  return TRUE;
}

flag tri_array_push_back(triArray* a, soyTri tri) {
  int d;
  int i;
  soyTri* pPrev;
  soyTri* pNew;
  if(a->count+1 > a->size) {
    pPrev = a->tris;
    pNew = realloc(a->tris, sizeof(soyTri)*a->count*2);
    if(a->tris == NULL) {
      a->tris = pPrev;
      return ERROR;
    }
    a->tris = pNew;
    a->size = a->count*2;
    d = a->size - a->count;
    for(i = a->count; i < a->count+d; i++) {
      a->tris[i] = null_tri();
    }
  }
  a->count++;
  a->tris[a->count-1] = tri;
  return TRUE;
}

flag tri_array_pop_back(triArray* a) {
  if(a->count == 0) {
    SLOG("Array empty\n");
    return ERROR;
  }
  a->tris[a->count-1] = null_tri();
  a->count--;
  return TRUE;
}

flag tri_array_pop_front(triArray* a) {
  int i = 0;
  if(a->count == 0) {
    SLOG("Array empty\n");
    return ERROR;
  }
  for(i = 0; i < a->count-1; i++) {
    a->tris[i] = a->tris[i+1];
  }
  a->tris[a->count-1] = null_tri();
  a->count--;
  return TRUE;
}

flag tri_array_free(triArray* a) {
  soy_free(a->tris);
  a->tris = NULL;
  a->count = 0;
  a->size = 0;
  return TRUE;
}

texCoord soy_3d_uv(float u, float v, float w) {
  texCoord res;
  res.u = u;
  res.v = v;
  res.w = w;
  return res;
}

vec3 soy_3d_vec3(float x, float y, float z) {
  vec3 res;
  res.x = x;
  res.y = y;
  res.z = z;
  return res;
}

vec4 soy_3d_vec4(float x, float y, float z, float w) {
  vec4 res;
  res.x = x;
  res.y = y;
  res.z = z;
  res.w = w;
  return res;
}

vec4i soy_3d_vec4i(int x, int y, int z, int w) {
  vec4i res;
  res.x = x;
  res.y = y;
  res.z = z;
  res.w = w;
  return res;
}

soyTri null_tri() {
  soyTri tri;
  tri.v1.colour = soy_pixel(0,0,0,255);
  tri.v1.points = soy_3d_vec4(0.0f, 0.0f, 0.0f, 0.0f);
  tri.v2.points = soy_3d_vec4(0.0f, 0.0f, 0.0f, 0.0f);
  tri.v3.points = soy_3d_vec4(0.0f, 0.0f, 0.0f, 0.0f);
  tri.v1.UVs = soy_3d_uv(0.0f, 0.0f, 0.0f);
  tri.v2.UVs = soy_3d_uv(0.0f, 0.0f, 0.0f);
  tri.v3.UVs = soy_3d_uv(0.0f, 0.0f, 0.0f);
  tri.v1.normals = soy_3d_vec4(0.0f, 0.0f, 0.0f, 0.0f);
  tri.v2.normals = soy_3d_vec4(0.0f, 0.0f, 0.0f, 0.0f);
  tri.v3.normals = soy_3d_vec4(0.0f, 0.0f, 0.0f, 0.0f);
  return tri;
}

flag soy_3d_vec4_add(vec4* res, vec4* v1, vec4* v2) {
  res->x = v1->x + v2->x;
  res->y = v1->y + v2->y;
  res->z = v1->z + v2->z;
  return TRUE;
}

flag soy_3d_vec4_subtract(vec4* res, vec4* v1, vec4* v2) {
  res->x = v1->x - v2->x;
  res->y = v1->y - v2->y;
  res->z = v1->z - v2->z;
  return TRUE;
}

flag soy_3d_vec4_multiply(vec4* res, vec4* v1, vec4* v2) {
  res->x = v1->x * v2->x;
  res->y = v1->y * v2->y;
  res->z = v1->z * v2->z;
  return TRUE;
}

flag soy_3d_vec4_multiply_scalar(vec4* res, vec4* v, float scalar) {
  res->x = v->x * scalar;
  res->y = v->y * scalar;
  res->z = v->z * scalar;
  return TRUE;
}

flag soy_3d_vec4_divide(vec4* res, vec4* v1, vec4* v2) {
  res->x = v1->x / v2->x;
  res->y = v1->y / v2->y;
  res->z = v1->z / v2->z;
  return TRUE;
}

flag soy_3d_vec4_divide_scalar(vec4* res, vec4* v1, float scalar) {
  if(scalar != 0) {
    res->x = v1->x / scalar;
    res->y = v1->y / scalar;
    res->z = v1->z / scalar;
  }
  return TRUE;
}

flag soy_3d_vec4_cross_product(vec4* res, vec4* v1, vec4* v2) {
  res->x = v1->y * v2->z - v1->z * v2->y;
  res->y = v1->z * v2->x - v1->x * v2->z;
  res->z = v1->x * v2->y - v1->y * v2->x;
  return TRUE;
}

flag soy_3d_vec4_invert(vec4* res, vec4* v) {
  res->x = v->x*-1.0f;
  res->y = v->y*-1.0f;
  res->z = v->z*-1.0f;
  return TRUE;
}

float soy_3d_vec4_dot_product(vec4* v1, vec4* v2) {
  return (v1->x*v2->x+v1->y*v2->y+v1->z*v2->z);
}

float soy_3d_vec4_length(vec4* v) {
  return sqrt(soy_3d_vec4_dot_product(v, v));
}

flag soy_3d_vec4_normalize(vec4* res, vec4* v) {
  float len = soy_3d_vec4_length(v);
  res->x = v->x / len;
  res->y = v->y / len;
  res->z = v->z / len;
  return TRUE;
}

flag soy_3d_mat4_identity(mat4* m) {
  m->m[0][0] = 1.0f; m->m[0][1] = 0.0f; m->m[0][2] = 0.0f; m->m[0][3] = 0.0f;
  m->m[1][0] = 0.0f; m->m[1][1] = 1.0f; m->m[1][2] = 0.0f; m->m[1][3] = 0.0f;
  m->m[2][0] = 0.0f; m->m[2][1] = 0.0f; m->m[2][2] = 1.0f; m->m[2][3] = 0.0f;
  m->m[3][0] = 0.0f; m->m[3][1] = 0.0f; m->m[3][2] = 0.0f; m->m[3][3] = 1.0f;
  return TRUE;
}

flag soy_3d_mat4_zero(mat4* m) {
  m->m[0][0] = 0.0f; m->m[0][1] = 0.0f; m->m[0][2] = 0.0f; m->m[0][3] = 0.0f;
  m->m[1][0] = 0.0f; m->m[1][1] = 0.0f; m->m[1][2] = 0.0f; m->m[1][3] = 0.0f;
  m->m[2][0] = 0.0f; m->m[2][1] = 0.0f; m->m[2][2] = 0.0f; m->m[2][3] = 0.0f;
  m->m[3][0] = 0.0f; m->m[3][1] = 0.0f; m->m[3][2] = 0.0f; m->m[3][3] = 0.0f;
  return TRUE;
}

flag soy_3d_mat4_vec4_multiply(vec4* res, vec4* i, mat4* m) {
  res->x = i->x*m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
  res->y = i->x*m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
  res->z = i->x*m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
  res->w = i->x*m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];
  return TRUE;
}

flag soy_3d_mat4_vec4_multiply_n(vec4* res, vec4* i, mat4* m) {
  res->x = i->x*m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
  res->y = i->x*m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
  res->z = i->x*m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
  res->w = i->x*m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];
  if(res->w!=0.0f) {
    res->x /= res->w;
    res->y /= res->w;
    res->z /= res->w;
  }
  return TRUE;
}

flag soy_3d_mat4_multiply(mat4* res, mat4* m1, mat4* m2) {
  int i;
  int j;
  soy_3d_mat4_identity(res);
  for(i = 0; i < 4; i++) {
    for(j = 0; j < 4; j++) {
      res->m[j][i] =
        m1->m[j][0] * m2->m[0][i] +
        m1->m[j][1] * m2->m[1][i] +
        m1->m[j][2] * m2->m[2][i] +
        m1->m[j][3] * m2->m[3][i];
    }
  }
  return TRUE;
}

flag soy_3d_mat4_tri_multiply(soyTri* dest, soyTri* orig, mat4* mat) {
  soy_3d_mat4_vec4_multiply(&dest->v1.points, &orig->v1.points, mat);
  soy_3d_mat4_vec4_multiply(&dest->v2.points, &orig->v2.points, mat);
  soy_3d_mat4_vec4_multiply(&dest->v3.points, &orig->v3.points, mat);
  return TRUE;
}

flag soy_3d_mat4_projection(mat4* m, float n, float f, float fov, float aspect) {
  float fNear = 0.1f;
  float fFar = 1000.0f;
  float fFov = 45.0f;
  float fAspectRatio = 1.0f;
  float fFovRad;;
  if(n != 0) {fNear = n;}
  if(f != 0) {fFar = f;}
  if(fov != 0) {fFov = fov;}
  if(aspect != 0) {fAspectRatio = aspect;}
  fFovRad = 1.0f / tan(fFov*0.5f / 180.0f * SOY_PI);
  soy_3d_mat4_zero(m);
  m->m[0][0] = fAspectRatio * fFovRad;
  m->m[1][1] = fFovRad;
  m->m[2][2] = fFar / (fFar - fNear);
  m->m[3][2] = (-fFar * fNear) / (fFar - fNear);
  m->m[2][3] = 1.0f;
  m->m[3][3] = 0.0f;
  return TRUE;
}

flag soy_3d_mat4_translation(mat4* m, float x, float y, float z) {
  soy_3d_mat4_identity(m);
  m->m[3][0] = x;
  m->m[3][1] = y;
  m->m[3][2] = z;
  m->m[3][3] = 1.0f;
  return TRUE;
}

flag soy_3d_mat4_scale(mat4* m, float x, float y, float z) {
  soy_3d_mat4_identity(m);
  m->m[0][0] = x;
  m->m[1][1] = y;
  m->m[2][2] = z;
  m->m[3][3] = 1.0f;
  return TRUE;
}

flag soy_3d_mat4_rotation(mat4* m, float angle, float x, float y, float z) {
  mat4 rotX, rotY, rotZ, temp;
  soy_3d_mat4_identity(m);
  soy_3d_mat4_identity(&rotX);
  soy_3d_mat4_identity(&rotY);
  soy_3d_mat4_identity(&rotZ);
  /* x-axis */
  rotX.m[0][0] = 1.0f;
  rotX.m[1][1] = cos(angle*x);
  rotX.m[1][2] = sin(angle*x);
  rotX.m[2][1] = -sin(angle*x);
  rotX.m[2][2] = cos(angle*x);
  rotX.m[3][3] = 1.0f;

  /* y-axis */
  rotY.m[0][0] = cos(angle*y);
  rotY.m[0][2] = -sin(angle*y);
  rotY.m[2][0] = sin(angle*y);
  rotY.m[1][1] = 1.0f;
  rotY.m[2][2] = cos(angle*y);
  rotY.m[3][3] = 1.0f;

  /* z-axis */
  rotZ.m[0][0] = cos(angle*z);
  rotZ.m[0][1] = -sin(angle*z);
  rotZ.m[1][0] = sin(angle*z);
  rotZ.m[1][1] = cos(angle*z);
  rotZ.m[2][2] = 1.0f;
  rotZ.m[3][3] = 1.0f;

  soy_3d_mat4_multiply(&temp, &rotX, &rotY);
  soy_3d_mat4_multiply(m, &temp, &rotZ);
  return TRUE;
}

flag soy_3d_mat4_point_at(mat4* mat, vec4* pos, vec4* target, vec4* up) {
		vec4 newForward;
        vec4 a, newUp, newRight;
        float dp;
        mat4 matrix;

        soy_3d_vec4_subtract(&newForward, target, pos);
		soy_3d_vec4_normalize(&newForward, &newForward);
        dp = soy_3d_vec4_dot_product(up, &newForward);
		soy_3d_vec4_multiply_scalar(&a, &newForward, dp);
		soy_3d_vec4_subtract(&newUp, up, &a);
		soy_3d_vec4_normalize(&newUp, &newUp);

		soy_3d_vec4_cross_product(&newRight, &newUp, &newForward);

		matrix.m[0][0] = newRight.x;
        matrix.m[0][1] = newRight.y;
        matrix.m[0][2] = newRight.z;
        matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = newUp.x;
        matrix.m[1][1] = newUp.y;
        matrix.m[1][2] = newUp.z;
        matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = newForward.x;
        matrix.m[2][1] = newForward.y;
        matrix.m[2][2] = newForward.z;
        matrix.m[2][3] = 0.0f;
		matrix.m[3][0] = pos->x;
        matrix.m[3][1] = pos->y;
        matrix.m[3][2] = pos->z;
        matrix.m[3][3] = 1.0f;
        *mat = matrix;
		return TRUE;
	}

flag soy_3d_mat4_quick_inverse(mat4* m) {
		mat4 matrix;
		matrix.m[0][0] = m->m[0][0];
        matrix.m[0][1] = m->m[1][0];
        matrix.m[0][2] = m->m[2][0];
        matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = m->m[0][1];
        matrix.m[1][1] = m->m[1][1];
        matrix.m[1][2] = m->m[2][1];
        matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = m->m[0][2];
        matrix.m[2][1] = m->m[1][2];
        matrix.m[2][2] = m->m[2][2];
        matrix.m[2][3] = 0.0f;
		matrix.m[3][0] =
          -(m->m[3][0] * matrix.m[0][0] + m->m[3][1] * matrix.m[1][0] + m->m[3][2] * matrix.m[2][0]);
		matrix.m[3][1] =
          -(m->m[3][0] * matrix.m[0][1] + m->m[3][1] * matrix.m[1][1] + m->m[3][2] * matrix.m[2][1]);
		matrix.m[3][2] =
          -(m->m[3][0] * matrix.m[0][2] + m->m[3][1] * matrix.m[1][2] + m->m[3][2] * matrix.m[2][2]);
		matrix.m[3][3] = 1.0f;
        *m = matrix;
		return TRUE;
}

flag soy_3d_compute_world_matrix(soyTransform* t, mat4* world) {
  mat4 scale;
  mat4 rot;
  mat4 trans;
  mat4 temp;
  soy_3d_mat4_scale(&scale, t->scale.x, t->scale.y, t->scale.z);
  soy_3d_mat4_rotation(&rot, SOY_2PI, t->rotation.x, t->rotation.y, t->rotation.z);
  soy_3d_mat4_translation(&trans, t->position.x, t->position.y, t->position.z);
  soy_3d_mat4_identity(world);

  soy_3d_mat4_multiply(&temp, &scale, &rot);
  soy_3d_mat4_multiply(world, &temp, &trans);
  return TRUE;
}

flag soy_3d_scale_projection_to_view(vec4* dest, int width, int height) {
  dest->x += 1.0f;
  dest->y += 1.0f;
  dest->x *= (float)width*0.5f;
  dest->y *= (float)height*0.5f;
  return TRUE;
}

flag soy_3d_scale_projection(soyTri* dest, int width, int height) {
  soy_3d_scale_projection_to_view(&dest->v1.points, width, height);
  soy_3d_scale_projection_to_view(&dest->v2.points, width, height);
  soy_3d_scale_projection_to_view(&dest->v3.points, width, height);
  return TRUE;
}

flag soy_3d_camera_init(soyCamera* camera, int width, int height) {
  camera->nearClip = 0.1f;
  camera->farClip = 1000.0f;
  camera->fieldOfView = 45.0f;
  camera->width = width;
  camera->height = height;
  camera->aspectRatio = (float)height/(float)width;
  camera->position = soy_3d_vec3(0,0,0);
  camera->rotation = soy_3d_vec3(0,0,0);
  soy_3d_mat4_projection(&camera->mat,
      camera->nearClip, camera->farClip, camera->fieldOfView, camera->aspectRatio);
  return TRUE;
}

flag soy_3d_free_soyMesh(soyMesh* m) {
  if(m->initialized) {
    soy_free(m->triangles);
    m->triangles = NULL;
    m->triCount = 0;
  } else {
    SLOG("Mesh to be freed isn't initialized\n");
    return ERROR;
  }
  return TRUE;
}

flag soy_3d_export_sem(soyMesh* mesh, const char* filename) {
  FILE* file = NULL;
  int i = 0;
  file = fopen(filename, "w");
  if(file == NULL) {
    SLOG1("Could not open file %s for writing\n", filename);
    return ERROR;
  }
  SLOG1("Exporting asset: %s\n", filename);
  fprintf(file, "form SEM\n");
  fprintf(file, "name %s\n", mesh->name);
  fprintf(file, "type %d\n", mesh->triForm);
  fprintf(file, "tris %d\n", mesh->triCount);

  for(i = 0; i < mesh->triCount; i++) {
    fprintf(file, "vert %f %f %f ",
        mesh->triangles[i].v1.points.x,
        mesh->triangles[i].v1.points.y,
        mesh->triangles[i].v1.points.z);
    fprintf(file, "%f %f %f ",
        mesh->triangles[i].v2.points.x,
        mesh->triangles[i].v2.points.y,
        mesh->triangles[i].v2.points.z);
    fprintf(file, "%f %f %f\n",
        mesh->triangles[i].v3.points.x,
        mesh->triangles[i].v3.points.y,
        mesh->triangles[i].v3.points.z);
    if(mesh->triForm == VT || mesh->triForm == VTN) {
      fprintf(file, "uv %f %f ",
          mesh->triangles[i].v1.UVs.u,
         mesh->triangles[i].v1.UVs.v);
      fprintf(file, "%f %f ",
          mesh->triangles[i].v2.UVs.u,
         mesh->triangles[i].v2.UVs.v);
      fprintf(file, "%f %f\n",
         mesh->triangles[i].v3.UVs.u,
         mesh->triangles[i].v3.UVs.v);
    }
    if(mesh->triForm == VN || mesh->triForm == VTN) {
      fprintf(file, "norm %f %f %f ",
         mesh->triangles[i].v1.normals.x,
         mesh->triangles[i].v1.normals.y,
         mesh->triangles[i].v1.normals.z);
      fprintf(file, "%f %f %f ",
         mesh->triangles[i].v2.normals.x,
         mesh->triangles[i].v2.normals.y,
         mesh->triangles[i].v2.normals.z);
      fprintf(file, "%f %f %f\n",
         mesh->triangles[i].v3.normals.x,
         mesh->triangles[i].v3.normals.y,
         mesh->triangles[i].v3.normals.z);
    }
  }
  fclose(file);
  return TRUE;
}

flag soy_3d_import_sem(soyMesh* mesh, const char* filename) {
  FILE* file = NULL;
  int i, j, k;
  int res = 0;
  int triCount = 0;
  int formatInt = 0;
  triFormat order = 0;
  char linePrefix[5];
  soyTri curTri;
  soyTri* tempTris = NULL;
  flag allocated = FALSE;
  i = 0;
  j = 0;
  k = 0;
  SLOG1("Importing asset: %s\n", filename);
  file = fopen(filename, "r");
  if(file == NULL) {
    SLOG1("Could not open file %s for reading\n", filename);
    return ERROR;
  }
  while(TRUE) {
    res = fscanf(file, "%s", linePrefix);
    if(res == EOF) {
      break;
    }

    if(strcmp(linePrefix, "vert") == 0) {
      if(allocated == FALSE && triCount > 0) {
        tempTris = soy_alloc(tempTris, sizeof(soyTri)*triCount);
        if(tempTris == NULL) {
          SLOG("Could not allocate temporary triangle buffer\n");
          return ERROR;
        }
        allocated = TRUE;
      }
      res = fscanf(file, "%f %f %f %f %f %f %f %f %f\n",
          &curTri.v1.points.x, &curTri.v1.points.y, &curTri.v1.points.z,
          &curTri.v2.points.x, &curTri.v2.points.y, &curTri.v2.points.z,
          &curTri.v3.points.x, &curTri.v3.points.y, &curTri.v3.points.z);
      if(allocated) {
        tempTris[i] = curTri;
        i++;
      }
    } else if(strcmp(linePrefix, "uv") == 0) {
      res = fscanf(file, "%f %f %f %f %f %f\n",
          &curTri.v1.UVs.u, &curTri.v1.UVs.v,
          &curTri.v2.UVs.u, &curTri.v2.UVs.v,
          &curTri.v3.UVs.u, &curTri.v3.UVs.v);
      if(allocated) {
        tempTris[j] = curTri;
        j++;
      }
    } else if (strcmp(linePrefix, "norm") == 0) {
      res = fscanf(file, "%f %f %f %f %f %f %f %f %f\n",
          &curTri.v1.points.x, &curTri.v1.points.y, &curTri.v1.points.z,
          &curTri.v2.points.x, &curTri.v2.points.y, &curTri.v2.points.z,
          &curTri.v3.points.x, &curTri.v3.points.y, &curTri.v3.points.z);
      if(allocated) {
        tempTris[k] = curTri;
        k++;
      }

    } else if(strcmp(linePrefix, "type") == 0) {
      res = fscanf(file, "%d\n", &formatInt);
      switch(formatInt) {
        case(0): order = V; break;
        case(1): order = VT; break;
        case(2): order = VTN; break;
        case(3): order = VN; break;
        default: order = V; break;
      }
    } else if(strcmp(linePrefix, "tris") == 0) {
      res = fscanf(file, "%d\n", &triCount);
    }
  }
  if(mesh->initialized) {
    soy_3d_free_soyMesh(mesh);
    mesh->initialized = FALSE;
  }
  mesh->triForm = order;
  mesh->triangles = tempTris;
  mesh->triCount = triCount;
  mesh->initialized = TRUE;
  fclose(file);
  return TRUE;
}

flag soy_3d_import_obj(soyMesh* destMesh, const char* filename) {
  FILE* file = NULL;
  char lineHeader[512];
  int res;
  int vertCount = 0;
  int uvCount = 0;
  int normalCount = 0;
  int triCount = 0;
  int index = 0;

  vec4* tempVerts = NULL;
  texCoord* tempUVs = NULL;
  vec4* tempNormals = NULL;
  soyIndices* tempIndices = NULL;
  soyTri* tempTris = NULL;

  destMesh->initialized = FALSE;

  file = fopen(filename, "r");

  if(file == NULL) {
    SLOG1("Couldn't find file %s\n", filename);
    return ERROR;
  }

  while(TRUE) {
    res = fscanf(file, "%s", lineHeader);
    if(res == EOF) {
      break;
    }
    if(strcmp(lineHeader, "v") == 0) {
      vertCount++;
    } else if(strcmp(lineHeader, "vt") == 0) {
      uvCount++;
    } else if(strcmp(lineHeader, "vn") == 0) {
      normalCount++;
    } else if(strcmp(lineHeader, "f") == 0) {
      triCount++;
    }
  }
  rewind(file);
  destMesh->triCount = triCount;
  tempVerts = soy_alloc(tempVerts, sizeof(vec4)*vertCount);
  tempIndices = soy_alloc(tempIndices, sizeof(soyIndices)*triCount);
  tempUVs = soy_alloc(tempUVs, sizeof(texCoord)*uvCount);
  tempNormals = soy_alloc(tempNormals, sizeof(vec4)*normalCount);
  tempTris = soy_alloc(tempTris, sizeof(soyTri)*triCount);

  if(tempVerts == NULL || tempIndices == NULL || tempUVs == NULL || tempNormals == NULL) {
    SLOG("Error allocating soyMesh memory\n");
  }
  vertCount = 0;
  uvCount = 0;
  normalCount = 0;
  triCount = 0;

  while(TRUE) {
    res = fscanf(file, "%s", lineHeader);
    if(res == EOF) {
      break;
    }
    if(strcmp(lineHeader, "v") == 0) {
      fscanf(file, "%f %f %f\n", &tempVerts[vertCount].x, &tempVerts[vertCount].y, &tempVerts[vertCount].z);
      vertCount++;
    } else if(strcmp(lineHeader, "vt") == 0) {
      fscanf(file, "%f %f\n", &tempUVs[uvCount].u, &tempUVs[uvCount].v);

      uvCount++;
    } else if(strcmp(lineHeader, "vn") == 0) {
      fscanf(file, "%f %f %f\n",
          &tempNormals[normalCount].x,
          &tempNormals[normalCount].y,
          &tempNormals[normalCount].z);
      normalCount++;
    } else if(strcmp(lineHeader, "f") == 0) {
      if( uvCount > 0 && normalCount > 0 ) {
        fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
          &tempIndices[triCount].vertIndices.x,
          &tempIndices[triCount].uvIndices.x,
          &tempIndices[triCount].normalIndices.x,

          &tempIndices[triCount].vertIndices.y,
          &tempIndices[triCount].uvIndices.y,
          &tempIndices[triCount].normalIndices.y,

          &tempIndices[triCount].vertIndices.z,
          &tempIndices[triCount].uvIndices.z,
          &tempIndices[triCount].normalIndices.z
          );
      } else if(uvCount == 0 && normalCount > 0) {
        fscanf(file, "%d//%d %d//%d %d//%d\n",
          &tempIndices[triCount].vertIndices.x,
          &tempIndices[triCount].normalIndices.x,

          &tempIndices[triCount].vertIndices.y,
          &tempIndices[triCount].normalIndices.y,

          &tempIndices[triCount].vertIndices.z,
          &tempIndices[triCount].normalIndices.z
          );
      } else if(uvCount > 0 && normalCount == 0) {
         fscanf(file, "%d/%d %d/%d %d/%d\n",
          &tempIndices[triCount].vertIndices.x,
          &tempIndices[triCount].uvIndices.x,

          &tempIndices[triCount].vertIndices.y,
          &tempIndices[triCount].uvIndices.y,

          &tempIndices[triCount].vertIndices.z,
          &tempIndices[triCount].uvIndices.z
          );
      } else if(uvCount == 0 && normalCount == 0) {
         fscanf(file, "%d %d %d\n",
          &tempIndices[triCount].vertIndices.x,
          &tempIndices[triCount].vertIndices.y,
          &tempIndices[triCount].vertIndices.z
          );
      }
      triCount++;
    }
  }
  for(index = 0; index < triCount; index++) {
    if(vertCount) {
      tempTris[index].v1.points = tempVerts[tempIndices[index].vertIndices.x-1];
      tempTris[index].v1.points.w = 1.0f;
      tempTris[index].v2.points = tempVerts[tempIndices[index].vertIndices.y-1];
      tempTris[index].v2.points.w = 1.0f;
      tempTris[index].v3.points = tempVerts[tempIndices[index].vertIndices.z-1];
      tempTris[index].v3.points.w = 1.0f;
    }
    if(normalCount) {
      tempTris[index].v1.normals = tempNormals[tempIndices[index].normalIndices.x-1];
      tempTris[index].v2.normals = tempNormals[tempIndices[index].normalIndices.y-1];
      tempTris[index].v3.normals = tempNormals[tempIndices[index].normalIndices.z-1];
    } else {
      tempTris[index].v1.normals = soy_3d_vec4(0.0f, 0.0f, 0.0f, 0.0f);
      tempTris[index].v2.normals = soy_3d_vec4(0.0f, 0.0f, 0.0f, 0.0f);
      tempTris[index].v3.normals = soy_3d_vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    if(uvCount) {
      tempTris[index].v1.UVs = tempUVs[tempIndices[index].uvIndices.x-1];
      tempTris[index].v2.UVs = tempUVs[tempIndices[index].uvIndices.y-1];
      tempTris[index].v3.UVs = tempUVs[tempIndices[index].uvIndices.z-1];
    } else {
      tempTris[index].v1.UVs = soy_3d_uv(0.0f, 0.0f, 0.0f);
      tempTris[index].v2.UVs = soy_3d_uv(0.0f, 0.0f, 0.0f);
    }
  }
  destMesh->triangles = tempTris;
  destMesh->initialized = TRUE;
  soy_free(tempVerts);
  soy_free(tempIndices);
  soy_free(tempUVs);
  soy_free(tempNormals);
  fclose(file);
  SLOG1("Loaded asset: %s\n", filename);
  return TRUE;
}

static long modelIDs = 0;

flag soy_3d_create_model(soyModel* model, const char* filename, const char* name) {
  char pathBuffer[256];
  const char* defaultName = "Null";
  FILE* file = NULL;
  int filesize = 0;
  modelIDs++;
  model->ID = modelIDs;
  if(model == NULL) {
    return ERROR;
  }
  if(filename != NULL) {
    soy_3d_import_obj(&model->mesh, filename);
  } else {
    SLOG1("Could not create model: %s\n", filename);
    return ERROR;
  }
  if(name == NULL) {
    name = defaultName;
  } else {
    model->mesh.name = name;
  }
  file = fopen(filename, "r");
  fseek(file, 0L, SEEK_END);
  filesize = ftell(file);
  fclose(file);
  model->alive = TRUE;
  model->fileSize = filesize;

  sprintf(pathBuffer, "%s%s%s", "Assets/Meshes/", name, ".sem");
/*
  soy_3d_export_sem(&model->mesh, pathBuffer);
  soy_3d_import_sem(&model->mesh, pathBuffer);
*/
  return TRUE;
}

flag soy_3d_free_model(soyModel* model) {
  soy_3d_free_soyMesh(&model->mesh);
  model->alive = FALSE;
  return TRUE;
}


#endif
