// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 28

#include <Box2D/Box2D.h>

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetLocalAnchorA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    anchor[0] = joint->GetLocalAnchorA().x;
    anchor[1] = joint->GetLocalAnchorA().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetLocalAnchorB___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    anchor[0] = joint->GetLocalAnchorB().x;
    anchor[1] = joint->GetLocalAnchorB().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetLocalAxisA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    anchor[0] = joint->GetLocalAxisA().x;
    anchor[1] = joint->GetLocalAxisA().y;
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetJointTranslation___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    return joint->GetJointTranslation();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetJointSpeed___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    return joint->GetJointSpeed();
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniIsMotorEnabled___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    return joint->IsMotorEnabled();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniEnableMotor___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    joint->EnableMotor(flag);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniSetMotorSpeed___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT speed) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    joint->SetMotorSpeed(speed);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetMotorSpeed___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    return joint->GetMotorSpeed();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniSetMaxMotorTorque___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT torque) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    joint->SetMaxMotorTorque(torque);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetMaxMotorTorque___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    return joint->GetMaxMotorTorque();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetMotorTorque___long_float_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT invDt) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    return joint->GetMotorTorque(invDt);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniSetSpringFrequencyHz___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT hz) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    joint->SetSpringFrequencyHz(hz);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetSpringFrequencyHz___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    return joint->GetSpringFrequencyHz();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniSetSpringDampingRatio___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT ratio) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    joint->SetSpringDampingRatio(ratio);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_WheelJoint_jniGetSpringDampingRatio___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2WheelJoint *joint = (b2WheelJoint *) addr;
    return joint->GetSpringDampingRatio();
}

