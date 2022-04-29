// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 25

#include <Box2D/Box2D.h>

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_EdgeShape_newEdgeShape___R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object) {
    return (jlong) (new b2EdgeShape());
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_EdgeShape_jniSet___long_float_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT v1x, JAVA_FLOAT v1y, JAVA_FLOAT v2x, JAVA_FLOAT v2y) {
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    edge->Set(b2Vec2(v1x, v1y), b2Vec2(v2x, v2y));
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_EdgeShape_jniGetVertex1___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT vertex__object) {
    auto vertex = (float *) ((JAVA_ARRAY) vertex__object)->data;
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    vertex[0] = edge->m_vertex1.x;
    vertex[1] = edge->m_vertex1.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_EdgeShape_jniGetVertex2___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT vertex__object) {
    auto vertex = (float *) ((JAVA_ARRAY) vertex__object)->data;
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    vertex[0] = edge->m_vertex2.x;
    vertex[1] = edge->m_vertex2.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_EdgeShape_jniGetVertex0___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT vertex__object) {
    auto vertex = (float *) ((JAVA_ARRAY) vertex__object)->data;
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    vertex[0] = edge->m_vertex0.x;
    vertex[1] = edge->m_vertex0.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_EdgeShape_jniSetVertex0___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT x, JAVA_FLOAT y) {
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    edge->m_vertex0.x = x;
    edge->m_vertex0.y = y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_EdgeShape_jniGetVertex3___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT vertex__object) {
    auto vertex = (float *) ((JAVA_ARRAY) vertex__object)->data;
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    vertex[0] = edge->m_vertex3.x;
    vertex[1] = edge->m_vertex3.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_EdgeShape_jniSetVertex3___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT x, JAVA_FLOAT y) {
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    edge->m_vertex3.x = x;
    edge->m_vertex3.y = y;
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_EdgeShape_jniHasVertex0___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    return edge->m_hasVertex0;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_EdgeShape_jniSetHasVertex0___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN hasVertex0) {
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    edge->m_hasVertex0 = hasVertex0;
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_EdgeShape_jniHasVertex3___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    return edge->m_hasVertex3;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_EdgeShape_jniSetHasVertex3___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN hasVertex3) {
    b2EdgeShape *edge = (b2EdgeShape *) addr;
    edge->m_hasVertex3 = hasVertex3;
}

