// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 23

#include <Box2D/Box2D.h>

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_PolygonShape_newPolygonShape___R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object) {
    b2PolygonShape *poly = new b2PolygonShape();
    return (jlong) poly;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_PolygonShape_jniSet___long_float_1ARRAY_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT verts__object, JAVA_INT offset, JAVA_INT len) {
    auto verts = (float *) ((JAVA_ARRAY) verts__object)->data;
    b2PolygonShape *poly = (b2PolygonShape *) addr;
    int numVertices = len / 2;
    b2Vec2 *verticesOut = new b2Vec2[numVertices];
    for (int i = 0; i < numVertices; i++) {
        verticesOut[i] = b2Vec2(verts[(i << 1) + offset], verts[(i << 1) + offset + 1]);
    }
    poly->Set(verticesOut, numVertices);
    delete[] verticesOut;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_PolygonShape_jniSetAsBox___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT hx, JAVA_FLOAT hy) {
    b2PolygonShape *poly = (b2PolygonShape *) addr;
    poly->SetAsBox(hx, hy);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_PolygonShape_jniSetAsBox___long_float_float_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT hx, JAVA_FLOAT hy, JAVA_FLOAT centerX, JAVA_FLOAT centerY, JAVA_FLOAT angle) {
    b2PolygonShape *poly = (b2PolygonShape *) addr;
    poly->SetAsBox(hx, hy, b2Vec2(centerX, centerY), angle);
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_PolygonShape_jniGetVertexCount___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2PolygonShape *poly = (b2PolygonShape *) addr;
    return poly->GetVertexCount();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_PolygonShape_jniGetVertex___long_int_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_INT index, JAVA_OBJECT verts__object) {
    auto verts = (float *) ((JAVA_ARRAY) verts__object)->data;
    b2PolygonShape *poly = (b2PolygonShape *) addr;
    const b2Vec2 v = poly->GetVertex(index);
    verts[0] = v.x;
    verts[1] = v.y;
}

