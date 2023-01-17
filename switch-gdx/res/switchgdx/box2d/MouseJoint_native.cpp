#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/MouseJoint.hpp>

#include <Box2D/Box2D.h>
	 
void com::badlogic::gdx::physics::box2d::joints::MouseJoint::M_jniSetTarget(jlong addr, jfloat x, jfloat y) {

		b2MouseJoint* joint = (b2MouseJoint*)addr;
		joint->SetTarget( b2Vec2(x, y ) );
}

void com::badlogic::gdx::physics::box2d::joints::MouseJoint::M_jniGetTarget_Array1_float(jlong addr, const jarray &target_object) {
	auto target = (jfloat *)target_object->data;

		b2MouseJoint* joint = (b2MouseJoint*)addr;
		target[0] = joint->GetTarget().x;
		target[1] = joint->GetTarget().y;
}

void com::badlogic::gdx::physics::box2d::joints::MouseJoint::M_jniSetMaxForce(jlong addr, jfloat force) {

		b2MouseJoint* joint = (b2MouseJoint*)addr;
		joint->SetMaxForce( force );
}

jfloat com::badlogic::gdx::physics::box2d::joints::MouseJoint::M_jniGetMaxForce_R_float(jlong addr) {

		b2MouseJoint* joint = (b2MouseJoint*)addr;
		return joint->GetMaxForce();
}

void com::badlogic::gdx::physics::box2d::joints::MouseJoint::M_jniSetFrequency(jlong addr, jfloat hz) {

		b2MouseJoint* joint = (b2MouseJoint*)addr;
		joint->SetFrequency(hz);
}

jfloat com::badlogic::gdx::physics::box2d::joints::MouseJoint::M_jniGetFrequency_R_float(jlong addr) {

		b2MouseJoint* joint = (b2MouseJoint*)addr;
		return joint->GetFrequency();
}

void com::badlogic::gdx::physics::box2d::joints::MouseJoint::M_jniSetDampingRatio(jlong addr, jfloat ratio) {

		b2MouseJoint* joint = (b2MouseJoint*)addr;
		joint->SetDampingRatio( ratio );
}

jfloat com::badlogic::gdx::physics::box2d::joints::MouseJoint::M_jniGetDampingRatio_R_float(jlong addr) {

		b2MouseJoint* joint = (b2MouseJoint*)addr;
		return joint->GetDampingRatio();
}

