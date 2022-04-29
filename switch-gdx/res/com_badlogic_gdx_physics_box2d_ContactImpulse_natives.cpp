// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 24

#include <Box2D/Box2D.h>

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_ContactImpulse_jniGetNormalImpulses___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT values__object) {
    auto values = (float *) ((JAVA_ARRAY) values__object)->data;
    b2ContactImpulse *contactImpulse = (b2ContactImpulse *) addr;
    values[0] = contactImpulse->normalImpulses[0];
    values[1] = contactImpulse->normalImpulses[1];
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_ContactImpulse_jniGetTangentImpulses___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT values__object) {
    auto values = (float *) ((JAVA_ARRAY) values__object)->data;
    b2ContactImpulse *contactImpulse = (b2ContactImpulse *) addr;
    values[0] = contactImpulse->tangentImpulses[0];
    values[1] = contactImpulse->tangentImpulses[1];
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_ContactImpulse_jniGetCount___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2ContactImpulse *contactImpulse = (b2ContactImpulse *) addr;
    return contactImpulse->count;
}

