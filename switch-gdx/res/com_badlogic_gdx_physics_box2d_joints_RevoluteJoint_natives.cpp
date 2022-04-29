// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 29

#include <Box2D/Box2D.h>

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetJointAngle___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->GetJointAngle();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetJointSpeed___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->GetJointSpeed();
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniIsLimitEnabled___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->IsLimitEnabled();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniEnableLimit___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    joint->EnableLimit(flag);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetLowerLimit___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->GetLowerLimit();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetUpperLimit___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->GetUpperLimit();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniSetLimits___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT lower, JAVA_FLOAT upper) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    joint->SetLimits(lower, upper);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniIsMotorEnabled___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->IsMotorEnabled();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniEnableMotor___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    joint->EnableMotor(flag);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniSetMotorSpeed___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT speed) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    joint->SetMotorSpeed(speed);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetMotorSpeed___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->GetMotorSpeed();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniSetMaxMotorTorque___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT torque) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    joint->SetMaxMotorTorque(torque);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetMotorTorque___long_float_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT invDt) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->GetMotorTorque(invDt);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetLocalAnchorA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    anchor[0] = joint->GetLocalAnchorA().x;
    anchor[1] = joint->GetLocalAnchorA().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetLocalAnchorB___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    anchor[0] = joint->GetLocalAnchorB().x;
    anchor[1] = joint->GetLocalAnchorB().y;
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetReferenceAngle___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->GetReferenceAngle();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_RevoluteJoint_jniGetMaxMotorTorque___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2RevoluteJoint *joint = (b2RevoluteJoint *) addr;
    return joint->GetMaxMotorTorque();
}

