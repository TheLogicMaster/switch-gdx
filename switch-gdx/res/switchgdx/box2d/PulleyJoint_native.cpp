#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/PulleyJoint.hpp>

#include <Box2D/Box2D.h> 
	 
void com::badlogic::gdx::physics::box2d::joints::PulleyJoint::M_jniGetGroundAnchorA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2PulleyJoint* joint = (b2PulleyJoint*)addr;
		anchor[0] = joint->GetGroundAnchorA().x;
		anchor[1] = joint->GetGroundAnchorA().y;
}

void com::badlogic::gdx::physics::box2d::joints::PulleyJoint::M_jniGetGroundAnchorB_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2PulleyJoint* joint = (b2PulleyJoint*)addr;
		anchor[0] = joint->GetGroundAnchorB().x;
		anchor[1] = joint->GetGroundAnchorB().y;
}

jfloat com::badlogic::gdx::physics::box2d::joints::PulleyJoint::M_jniGetLength1_R_float(jlong addr) {

		b2PulleyJoint* joint = (b2PulleyJoint*)addr;
		return joint->GetLengthA();
}

jfloat com::badlogic::gdx::physics::box2d::joints::PulleyJoint::M_jniGetLength2_R_float(jlong addr) {

		b2PulleyJoint* joint = (b2PulleyJoint*)addr;
		return joint->GetLengthB();
}

jfloat com::badlogic::gdx::physics::box2d::joints::PulleyJoint::M_jniGetRatio_R_float(jlong addr) {

		b2PulleyJoint* joint = (b2PulleyJoint*)addr;
		return joint->GetRatio();
}

