// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 28

#include <Box2D/Box2D.h>

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PulleyJoint_jniGetGroundAnchorA___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2PulleyJoint *joint = (b2PulleyJoint *) addr;
    anchor[0] = joint->GetGroundAnchorA().x;
    anchor[1] = joint->GetGroundAnchorA().y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_joints_PulleyJoint_jniGetGroundAnchorB___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT anchor__object) {
    auto anchor = (float *) ((JAVA_ARRAY) anchor__object)->data;
    b2PulleyJoint *joint = (b2PulleyJoint *) addr;
    anchor[0] = joint->GetGroundAnchorB().x;
    anchor[1] = joint->GetGroundAnchorB().y;
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PulleyJoint_jniGetLength1___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PulleyJoint *joint = (b2PulleyJoint *) addr;
    return joint->GetLengthA();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PulleyJoint_jniGetLength2___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PulleyJoint *joint = (b2PulleyJoint *) addr;
    return joint->GetLengthB();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_joints_PulleyJoint_jniGetRatio___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PulleyJoint *joint = (b2PulleyJoint *) addr;
    return joint->GetRatio();
}

