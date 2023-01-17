#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/Joint.hpp>

#include <Box2D/Box2D.h> 
	 
jint com::badlogic::gdx::physics::box2d::Joint::M_jniGetType_R_int(jlong addr) {

		b2Joint* joint = (b2Joint*)addr;
		return joint->GetType();
}

jlong com::badlogic::gdx::physics::box2d::Joint::M_jniGetBodyA_R_long(jlong addr) {

		b2Joint* joint = (b2Joint*)addr;
		return (jlong)joint->GetBodyA();
}

jlong com::badlogic::gdx::physics::box2d::Joint::M_jniGetBodyB_R_long(jlong addr) {

		b2Joint* joint = (b2Joint*)addr;
		return (jlong)joint->GetBodyB();
}

void com::badlogic::gdx::physics::box2d::Joint::M_jniGetAnchorA_Array1_float(jlong addr, const jarray &anchorA_object) {
	auto anchorA = (jfloat *)anchorA_object->data;

		b2Joint* joint = (b2Joint*)addr;
		b2Vec2 a = joint->GetAnchorA();
		anchorA[0] = a.x;
		anchorA[1] = a.y;
}

void com::badlogic::gdx::physics::box2d::Joint::M_jniGetAnchorB_Array1_float(jlong addr, const jarray &anchorB_object) {
	auto anchorB = (jfloat *)anchorB_object->data;

		b2Joint* joint = (b2Joint*)addr;
		b2Vec2 a = joint->GetAnchorB();
		anchorB[0] = a.x;
		anchorB[1] = a.y;
}

jbool com::badlogic::gdx::physics::box2d::Joint::M_jniGetCollideConnected_R_boolean(jlong addr) {

		b2Joint* joint = (b2Joint*) addr;
		return joint->GetCollideConnected();
}

void com::badlogic::gdx::physics::box2d::Joint::M_jniGetReactionForce_Array1_float(jlong addr, jfloat inv_dt, const jarray &reactionForce_object) {
	auto reactionForce = (jfloat *)reactionForce_object->data;

		b2Joint* joint = (b2Joint*)addr;
		b2Vec2 f = joint->GetReactionForce(inv_dt);
		reactionForce[0] = f.x;
		reactionForce[1] = f.y;
}

jfloat com::badlogic::gdx::physics::box2d::Joint::M_jniGetReactionTorque_R_float(jlong addr, jfloat inv_dt) {

		b2Joint* joint = (b2Joint*)addr;
		return joint->GetReactionTorque(inv_dt);
}

jbool com::badlogic::gdx::physics::box2d::Joint::M_jniIsActive_R_boolean(jlong addr) {

		b2Joint* joint = (b2Joint*)addr;
		return joint->IsActive();
}

