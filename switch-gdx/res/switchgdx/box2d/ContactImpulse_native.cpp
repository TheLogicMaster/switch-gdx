#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/ContactImpulse.hpp>

#include <Box2D/Box2D.h>
	 
void com::badlogic::gdx::physics::box2d::ContactImpulse::M_jniGetNormalImpulses_Array1_float(jlong addr, const jarray &values_object) {
	auto values = (jfloat *)values_object->data;

		b2ContactImpulse* contactImpulse = (b2ContactImpulse*)addr;	
		values[0] = contactImpulse->normalImpulses[0];
		values[1] = contactImpulse->normalImpulses[1];
}

void com::badlogic::gdx::physics::box2d::ContactImpulse::M_jniGetTangentImpulses_Array1_float(jlong addr, const jarray &values_object) {
	auto values = (jfloat *)values_object->data;

	  	b2ContactImpulse* contactImpulse = (b2ContactImpulse*)addr;	
		values[0] = contactImpulse->tangentImpulses[0];
		values[1] = contactImpulse->tangentImpulses[1];
}

jint com::badlogic::gdx::physics::box2d::ContactImpulse::M_jniGetCount_R_int(jlong addr) {

		b2ContactImpulse* contactImpulse = (b2ContactImpulse*)addr;
		return contactImpulse->count;
}

