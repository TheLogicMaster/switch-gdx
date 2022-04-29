// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 26

#include <Box2D/Box2D.h>

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Contact_jniGetWorldManifold___long_float_1ARRAY_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT tmp__object) {
    auto tmp = (float *) ((JAVA_ARRAY) tmp__object)->data;
    b2Contact *contact = (b2Contact *) addr;
    b2WorldManifold manifold;
    contact->GetWorldManifold(&manifold);
    int numPoints = contact->GetManifold()->pointCount;

    tmp[0] = manifold.normal.x;
    tmp[1] = manifold.normal.y;

    for (int i = 0; i < numPoints; i++) {
        tmp[2 + i * 2] = manifold.points[i].x;
        tmp[2 + i * 2 + 1] = manifold.points[i].y;
    }

    tmp[6] = manifold.separations[0];
    tmp[7] = manifold.separations[1];

    return numPoints;
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Contact_jniIsTouching___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    return contact->IsTouching();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Contact_jniSetEnabled___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2Contact *contact = (b2Contact *) addr;
    contact->SetEnabled(flag);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Contact_jniIsEnabled___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    return contact->IsEnabled();
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_Contact_jniGetFixtureA___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    return (jlong) contact->GetFixtureA();
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_Contact_jniGetFixtureB___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    return (jlong) contact->GetFixtureB();
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Contact_jniGetChildIndexA___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    return contact->GetChildIndexA();
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Contact_jniGetChildIndexB___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    return contact->GetChildIndexB();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Contact_jniSetFriction___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT friction) {
    b2Contact *contact = (b2Contact *) addr;
    contact->SetFriction(friction);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Contact_jniGetFriction___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    return contact->GetFriction();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Contact_jniResetFriction___long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    contact->ResetFriction();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Contact_jniSetRestitution___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT restitution) {
    b2Contact *contact = (b2Contact *) addr;
    contact->SetRestitution(restitution);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Contact_jniGetRestitution___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    return contact->GetRestitution();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Contact_jniResetRestitution___long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    contact->ResetRestitution();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Contact_jniGetTangentSpeed___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Contact *contact = (b2Contact *) addr;
    return contact->GetTangentSpeed();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Contact_jniSetTangentSpeed___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT speed) {
    b2Contact *contact = (b2Contact *) addr;
    contact->SetTangentSpeed(speed);
}

