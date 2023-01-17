#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/EdgeShape.hpp>

#include <Box2D/Box2D.h>
	 
jlong com::badlogic::gdx::physics::box2d::EdgeShape::M_newEdgeShape_R_long() {

		return (jlong)(new b2EdgeShape());
}

void com::badlogic::gdx::physics::box2d::EdgeShape::M_jniSet(jlong addr, jfloat v1x, jfloat v1y, jfloat v2x, jfloat v2y) {

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		edge->Set(b2Vec2(v1x, v1y), b2Vec2(v2x, v2y));
}

void com::badlogic::gdx::physics::box2d::EdgeShape::M_jniGetVertex1_Array1_float(jlong addr, const jarray &vertex_object) {
	auto vertex = (jfloat *)vertex_object->data;

		b2EdgeShape* edge = (b2EdgeShape*)addr; 
		vertex[0] = edge->m_vertex1.x;
		vertex[1] = edge->m_vertex1.y;
}

void com::badlogic::gdx::physics::box2d::EdgeShape::M_jniGetVertex2_Array1_float(jlong addr, const jarray &vertex_object) {
	auto vertex = (jfloat *)vertex_object->data;

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		vertex[0] = edge->m_vertex2.x;
		vertex[1] = edge->m_vertex2.y;
}

void com::badlogic::gdx::physics::box2d::EdgeShape::M_jniGetVertex0_Array1_float(jlong addr, const jarray &vertex_object) {
	auto vertex = (jfloat *)vertex_object->data;

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		vertex[0] = edge->m_vertex0.x;
		vertex[1] = edge->m_vertex0.y;
}

void com::badlogic::gdx::physics::box2d::EdgeShape::M_jniSetVertex0(jlong addr, jfloat x, jfloat y) {

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		edge->m_vertex0.x = x;
		edge->m_vertex0.y = y;
}

void com::badlogic::gdx::physics::box2d::EdgeShape::M_jniGetVertex3_Array1_float(jlong addr, const jarray &vertex_object) {
	auto vertex = (jfloat *)vertex_object->data;

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		vertex[0] = edge->m_vertex3.x;
		vertex[1] = edge->m_vertex3.y;
}

void com::badlogic::gdx::physics::box2d::EdgeShape::M_jniSetVertex3(jlong addr, jfloat x, jfloat y) {

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		edge->m_vertex3.x = x;
		edge->m_vertex3.y = y;
}

jbool com::badlogic::gdx::physics::box2d::EdgeShape::M_jniHasVertex0_R_boolean(jlong addr) {

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		return edge->m_hasVertex0;
}

void com::badlogic::gdx::physics::box2d::EdgeShape::M_jniSetHasVertex0(jlong addr, jbool hasVertex0) {

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		edge->m_hasVertex0 = hasVertex0;
}

jbool com::badlogic::gdx::physics::box2d::EdgeShape::M_jniHasVertex3_R_boolean(jlong addr) {

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		return edge->m_hasVertex3;
}

void com::badlogic::gdx::physics::box2d::EdgeShape::M_jniSetHasVertex3(jlong addr, jbool hasVertex3) {

		b2EdgeShape* edge = (b2EdgeShape*)addr;
		edge->m_hasVertex3 = hasVertex3;
}

