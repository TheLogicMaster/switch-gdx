#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/joints/MotorJoint.hpp>

#include <Box2D/Box2D.h>
	 
void com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniGetLinearOffset_Array1_float(jlong addr, const jarray &linearOffset_object) {
	auto linearOffset = (jfloat *)linearOffset_object->data;

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		linearOffset[0] = joint->GetLinearOffset().x;
		linearOffset[1] = joint->GetLinearOffset().y;
}

void com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniSetLinearOffset(jlong addr, jfloat linearOffsetX, jfloat linearOffsetY) {

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		joint->SetLinearOffset(b2Vec2(linearOffsetX, linearOffsetY));
}

jfloat com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniGetAngularOffset_R_float(jlong addr) {

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		return joint->GetAngularOffset();
}

void com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniSetAngularOffset(jlong addr, jfloat angularOffset) {

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		joint->SetAngularOffset(angularOffset);
}

jfloat com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniGetMaxForce_R_float(jlong addr) {

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		return joint->GetMaxForce();
}

void com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniSetMaxForce(jlong addr, jfloat maxForce) {

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		joint->SetMaxForce(maxForce);
}

jfloat com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniGetMaxTorque_R_float(jlong addr) {

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		return joint->GetMaxTorque();
}

void com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniSetMaxTorque(jlong addr, jfloat maxTorque) {

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		joint->SetMaxTorque(maxTorque);
}

jfloat com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniGetCorrectionFactor_R_float(jlong addr) {

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		return joint->GetCorrectionFactor();
}

void com::badlogic::gdx::physics::box2d::joints::MotorJoint::M_jniSetCorrectionFactor(jlong addr, jfloat correctionFactor) {

		b2MotorJoint* joint = (b2MotorJoint*)addr;
		joint->SetCorrectionFactor(correctionFactor);
}

