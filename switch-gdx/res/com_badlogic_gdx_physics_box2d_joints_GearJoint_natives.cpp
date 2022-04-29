// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 29

#include <Box2D/Box2D.h>

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_joints_GearJoint_jniGetJoint1___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2GearJoint *joint = (b2GearJoint *) addr;
    b2Joint *joint1 = joint->GetJoint1();
    return (jlong) joint1;
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_joints_GearJoint_jniGetJoint2___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2GearJoint *joint = (b2GearJoint *) addr;
    b2Joint *joint2 = joint->GetJoint2();
    return (jlong) joint2;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_GearJoint_jniSetRatio___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT ratio) {
    b2GearJoint *joint = (b2GearJoint *) addr;
    joint->SetRatio(ratio);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_GearJoint_jniGetRatio___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2GearJoint *joint = (b2GearJoint *) addr;
    return joint->GetRatio();
}

