#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/RopeJoint.hpp>

#include <Box2D/Box2D.h>
	 
void com::badlogic::gdx::physics::box2d::joints::RopeJoint::M_jniGetLocalAnchorA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2RopeJoint* joint = (b2RopeJoint*)addr;
		anchor[0] = joint->GetLocalAnchorA().x;
		anchor[1] = joint->GetLocalAnchorA().y;
}

void com::badlogic::gdx::physics::box2d::joints::RopeJoint::M_jniGetLocalAnchorB_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2RopeJoint* joint = (b2RopeJoint*)addr;
		anchor[0] = joint->GetLocalAnchorB().x;
		anchor[1] = joint->GetLocalAnchorB().y;
}

jfloat com::badlogic::gdx::physics::box2d::joints::RopeJoint::M_jniGetMaxLength_R_float(jlong addr) {

		b2RopeJoint* rope = (b2RopeJoint*)addr;
		return rope->GetMaxLength();
}

void com::badlogic::gdx::physics::box2d::joints::RopeJoint::M_jniSetMaxLength(jlong addr, jfloat length) {

		b2RopeJoint* rope = (b2RopeJoint*)addr;
		rope->SetMaxLength(length);
}

