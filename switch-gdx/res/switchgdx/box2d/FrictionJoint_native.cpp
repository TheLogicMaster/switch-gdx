#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/FrictionJoint.hpp>

#include <Box2D/Box2D.h> 
	 
void com::badlogic::gdx::physics::box2d::joints::FrictionJoint::M_jniGetLocalAnchorA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2FrictionJoint* joint = (b2FrictionJoint*)addr;
		anchor[0] = joint->GetLocalAnchorA().x;
		anchor[1] = joint->GetLocalAnchorA().y;
}

void com::badlogic::gdx::physics::box2d::joints::FrictionJoint::M_jniGetLocalAnchorB_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2FrictionJoint* joint = (b2FrictionJoint*)addr;
		anchor[0] = joint->GetLocalAnchorB().x;
		anchor[1] = joint->GetLocalAnchorB().y;
}

void com::badlogic::gdx::physics::box2d::joints::FrictionJoint::M_jniSetMaxForce(jlong addr, jfloat force) {

		b2FrictionJoint* joint = (b2FrictionJoint*)addr;
		joint->SetMaxForce( force );
}

jfloat com::badlogic::gdx::physics::box2d::joints::FrictionJoint::M_jniGetMaxForce_R_float(jlong addr) {

		b2FrictionJoint* joint = (b2FrictionJoint*)addr;
		return joint->GetMaxForce();
}

void com::badlogic::gdx::physics::box2d::joints::FrictionJoint::M_jniSetMaxTorque(jlong addr, jfloat torque) {

		b2FrictionJoint* joint = (b2FrictionJoint*)addr;
		joint->SetMaxTorque( torque );
}

jfloat com::badlogic::gdx::physics::box2d::joints::FrictionJoint::M_jniGetMaxTorque_R_float(jlong addr) {

		b2FrictionJoint* joint = (b2FrictionJoint*)addr;
		return joint->GetMaxTorque();
}

