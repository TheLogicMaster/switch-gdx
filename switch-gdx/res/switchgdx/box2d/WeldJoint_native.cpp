#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/WeldJoint.hpp>

		#include <Box2D/Box2D.h>
	 
void com::badlogic::gdx::physics::box2d::joints::WeldJoint::M_jniGetLocalAnchorA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2WeldJoint* joint = (b2WeldJoint*)addr;
		anchor[0] = joint->GetLocalAnchorA().x;
		anchor[1] = joint->GetLocalAnchorA().y;
}

void com::badlogic::gdx::physics::box2d::joints::WeldJoint::M_jniGetLocalAnchorB_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2WeldJoint* joint = (b2WeldJoint*)addr;
		anchor[0] = joint->GetLocalAnchorB().x;
		anchor[1] = joint->GetLocalAnchorB().y;
}

jfloat com::badlogic::gdx::physics::box2d::joints::WeldJoint::M_jniGetReferenceAngle_R_float(jlong addr) {

		b2WeldJoint* joint = (b2WeldJoint*)addr;
		return joint->GetReferenceAngle();
}

jfloat com::badlogic::gdx::physics::box2d::joints::WeldJoint::M_jniGetFrequency_R_float(jlong addr) {

		b2WeldJoint* joint = (b2WeldJoint*)addr;
		return joint->GetFrequency();
}

void com::badlogic::gdx::physics::box2d::joints::WeldJoint::M_jniSetFrequency(jlong addr, jfloat hz) {

		b2WeldJoint* joint = (b2WeldJoint*)addr;
		joint->SetFrequency(hz);
}

jfloat com::badlogic::gdx::physics::box2d::joints::WeldJoint::M_jniGetDampingRatio_R_float(jlong addr) {

		b2WeldJoint* joint = (b2WeldJoint*)addr;
		return joint->GetDampingRatio();
}

void com::badlogic::gdx::physics::box2d::joints::WeldJoint::M_jniSetDampingRatio(jlong addr, jfloat ratio) {

		b2WeldJoint* joint = (b2WeldJoint*)addr;
		joint->SetDampingRatio(ratio);
}

