#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/ChainShape.hpp>

#include <Box2D/Box2D.h>
	 
jlong com::badlogic::gdx::physics::box2d::ChainShape::M_newChainShape_R_long() {

		return (jlong)(new b2ChainShape());
}

void com::badlogic::gdx::physics::box2d::ChainShape::M_jniCreateLoop_Array1_float(jlong addr, const jarray &verts_object, jint offset, jint numVertices) {
	auto verts = (jfloat *)verts_object->data;

		b2ChainShape* chain = (b2ChainShape*)addr;
		b2Vec2* verticesOut = new b2Vec2[numVertices];
		for( int i = 0; i < numVertices; i++ )
			verticesOut[i] = b2Vec2(verts[offset+(i<<1)], verts[offset+(i<<1)+1]);
		chain->CreateLoop( verticesOut, numVertices );
		delete[] verticesOut;
}

void com::badlogic::gdx::physics::box2d::ChainShape::M_jniCreateChain_Array1_float(jlong addr, const jarray &verts_object, jint offset, jint numVertices) {
	auto verts = (jfloat *)verts_object->data;

		b2ChainShape* chain = (b2ChainShape*)addr;
		b2Vec2* verticesOut = new b2Vec2[numVertices];
		for( int i = 0; i < numVertices; i++ )
			verticesOut[i] = b2Vec2(verts[offset+(i<<1)], verts[offset+(i<<1)+1]);
		chain->CreateChain( verticesOut, numVertices );
		delete[] verticesOut;
}

void com::badlogic::gdx::physics::box2d::ChainShape::M_jniSetPrevVertex(jlong addr, jfloat x, jfloat y) {

		b2ChainShape* chain = (b2ChainShape*)addr;
		chain->SetPrevVertex(b2Vec2(x, y));
}

void com::badlogic::gdx::physics::box2d::ChainShape::M_jniSetNextVertex(jlong addr, jfloat x, jfloat y) {

		b2ChainShape* chain = (b2ChainShape*)addr;
		chain->SetNextVertex(b2Vec2(x, y));
}

jint com::badlogic::gdx::physics::box2d::ChainShape::M_jniGetVertexCount_R_int(jlong addr) {

		b2ChainShape* chain = (b2ChainShape*)addr;
		return chain->GetVertexCount();
}

void com::badlogic::gdx::physics::box2d::ChainShape::M_jniGetVertex_Array1_float(jlong addr, jint index, const jarray &verts_object) {
	auto verts = (jfloat *)verts_object->data;

		b2ChainShape* chain = (b2ChainShape*)addr;
		const b2Vec2 v = chain->GetVertex( index );
		verts[0] = v.x;
		verts[1] = v.y;
}

void com::badlogic::gdx::physics::box2d::ChainShape::M_jniClear(jlong addr) {
    b2ChainShape* chain = (b2ChainShape*)addr;
    chain->Clear();
}
