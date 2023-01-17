#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/GearJoint.hpp>

#include <Box2D/Box2D.h> 
	 
jlong com::badlogic::gdx::physics::box2d::joints::GearJoint::M_jniGetJoint1_R_long(jlong addr) {

		b2GearJoint* joint =  (b2GearJoint*)addr;
		b2Joint* joint1 = joint->GetJoint1();
		return (jlong)joint1;
}

jlong com::badlogic::gdx::physics::box2d::joints::GearJoint::M_jniGetJoint2_R_long(jlong addr) {

		b2GearJoint* joint =  (b2GearJoint*)addr;
		b2Joint* joint2 = joint->GetJoint2();
		return (jlong)joint2;
}

void com::badlogic::gdx::physics::box2d::joints::GearJoint::M_jniSetRatio(jlong addr, jfloat ratio) {

		b2GearJoint* joint =  (b2GearJoint*)addr;
		joint->SetRatio( ratio );
}

jfloat com::badlogic::gdx::physics::box2d::joints::GearJoint::M_jniGetRatio_R_float(jlong addr) {

		b2GearJoint* joint =  (b2GearJoint*)addr;
		return joint->GetRatio();
}

