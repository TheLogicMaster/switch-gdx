// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 27

#include <Box2D/Box2D.h>

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WeldJoint_jniGetLocalAnchorA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2WeldJoint *joint = (b2WeldJoint *) addr;
    anchor[0] = joint->GetLocalAnchorA().x;
    anchor[1] = joint->GetLocalAnchorA().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WeldJoint_jniGetLocalAnchorB___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2WeldJoint *joint = (b2WeldJoint *) addr;
    anchor[0] = joint->GetLocalAnchorB().x;
    anchor[1] = joint->GetLocalAnchorB().y;
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WeldJoint_jniGetReferenceAngle___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WeldJoint *joint = (b2WeldJoint *) addr;
    return joint->GetReferenceAngle();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WeldJoint_jniGetFrequency___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WeldJoint *joint = (b2WeldJoint *) addr;
    return joint->GetFrequency();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WeldJoint_jniSetFrequency___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT hz) {
    b2WeldJoint *joint = (b2WeldJoint *) addr;
    joint->SetFrequency(hz);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WeldJoint_jniGetDampingRatio___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WeldJoint *joint = (b2WeldJoint *) addr;
    return joint->GetDampingRatio();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WeldJoint_jniSetDampingRatio___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT ratio) {
    b2WeldJoint *joint = (b2WeldJoint *) addr;
    joint->SetDampingRatio(ratio);
}

