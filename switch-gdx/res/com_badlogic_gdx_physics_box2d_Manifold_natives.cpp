// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 23

#include <Box2D/Box2D.h>

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Manifold_jniGetType___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Manifold *manifold = (b2Manifold *) addr;
    return manifold->type;
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Manifold_jniGetPointCount___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Manifold *manifold = (b2Manifold *) addr;
    return manifold->pointCount;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Manifold_jniGetLocalNormal___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT values__object) {
    auto values = (float *) ((JAVA_ARRAY) values__object)->data;
    b2Manifold *manifold = (b2Manifold *) addr;
    values[0] = manifold->localNormal.x;
    values[1] = manifold->localNormal.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Manifold_jniGetLocalPoint___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT values__object) {
    auto values = (float *) ((JAVA_ARRAY) values__object)->data;
    b2Manifold *manifold = (b2Manifold *) addr;
    values[0] = manifold->localPoint.x;
    values[1] = manifold->localPoint.y;
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Manifold_jniGetPoint___long_float_1ARRAY_int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT values__object, JAVA_INT idx) {
    auto values = (float *) ((JAVA_ARRAY) values__object)->data;
    b2Manifold *manifold = (b2Manifold *) addr;

    values[0] = manifold->points[idx].localPoint.x;
    values[1] = manifold->points[idx].localPoint.y;
    values[2] = manifold->points[idx].normalImpulse;
    values[3] = manifold->points[idx].tangentImpulse;

    return (jint) manifold->points[idx].id.key;
}

