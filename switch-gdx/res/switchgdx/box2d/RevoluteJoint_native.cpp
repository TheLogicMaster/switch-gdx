#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/RevoluteJoint.hpp>

#include <Box2D/Box2D.h> 
	 
jfloat com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetJointAngle_R_float(jlong addr) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->GetJointAngle();
}

jfloat com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetJointSpeed_R_float(jlong addr) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->GetJointSpeed();
}

jbool com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniIsLimitEnabled_R_boolean(jlong addr) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->IsLimitEnabled();
}

void com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniEnableLimit(jlong addr, jbool flag) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		joint->EnableLimit(flag);
}

jfloat com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetLowerLimit_R_float(jlong addr) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->GetLowerLimit();
}

jfloat com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetUpperLimit_R_float(jlong addr) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->GetUpperLimit();
}

void com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniSetLimits(jlong addr, jfloat lower, jfloat upper) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		joint->SetLimits(lower, upper );
}

jbool com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniIsMotorEnabled_R_boolean(jlong addr) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->IsMotorEnabled();
}

void com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniEnableMotor(jlong addr, jbool flag) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		joint->EnableMotor(flag);
}

void com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniSetMotorSpeed(jlong addr, jfloat speed) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		joint->SetMotorSpeed(speed);
}

jfloat com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetMotorSpeed_R_float(jlong addr) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->GetMotorSpeed();
}

void com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniSetMaxMotorTorque(jlong addr, jfloat torque) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		joint->SetMaxMotorTorque(torque);
}

jfloat com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetMotorTorque_R_float(jlong addr, jfloat invDt) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->GetMotorTorque(invDt);
}

void com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetLocalAnchorA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		anchor[0] = joint->GetLocalAnchorA().x;
		anchor[1] = joint->GetLocalAnchorA().y;
}

void com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetLocalAnchorB_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		anchor[0] = joint->GetLocalAnchorB().x;
		anchor[1] = joint->GetLocalAnchorB().y;
}

jfloat com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetReferenceAngle_R_float(jlong addr) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->GetReferenceAngle();
}

jfloat com::badlogic::gdx::physics::box2d::joints::RevoluteJoint::M_jniGetMaxMotorTorque_R_float(jlong addr) {

		b2RevoluteJoint* joint = (b2RevoluteJoint*)addr;
		return joint->GetMaxMotorTorque();
}

