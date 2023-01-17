#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/DistanceJoint.hpp>

#include <Box2D/Box2D.h>
	 
void com::badlogic::gdx::physics::box2d::joints::DistanceJoint::M_jniGetLocalAnchorA_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2DistanceJoint* joint = (b2DistanceJoint*)addr;
		anchor[0] = joint->GetLocalAnchorA().x;
		anchor[1] = joint->GetLocalAnchorA().y;
}

void com::badlogic::gdx::physics::box2d::joints::DistanceJoint::M_jniGetLocalAnchorB_Array1_float(jlong addr, const jarray &anchor_object) {
	auto anchor = (jfloat *)anchor_object->data;

		b2DistanceJoint* joint = (b2DistanceJoint*)addr;
		anchor[0] = joint->GetLocalAnchorB().x;
		anchor[1] = joint->GetLocalAnchorB().y;
}

void com::badlogic::gdx::physics::box2d::joints::DistanceJoint::M_jniSetLength(jlong addr, jfloat length) {

		b2DistanceJoint* joint = (b2DistanceJoint*)addr;
		joint->SetLength( length );
}

jfloat com::badlogic::gdx::physics::box2d::joints::DistanceJoint::M_jniGetLength_R_float(jlong addr) {

		b2DistanceJoint* joint = (b2DistanceJoint*)addr;
		return joint->GetLength();
}

void com::badlogic::gdx::physics::box2d::joints::DistanceJoint::M_jniSetFrequency(jlong addr, jfloat hz) {

		b2DistanceJoint* joint = (b2DistanceJoint*)addr;
		joint->SetFrequency( hz );
}

jfloat com::badlogic::gdx::physics::box2d::joints::DistanceJoint::M_jniGetFrequency_R_float(jlong addr) {

		b2DistanceJoint* joint = (b2DistanceJoint*)addr;
		return joint->GetFrequency();
}

void com::badlogic::gdx::physics::box2d::joints::DistanceJoint::M_jniSetDampingRatio(jlong addr, jfloat ratio) {

		b2DistanceJoint* joint = (b2DistanceJoint*)addr;
		joint->SetDampingRatio( ratio );
}

jfloat com::badlogic::gdx::physics::box2d::joints::DistanceJoint::M_jniGetDampingRatio_R_float(jlong addr) {

		b2DistanceJoint* joint = (b2DistanceJoint*)addr;
		return joint->GetDampingRatio();
}

