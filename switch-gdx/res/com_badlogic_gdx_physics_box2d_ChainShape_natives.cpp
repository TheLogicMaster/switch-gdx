// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 23

#include <Box2D/Box2D.h>

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_ChainShape_newChainShape___R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object) {
    return (jlong) (new b2ChainShape());
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_ChainShape_jniCreateLoop___long_float_1ARRAY_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT verts__object, JAVA_INT offset, JAVA_INT numVertices) {
    auto verts = (float *) ((JAVA_ARRAY) verts__object)->data;
    b2ChainShape *chain = (b2ChainShape *) addr;
    b2Vec2 *verticesOut = new b2Vec2[numVertices];
    for (int i = 0; i < numVertices; i++)
        verticesOut[i] = b2Vec2(verts[offset + (i << 1)], verts[offset + (i << 1) + 1]);
    chain->CreateLoop(verticesOut, numVertices);
    delete[] verticesOut;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_ChainShape_jniCreateChain___long_float_1ARRAY_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT verts__object, JAVA_INT offset, JAVA_INT numVertices) {
    auto verts = (float *) ((JAVA_ARRAY) verts__object)->data;
    b2ChainShape *chain = (b2ChainShape *) addr;
    b2Vec2 *verticesOut = new b2Vec2[numVertices];
    for (int i = 0; i < numVertices; i++)
        verticesOut[i] = b2Vec2(verts[offset + (i << 1)], verts[offset + (i << 1) + 1]);
    chain->CreateChain(verticesOut, numVertices);
    delete[] verticesOut;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_ChainShape_jniSetPrevVertex___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT x, JAVA_FLOAT y) {
    b2ChainShape *chain = (b2ChainShape *) addr;
    chain->SetPrevVertex(b2Vec2(x, y));
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_ChainShape_jniSetNextVertex___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT x, JAVA_FLOAT y) {
    b2ChainShape *chain = (b2ChainShape *) addr;
    chain->SetNextVertex(b2Vec2(x, y));
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_ChainShape_jniGetVertexCount___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2ChainShape *chain = (b2ChainShape *) addr;
    return chain->GetVertexCount();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_ChainShape_jniGetVertex___long_int_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_INT index, JAVA_OBJECT verts__object) {
    auto verts = (float *) ((JAVA_ARRAY) verts__object)->data;
    b2ChainShape *chain = (b2ChainShape *) addr;
    const b2Vec2 v = chain->GetVertex(index);
    verts[0] = v.x;
    verts[1] = v.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_ChainShape_jniClear___long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2ChainShape* chain = (b2ChainShape*)addr;
    chain->Clear();
}
