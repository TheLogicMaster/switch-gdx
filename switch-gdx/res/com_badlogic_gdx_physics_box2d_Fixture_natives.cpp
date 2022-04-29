// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 25

#include <Box2D/Box2D.h>

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Fixture_jniGetType___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Fixture *fixture = (b2Fixture *) addr;
    b2Shape::Type type = fixture->GetType();
    switch (type) {
        case b2Shape::e_circle:
            return 0;
        case b2Shape::e_edge:
            return 1;
        case b2Shape::e_polygon:
            return 2;
        case b2Shape::e_chain:
            return 3;
        default:
            return -1;
    }
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_Fixture_jniGetShape___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Fixture *fixture = (b2Fixture *) addr;
    return (jlong) fixture->GetShape();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Fixture_jniSetSensor___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN sensor) {
    b2Fixture *fixture = (b2Fixture *) addr;
    fixture->SetSensor(sensor);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Fixture_jniIsSensor___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Fixture *fixture = (b2Fixture *) addr;
    return fixture->IsSensor();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Fixture_jniSetFilterData___long_short_short_short(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_SHORT categoryBits, JAVA_SHORT maskBits, JAVA_SHORT groupIndex) {
    b2Fixture *fixture = (b2Fixture *) addr;
    b2Filter filter;
    filter.categoryBits = categoryBits;
    filter.maskBits = maskBits;
    filter.groupIndex = groupIndex;
    fixture->SetFilterData(filter);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Fixture_jniGetFilterData___long_short_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT filter__object) {
    auto filter = (short *) ((JAVA_ARRAY) filter__object)->data;
    b2Fixture *fixture = (b2Fixture *) addr;
    unsigned short *filterOut = (unsigned short *) filter;
    b2Filter f = fixture->GetFilterData();
    filterOut[0] = f.maskBits;
    filterOut[1] = f.categoryBits;
    filterOut[2] = f.groupIndex;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Fixture_jniRefilter___long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Fixture *fixture = (b2Fixture *) addr;
    fixture->Refilter();
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Fixture_jniTestPoint___long_float_float_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT x, JAVA_FLOAT y) {
    b2Fixture *fixture = (b2Fixture *) addr;
    return fixture->TestPoint(b2Vec2(x, y));
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Fixture_jniSetDensity___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT density) {
    b2Fixture *fixture = (b2Fixture *) addr;
    fixture->SetDensity(density);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Fixture_jniGetDensity___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Fixture *fixture = (b2Fixture *) addr;
    return fixture->GetDensity();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Fixture_jniGetFriction___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Fixture *fixture = (b2Fixture *) addr;
    return fixture->GetFriction();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Fixture_jniSetFriction___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT friction) {
    b2Fixture *fixture = (b2Fixture *) addr;
    fixture->SetFriction(friction);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Fixture_jniGetRestitution___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Fixture *fixture = (b2Fixture *) addr;
    return fixture->GetRestitution();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Fixture_jniSetRestitution___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT restitution) {
    b2Fixture *fixture = (b2Fixture *) addr;
    fixture->SetRestitution(restitution);
}

