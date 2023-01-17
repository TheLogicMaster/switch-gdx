#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/WheelJoint.hpp>

#include <Box2D/Box2D.h> 
	 
void com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetLocalAnchorA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2WheelJoint* joint = (b2WheelJoint*)addr;
		anchor[0] = joint->GetLocalAnchorA().x;
		anchor[1] = joint->GetLocalAnchorA().y;
}

void com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetLocalAnchorB_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2WheelJoint* joint = (b2WheelJoint*)addr;
		anchor[0] = joint->GetLocalAnchorB().x;
		anchor[1] = joint->GetLocalAnchorB().y;
}

void com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetLocalAxisA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2WheelJoint* joint = (b2WheelJoint*)addr;
		anchor[0] = joint->GetLocalAxisA().x;
		anchor[1] = joint->GetLocalAxisA().y;
}

jfloat com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetJointTranslation_R_float(jlong addr) {

	  	b2WheelJoint* joint = (b2WheelJoint*)addr;
		return joint->GetJointTranslation();
}

jfloat com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetJointSpeed_R_float(jlong addr) {

	  	b2WheelJoint* joint = (b2WheelJoint*)addr;
		return joint->GetJointSpeed();
}

jbool com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniIsMotorEnabled_R_boolean(jlong addr) {

	  	b2WheelJoint* joint = (b2WheelJoint*)addr;
		return joint->IsMotorEnabled();
}

void com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniEnableMotor(jlong addr, jbool flag) {

	  	b2WheelJoint* joint = (b2WheelJoint*)addr;
		joint->EnableMotor(flag);
}

void com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniSetMotorSpeed(jlong addr, jfloat speed) {

	  	b2WheelJoint* joint = (b2WheelJoint*)addr;
		joint->SetMotorSpeed(speed);
}

jfloat com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetMotorSpeed_R_float(jlong addr) {

	  	b2WheelJoint* joint = (b2WheelJoint*)addr;
		return joint->GetMotorSpeed();
}

void com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniSetMaxMotorTorque(jlong addr, jfloat torque) {

	  	b2WheelJoint* joint = (b2WheelJoint*)addr;
		joint->SetMaxMotorTorque(torque);
}

jfloat com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetMaxMotorTorque_R_float(jlong addr) {

		b2WheelJoint* joint = (b2WheelJoint*)addr;
		return joint->GetMaxMotorTorque();
}

jfloat com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetMotorTorque_R_float(jlong addr, jfloat invDt) {

	  	b2WheelJoint* joint = (b2WheelJoint*)addr;
		return joint->GetMotorTorque(invDt);
}

void com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniSetSpringFrequencyHz(jlong addr, jfloat hz) {

		b2WheelJoint* joint = (b2WheelJoint*)addr;
		joint->SetSpringFrequencyHz(hz);
}

jfloat com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetSpringFrequencyHz_R_float(jlong addr) {

		b2WheelJoint* joint = (b2WheelJoint*)addr;
		return joint->GetSpringFrequencyHz();
}

void com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniSetSpringDampingRatio(jlong addr, jfloat ratio) {

		b2WheelJoint* joint = (b2WheelJoint*)addr;
		joint->SetSpringDampingRatio(ratio);
}

jfloat com::badlogic::gdx::physics::box2d::joints::WheelJoint::M_jniGetSpringDampingRatio_R_float(jlong addr) {

		b2WheelJoint* joint = (b2WheelJoint*)addr;
		return joint->GetSpringDampingRatio();
}

