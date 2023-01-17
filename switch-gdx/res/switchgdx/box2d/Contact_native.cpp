#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/Contact.hpp>

#include <Box2D/Box2D.h>
	 
jint com::badlogic::gdx::physics::box2d::Contact::M_jniGetWorldManifold_Array1_float_R_int(jlong addr, const jarray &tmp_object) {
	auto tmp = (jfloat *)tmp_object->data;

		b2Contact* contact = (b2Contact*)addr;
		b2WorldManifold manifold;
		contact->GetWorldManifold(&manifold);
		int numPoints = contact->GetManifold()->pointCount;
	
		tmp[0] = manifold.normal.x;
		tmp[1] = manifold.normal.y;
	
		for( int i = 0; i < numPoints; i++ )
		{
			tmp[2 + i*2] = manifold.points[i].x;
			tmp[2 + i*2+1] = manifold.points[i].y;
		}
	
		tmp[6] = manifold.separations[0];
		tmp[7] = manifold.separations[1];

		return numPoints;
}

jbool com::badlogic::gdx::physics::box2d::Contact::M_jniIsTouching_R_boolean(jlong addr) {

		b2Contact* contact = (b2Contact*)addr;
		return contact->IsTouching();
}

void com::badlogic::gdx::physics::box2d::Contact::M_jniSetEnabled(jlong addr, jbool flag) {

		b2Contact* contact = (b2Contact*)addr;
		contact->SetEnabled(flag);
}

jbool com::badlogic::gdx::physics::box2d::Contact::M_jniIsEnabled_R_boolean(jlong addr) {

		b2Contact* contact = (b2Contact*)addr;
		return contact->IsEnabled();
}

jlong com::badlogic::gdx::physics::box2d::Contact::M_jniGetFixtureA_R_long(jlong addr) {

		b2Contact* contact = (b2Contact*)addr;
		return (jlong)contact->GetFixtureA();
}

jlong com::badlogic::gdx::physics::box2d::Contact::M_jniGetFixtureB_R_long(jlong addr) {

		b2Contact* contact = (b2Contact*)addr;
		return (jlong)contact->GetFixtureB();
}

jint com::badlogic::gdx::physics::box2d::Contact::M_jniGetChildIndexA_R_int(jlong addr) {

		b2Contact* contact = (b2Contact*)addr;
		return contact->GetChildIndexA();
}

jint com::badlogic::gdx::physics::box2d::Contact::M_jniGetChildIndexB_R_int(jlong addr) {

		b2Contact* contact = (b2Contact*)addr;
		return contact->GetChildIndexB();
}

void com::badlogic::gdx::physics::box2d::Contact::M_jniSetFriction(jlong addr, jfloat friction) {

		b2Contact* contact = (b2Contact*)addr;
		contact->SetFriction(friction);
}

jfloat com::badlogic::gdx::physics::box2d::Contact::M_jniGetFriction_R_float(jlong addr) {

		b2Contact* contact = (b2Contact*)addr;
		return contact->GetFriction();
}

void com::badlogic::gdx::physics::box2d::Contact::M_jniResetFriction(jlong addr) {

	  	b2Contact* contact = (b2Contact*)addr;
		contact->ResetFriction();
}

void com::badlogic::gdx::physics::box2d::Contact::M_jniSetRestitution(jlong addr, jfloat restitution) {

	  	b2Contact* contact = (b2Contact*)addr;
		contact->SetRestitution(restitution);
}

jfloat com::badlogic::gdx::physics::box2d::Contact::M_jniGetRestitution_R_float(jlong addr) {

	  	b2Contact* contact = (b2Contact*)addr;
		return contact->GetRestitution();
}

void com::badlogic::gdx::physics::box2d::Contact::M_jniResetRestitution(jlong addr) {

	  	b2Contact* contact = (b2Contact*)addr;
		contact->ResetRestitution();
}

jfloat com::badlogic::gdx::physics::box2d::Contact::M_jniGetTangentSpeed_R_float(jlong addr) {

	  	b2Contact* contact = (b2Contact*)addr;
		return contact->GetTangentSpeed();
}

void com::badlogic::gdx::physics::box2d::Contact::M_jniSetTangentSpeed(jlong addr, jfloat speed) {

	  	b2Contact* contact = (b2Contact*)addr;
		contact->SetTangentSpeed(speed);
}

