// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 27

#include <Box2D/Box2D.h>

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniGetLinearOffset___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT linearOffset__object) {
    auto linearOffset = (float *) ((JAVA_ARRAY) linearOffset__object)->data;
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    linearOffset[0] = joint->GetLinearOffset().x;
    linearOffset[1] = joint->GetLinearOffset().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniSetLinearOffset___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT linearOffsetX, JAVA_FLOAT linearOffsetY) {
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    joint->SetLinearOffset(b2Vec2(linearOffsetX, linearOffsetY));
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniGetAngularOffset___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    return joint->GetAngularOffset();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniSetAngularOffset___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT angularOffset) {
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    joint->SetAngularOffset(angularOffset);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniGetMaxForce___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    return joint->GetMaxForce();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniSetMaxForce___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT maxForce) {
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    joint->SetMaxForce(maxForce);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniGetMaxTorque___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    return joint->GetMaxTorque();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniSetMaxTorque___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT maxTorque) {
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    joint->SetMaxTorque(maxTorque);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniGetCorrectionFactor___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    return joint->GetCorrectionFactor();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_MotorJoint_jniSetCorrectionFactor___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT correctionFactor) {
    b2MotorJoint *joint = (b2MotorJoint *) addr;
    joint->SetCorrectionFactor(correctionFactor);
}

