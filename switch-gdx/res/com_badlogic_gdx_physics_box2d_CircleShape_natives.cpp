// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 25

#include <Box2D/Box2D.h>

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_CircleShape_newCircleShape___R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object) {
    return (jlong) (new b2CircleShape());
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_CircleShape_jniGetPosition___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT position__object) {
    auto position = (float *) ((JAVA_ARRAY) position__object)->data;
    b2CircleShape *circle = (b2CircleShape *) addr;
    position[0] = circle->m_p.x;
    position[1] = circle->m_p.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_CircleShape_jniSetPosition___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT positionX, JAVA_FLOAT positionY) {
    b2CircleShape *circle = (b2CircleShape *) addr;
    circle->m_p.x = positionX;
    circle->m_p.y = positionY;
}

