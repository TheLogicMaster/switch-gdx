// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 26

#include <Box2D/Box2D.h>

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Shape_jniGetRadius___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Shape *shape = (b2Shape *) addr;
    return shape->m_radius;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Shape_jniSetRadius___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT radius) {
    b2Shape *shape = (b2Shape *) addr;
    shape->m_radius = radius;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Shape_jniDispose___long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Shape *shape = (b2Shape *) addr;
    delete shape;
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Shape_jniGetType___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG addr) {
    b2Shape *shape = (b2Shape *) addr;
    switch (shape->m_type) {
        case b2Shape::e_circle:
            return 0;
        case b2Shape::e_edge:
            return 1;
        case b2Shape::e_polygon:
            return 2;
        case b2Shape::e_chain:
            return 3;
        default:
            return -1;
    }
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Shape_jniGetChildCount___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Shape *shape = (b2Shape *) addr;
    return shape->GetChildCount();
}

