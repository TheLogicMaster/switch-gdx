// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 27

#include <Box2D/Box2D.h>

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_DistanceJoint_jniGetLocalAnchorA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2DistanceJoint *joint = (b2DistanceJoint *) addr;
    anchor[0] = joint->GetLocalAnchorA().x;
    anchor[1] = joint->GetLocalAnchorA().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_DistanceJoint_jniGetLocalAnchorB___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2DistanceJoint *joint = (b2DistanceJoint *) addr;
    anchor[0] = joint->GetLocalAnchorB().x;
    anchor[1] = joint->GetLocalAnchorB().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_DistanceJoint_jniSetLength___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT length) {
    b2DistanceJoint *joint = (b2DistanceJoint *) addr;
    joint->SetLength(length);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_DistanceJoint_jniGetLength___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2DistanceJoint *joint = (b2DistanceJoint *) addr;
    return joint->GetLength();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_DistanceJoint_jniSetFrequency___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT hz) {
    b2DistanceJoint *joint = (b2DistanceJoint *) addr;
    joint->SetFrequency(hz);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_DistanceJoint_jniGetFrequency___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2DistanceJoint *joint = (b2DistanceJoint *) addr;
    return joint->GetFrequency();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_DistanceJoint_jniSetDampingRatio___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT ratio) {
    b2DistanceJoint *joint = (b2DistanceJoint *) addr;
    joint->SetDampingRatio(ratio);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_DistanceJoint_jniGetDampingRatio___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2DistanceJoint *joint = (b2DistanceJoint *) addr;
    return joint->GetDampingRatio();
}

