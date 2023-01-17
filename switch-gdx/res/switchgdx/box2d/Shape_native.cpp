#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/Shape.hpp>

#include <Box2D/Box2D.h>
	 
jfloat com::badlogic::gdx::physics::box2d::Shape::M_jniGetRadius_R_float(jlong addr) {

		b2Shape* shape = (b2Shape*)addr;
		return shape->m_radius;
}

void com::badlogic::gdx::physics::box2d::Shape::M_jniSetRadius(jlong addr, jfloat radius) {

		b2Shape* shape = (b2Shape*)addr;
		shape->m_radius = radius;
}

void com::badlogic::gdx::physics::box2d::Shape::M_jniDispose(jlong addr) {

		b2Shape* shape = (b2Shape*)addr;
		delete shape;
}

jint com::badlogic::gdx::physics::box2d::Shape::SM_jniGetType_R_int(jlong addr) {

		b2Shape* shape = (b2Shape*)addr;
		switch(shape->m_type) {
		case b2Shape::e_circle: return 0;
		case b2Shape::e_edge: return 1;
		case b2Shape::e_polygon: return 2;
		case b2Shape::e_chain: return 3;
		default: return -1;
		}
}

jint com::badlogic::gdx::physics::box2d::Shape::M_jniGetChildCount_R_int(jlong addr) {

		b2Shape* shape = (b2Shape*)addr;
		return shape->GetChildCount();
}

