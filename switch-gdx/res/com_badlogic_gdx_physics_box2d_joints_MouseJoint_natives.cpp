// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 28

#include <Box2D/Box2D.h>

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MouseJoint_jniSetTarget___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT x, JAVA_FLOAT y) {
    b2MouseJoint *joint = (b2MouseJoint *) addr;
    joint->SetTarget(b2Vec2(x, y));
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MouseJoint_jniGetTarget___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT target__object) {
    auto target = (float *) ((JAVA_ARRAY) target__object)->data;
    b2MouseJoint *joint = (b2MouseJoint *) addr;
    target[0] = joint->GetTarget().x;
    target[1] = joint->GetTarget().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MouseJoint_jniSetMaxForce___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT force) {
    b2MouseJoint *joint = (b2MouseJoint *) addr;
    joint->SetMaxForce(force);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_MouseJoint_jniGetMaxForce___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2MouseJoint *joint = (b2MouseJoint *) addr;
    return joint->GetMaxForce();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MouseJoint_jniSetFrequency___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT hz) {
    b2MouseJoint *joint = (b2MouseJoint *) addr;
    joint->SetFrequency(hz);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_MouseJoint_jniGetFrequency___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2MouseJoint *joint = (b2MouseJoint *) addr;
    return joint->GetFrequency();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MouseJoint_jniSetDampingRatio___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT ratio) {
    b2MouseJoint *joint = (b2MouseJoint *) addr;
    joint->SetDampingRatio(ratio);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_MouseJoint_jniGetDampingRatio___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2MouseJoint *joint = (b2MouseJoint *) addr;
    return joint->GetDampingRatio();
}

