#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/PolygonShape.hpp>

     #include <Box2D/Box2D.h>
	 
jlong com::badlogic::gdx::physics::box2d::PolygonShape::M_newPolygonShape_R_long() {

		b2PolygonShape* poly = new b2PolygonShape();
		return (jlong)poly;
}

void com::badlogic::gdx::physics::box2d::PolygonShape::M_jniSet_Array1_float(jlong addr, const jarray &verts_object, jint offset, jint len) {
	auto verts = (jfloat *)verts_object->data;

		b2PolygonShape* poly = (b2PolygonShape*)addr;
		int numVertices = len / 2;
		b2Vec2* verticesOut = new b2Vec2[numVertices];
		for(int i = 0; i < numVertices; i++) { 
			verticesOut[i] = b2Vec2(verts[(i<<1) + offset], verts[(i<<1) + offset + 1]);
		}
		poly->Set(verticesOut, numVertices);
		delete[] verticesOut;
	 }

void com::badlogic::gdx::physics::box2d::PolygonShape::M_jniSetAsBox(jlong addr, jfloat hx, jfloat hy) {

		b2PolygonShape* poly = (b2PolygonShape*)addr;
		poly->SetAsBox(hx, hy);
}

void com::badlogic::gdx::physics::box2d::PolygonShape::M_jniSetAsBox(jlong addr, jfloat hx, jfloat hy, jfloat centerX, jfloat centerY, jfloat angle) {

		b2PolygonShape* poly = (b2PolygonShape*)addr;
		poly->SetAsBox( hx, hy, b2Vec2( centerX, centerY ), angle );
}

jint com::badlogic::gdx::physics::box2d::PolygonShape::M_jniGetVertexCount_R_int(jlong addr) {

		b2PolygonShape* poly = (b2PolygonShape*)addr;
		return poly->GetVertexCount();
}

void com::badlogic::gdx::physics::box2d::PolygonShape::M_jniGetVertex_Array1_float(jlong addr, jint index, const jarray &verts_object) {
	auto verts = (jfloat *)verts_object->data;

		b2PolygonShape* poly = (b2PolygonShape*)addr;
		const b2Vec2 v = poly->GetVertex( index );
		verts[0] = v.x;
		verts[1] = v.y;
}

