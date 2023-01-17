#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/Manifold.hpp>

#include <Box2D/Box2D.h>
	 
jint com::badlogic::gdx::physics::box2d::Manifold::M_jniGetType_R_int(jlong addr) {

		b2Manifold* manifold = (b2Manifold*)addr;
		return manifold->type;
}

jint com::badlogic::gdx::physics::box2d::Manifold::M_jniGetPointCount_R_int(jlong addr) {

	  	b2Manifold* manifold = (b2Manifold*)addr;
		return manifold->pointCount;
}

void com::badlogic::gdx::physics::box2d::Manifold::M_jniGetLocalNormal_Array1_float(jlong addr, const jarray &values_object) {
	auto values = (jfloat *)values_object->data;

		b2Manifold* manifold = (b2Manifold*)addr;
		values[0] = manifold->localNormal.x;
		values[1] = manifold->localNormal.y;
}

void com::badlogic::gdx::physics::box2d::Manifold::M_jniGetLocalPoint_Array1_float(jlong addr, const jarray &values_object) {
	auto values = (jfloat *)values_object->data;

		b2Manifold* manifold = (b2Manifold*)addr;
		values[0] = manifold->localPoint.x;
		values[1] = manifold->localPoint.y;
}

jint com::badlogic::gdx::physics::box2d::Manifold::M_jniGetPoint_Array1_float_R_int(jlong addr, const jarray &values_object, jint idx) {
	auto values = (jfloat *)values_object->data;

		b2Manifold* manifold = (b2Manifold*)addr;
		  
		values[0] = manifold->points[idx].localPoint.x;
		values[1] = manifold->points[idx].localPoint.y;
		values[2] = manifold->points[idx].normalImpulse;
		values[3] = manifold->points[idx].tangentImpulse;  
		  
		return (jint)manifold->points[idx].id.key;
}

