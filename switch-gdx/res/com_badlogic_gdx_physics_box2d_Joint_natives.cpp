// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 24

#include <Box2D/Box2D.h>

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Joint_jniGetType___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Joint *joint = (b2Joint *) addr;
    return joint->GetType();
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_Joint_jniGetBodyA___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Joint *joint = (b2Joint *) addr;
    return (jlong) joint->GetBodyA();
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_Joint_jniGetBodyB___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Joint *joint = (b2Joint *) addr;
    return (jlong) joint->GetBodyB();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Joint_jniGetAnchorA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchorA__object) {
    auto anchorA = (float *) ((JAVA_ARRAY) anchorA__object)->data;
    b2Joint *joint = (b2Joint *) addr;
    b2Vec2 a = joint->GetAnchorA();
    anchorA[0] = a.x;
    anchorA[1] = a.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Joint_jniGetAnchorB___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchorB__object) {
    auto anchorB = (float *) ((JAVA_ARRAY) anchorB__object)->data;
    b2Joint *joint = (b2Joint *) addr;
    b2Vec2 a = joint->GetAnchorB();
    anchorB[0] = a.x;
    anchorB[1] = a.y;
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Joint_jniGetCollideConnected___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Joint *joint = (b2Joint *) addr;
    return joint->GetCollideConnected();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Joint_jniGetReactionForce___long_float_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT inv_dt, JAVA_OBJECT reactionForce__object) {
    auto reactionForce = (float *) ((JAVA_ARRAY) reactionForce__object)->data;
    b2Joint *joint = (b2Joint *) addr;
    b2Vec2 f = joint->GetReactionForce(inv_dt);
    reactionForce[0] = f.x;
    reactionForce[1] = f.y;
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Joint_jniGetReactionTorque___long_float_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT inv_dt) {
    b2Joint *joint = (b2Joint *) addr;
    return joint->GetReactionTorque(inv_dt);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Joint_jniIsActive___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Joint *joint = (b2Joint *) addr;
    return joint->IsActive();
}

