// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 28

#include <Box2D/Box2D.h>

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetLocalAnchorA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    anchor[0] = joint->GetLocalAnchorA().x;
    anchor[1] = joint->GetLocalAnchorA().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetLocalAnchorB___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    anchor[0] = joint->GetLocalAnchorB().x;
    anchor[1] = joint->GetLocalAnchorB().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetLocalAxisA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    anchor[0] = joint->GetLocalAxisA().x;
    anchor[1] = joint->GetLocalAxisA().y;
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetJointTranslation___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->GetJointTranslation();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetJointSpeed___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->GetJointSpeed();
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniIsLimitEnabled___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->IsLimitEnabled();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniEnableLimit___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    joint->EnableLimit(flag);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetLowerLimit___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->GetLowerLimit();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetUpperLimit___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->GetUpperLimit();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniSetLimits___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT lower, JAVA_FLOAT upper) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    joint->SetLimits(lower, upper);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniIsMotorEnabled___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->IsMotorEnabled();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniEnableMotor___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    joint->EnableMotor(flag);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniSetMotorSpeed___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT speed) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    joint->SetMotorSpeed(speed);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetMotorSpeed___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->GetMotorSpeed();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniSetMaxMotorForce___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT force) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    joint->SetMaxMotorForce(force);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetMotorForce___long_float_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT invDt) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->GetMotorForce(invDt);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetMaxMotorForce___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->GetMaxMotorForce();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PrismaticJoint_jniGetReferenceAngle___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PrismaticJoint *joint = (b2PrismaticJoint *) addr;
    return joint->GetReferenceAngle();
}

