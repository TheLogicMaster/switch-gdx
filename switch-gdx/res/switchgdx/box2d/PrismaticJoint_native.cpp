#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/PrismaticJoint.hpp>

#include <Box2D/Box2D.h>
	 
void com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetLocalAnchorA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		anchor[0] = joint->GetLocalAnchorA().x;
		anchor[1] = joint->GetLocalAnchorA().y;
}

void com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetLocalAnchorB_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		anchor[0] = joint->GetLocalAnchorB().x;
		anchor[1] = joint->GetLocalAnchorB().y;
}

void com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetLocalAxisA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		anchor[0] = joint->GetLocalAxisA().x;
		anchor[1] = joint->GetLocalAxisA().y;
}

jfloat com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetJointTranslation_R_float(jlong addr) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->GetJointTranslation();
}

jfloat com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetJointSpeed_R_float(jlong addr) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->GetJointSpeed();
}

jbool com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniIsLimitEnabled_R_boolean(jlong addr) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->IsLimitEnabled();
}

void com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniEnableLimit(jlong addr, jbool flag) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		joint->EnableLimit(flag);
}

jfloat com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetLowerLimit_R_float(jlong addr) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->GetLowerLimit();
}

jfloat com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetUpperLimit_R_float(jlong addr) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->GetUpperLimit();
}

void com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniSetLimits(jlong addr, jfloat lower, jfloat upper) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		joint->SetLimits(lower, upper );
}

jbool com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniIsMotorEnabled_R_boolean(jlong addr) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->IsMotorEnabled();
}

void com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniEnableMotor(jlong addr, jbool flag) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		joint->EnableMotor(flag);
}

void com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniSetMotorSpeed(jlong addr, jfloat speed) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		joint->SetMotorSpeed(speed);
}

jfloat com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetMotorSpeed_R_float(jlong addr) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->GetMotorSpeed();
}

void com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniSetMaxMotorForce(jlong addr, jfloat force) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		joint->SetMaxMotorForce(force);
}

jfloat com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetMotorForce_R_float(jlong addr, jfloat invDt) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->GetMotorForce(invDt);
}

jfloat com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetMaxMotorForce_R_float(jlong addr) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->GetMaxMotorForce();
}

jfloat com::badlogic::gdx::physics::box2d::joints::PrismaticJoint::M_jniGetReferenceAngle_R_float(jlong addr) {

		b2PrismaticJoint* joint = (b2PrismaticJoint*)addr;
		return joint->GetReferenceAngle();
}

