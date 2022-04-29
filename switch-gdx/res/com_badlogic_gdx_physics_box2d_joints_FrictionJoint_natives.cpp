// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 26

#include <Box2D/Box2D.h>

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_FrictionJoint_jniGetLocalAnchorA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2FrictionJoint *joint = (b2FrictionJoint *) addr;
    anchor[0] = joint->GetLocalAnchorA().x;
    anchor[1] = joint->GetLocalAnchorA().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_FrictionJoint_jniGetLocalAnchorB___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2FrictionJoint *joint = (b2FrictionJoint *) addr;
    anchor[0] = joint->GetLocalAnchorB().x;
    anchor[1] = joint->GetLocalAnchorB().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_FrictionJoint_jniSetMaxForce___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT force) {
    b2FrictionJoint *joint = (b2FrictionJoint *) addr;
    joint->SetMaxForce(force);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_FrictionJoint_jniGetMaxForce___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2FrictionJoint *joint = (b2FrictionJoint *) addr;
    return joint->GetMaxForce();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_FrictionJoint_jniSetMaxTorque___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT torque) {
    b2FrictionJoint *joint = (b2FrictionJoint *) addr;
    joint->SetMaxTorque(torque);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_FrictionJoint_jniGetMaxTorque___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2FrictionJoint *joint = (b2FrictionJoint *) addr;
    return joint->GetMaxTorque();
}

