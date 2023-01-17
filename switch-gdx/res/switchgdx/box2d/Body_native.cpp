#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/Body.hpp>

#include <Box2D/Box2D.h>
	 
jlong com::badlogic::gdx::physics::box2d::Body::M_jniCreateFixture_R_long(jlong addr, jlong shapeAddr, jfloat friction, jfloat restitution, jfloat density, jbool isSensor, jshort filterCategoryBits, jshort filterMaskBits, jshort filterGroupIndex) {

	b2Body* body = (b2Body*)addr;
	b2Shape* shape = (b2Shape*)shapeAddr;
	b2FixtureDef fixtureDef;

	fixtureDef.shape = shape;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.density = density;
	fixtureDef.isSensor = isSensor;
	fixtureDef.filter.maskBits = filterMaskBits;
	fixtureDef.filter.categoryBits = filterCategoryBits;
	fixtureDef.filter.groupIndex = filterGroupIndex;

	return (jlong)body->CreateFixture( &fixtureDef );
}

jlong com::badlogic::gdx::physics::box2d::Body::M_jniCreateFixture_R_long(jlong addr, jlong shapeAddr, jfloat density) {

		b2Body* body = (b2Body*)addr;
		b2Shape* shape = (b2Shape*)shapeAddr;
		return (jlong)body->CreateFixture( shape, density );
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetTransform(jlong addr, jfloat positionX, jfloat positionY, jfloat angle) {

		b2Body* body = (b2Body*)addr;
		body->SetTransform(b2Vec2(positionX, positionY), angle);
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetTransform_Array1_float(jlong addr, const jarray &vals_object) {
	auto vals = (jfloat *)vals_object->data;

		b2Body* body = (b2Body*)addr;
		b2Transform t = body->GetTransform();
		vals[0] = t.p.x;
		vals[1] = t.p.y;
		vals[2] = t.q.c;
		vals[3] = t.q.s;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetPosition_Array1_float(jlong addr, const jarray &position_object) {
	auto position = (jfloat *)position_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 p = body->GetPosition();
		position[0] = p.x;
		position[1] = p.y;
}

jfloat com::badlogic::gdx::physics::box2d::Body::M_jniGetAngle_R_float(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->GetAngle();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetWorldCenter_Array1_float(jlong addr, const jarray &worldCenter_object) {
	auto worldCenter = (jfloat *)worldCenter_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 w = body->GetWorldCenter();
		worldCenter[0] = w.x;
		worldCenter[1] = w.y;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetLocalCenter_Array1_float(jlong addr, const jarray &localCenter_object) {
	auto localCenter = (jfloat *)localCenter_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 w = body->GetLocalCenter();
		localCenter[0] = w.x;
		localCenter[1] = w.y;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetLinearVelocity(jlong addr, jfloat x, jfloat y) {

		b2Body* body = (b2Body*)addr;
		body->SetLinearVelocity(b2Vec2(x, y));
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetLinearVelocity_Array1_float(jlong addr, const jarray &linearVelocity_object) {
	auto linearVelocity = (jfloat *)linearVelocity_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 l = body->GetLinearVelocity();
		linearVelocity[0] = l.x;
		linearVelocity[1] = l.y;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetAngularVelocity(jlong addr, jfloat omega) {

		b2Body* body = (b2Body*)addr;
		body->SetAngularVelocity(omega);
}

jfloat com::badlogic::gdx::physics::box2d::Body::M_jniGetAngularVelocity_R_float(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->GetAngularVelocity();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniApplyForce(jlong addr, jfloat forceX, jfloat forceY, jfloat pointX, jfloat pointY, jbool wake) {

		b2Body* body = (b2Body*)addr;
		body->ApplyForce(b2Vec2(forceX, forceY), b2Vec2(pointX, pointY), wake);
}

void com::badlogic::gdx::physics::box2d::Body::M_jniApplyForceToCenter(jlong addr, jfloat forceX, jfloat forceY, jbool wake) {

		b2Body* body = (b2Body*)addr;
		body->ApplyForceToCenter(b2Vec2(forceX, forceY), wake);
}

void com::badlogic::gdx::physics::box2d::Body::M_jniApplyTorque(jlong addr, jfloat torque, jbool wake) {

		b2Body* body = (b2Body*)addr;
		body->ApplyTorque(torque, wake);
}

void com::badlogic::gdx::physics::box2d::Body::M_jniApplyLinearImpulse(jlong addr, jfloat impulseX, jfloat impulseY, jfloat pointX, jfloat pointY, jbool wake) {

		b2Body* body = (b2Body*)addr;
		body->ApplyLinearImpulse( b2Vec2( impulseX, impulseY ), b2Vec2( pointX, pointY ), wake);
}

void com::badlogic::gdx::physics::box2d::Body::M_jniApplyAngularImpulse(jlong addr, jfloat impulse, jbool wake) {

		b2Body* body = (b2Body*)addr;
		body->ApplyAngularImpulse(impulse, wake);
}

jfloat com::badlogic::gdx::physics::box2d::Body::M_jniGetMass_R_float(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->GetMass();
}

jfloat com::badlogic::gdx::physics::box2d::Body::M_jniGetInertia_R_float(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->GetInertia();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetMassData_Array1_float(jlong addr, const jarray &massData_object) {
	auto massData = (jfloat *)massData_object->data;

		b2Body* body = (b2Body*)addr;
		b2MassData m;
		body->GetMassData(&m);
		massData[0] = m.mass;
		massData[1] = m.center.x;
		massData[2] = m.center.y;
		massData[3] = m.I;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetMassData(jlong addr, jfloat mass, jfloat centerX, jfloat centerY, jfloat I) {

		b2Body* body = (b2Body*)addr;
		b2MassData m;
		m.mass = mass;
		m.center.x = centerX;
		m.center.y = centerY;
		m.I = I;
		body->SetMassData(&m);
}

void com::badlogic::gdx::physics::box2d::Body::M_jniResetMassData(jlong addr) {

		b2Body* body = (b2Body*)addr;
		body->ResetMassData();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetWorldPoint_Array1_float(jlong addr, jfloat localPointX, jfloat localPointY, const jarray &worldPoint_object) {
	auto worldPoint = (jfloat *)worldPoint_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 w = body->GetWorldPoint( b2Vec2( localPointX, localPointY ) );
		worldPoint[0] = w.x;
		worldPoint[1] = w.y;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetWorldVector_Array1_float(jlong addr, jfloat localVectorX, jfloat localVectorY, const jarray &worldVector_object) {
	auto worldVector = (jfloat *)worldVector_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 w = body->GetWorldVector( b2Vec2( localVectorX, localVectorY ) );
		worldVector[0] = w.x;
		worldVector[1] = w.y;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetLocalPoint_Array1_float(jlong addr, jfloat worldPointX, jfloat worldPointY, const jarray &localPoint_object) {
	auto localPoint = (jfloat *)localPoint_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 w = body->GetLocalPoint( b2Vec2( worldPointX, worldPointY ) );
		localPoint[0] = w.x;
		localPoint[1] = w.y;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetLocalVector_Array1_float(jlong addr, jfloat worldVectorX, jfloat worldVectorY, const jarray &worldVector_object) {
	auto worldVector = (jfloat *)worldVector_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 w = body->GetLocalVector( b2Vec2( worldVectorX, worldVectorY ) );
		worldVector[0] = w.x;
		worldVector[1] = w.y;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetLinearVelocityFromWorldPoint_Array1_float(jlong addr, jfloat worldPointX, jfloat worldPointY, const jarray &linVelWorld_object) {
	auto linVelWorld = (jfloat *)linVelWorld_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 w = body->GetLinearVelocityFromWorldPoint( b2Vec2( worldPointX, worldPointY ) );
		linVelWorld[0] = w.x;
		linVelWorld[1] = w.y;
}

void com::badlogic::gdx::physics::box2d::Body::M_jniGetLinearVelocityFromLocalPoint_Array1_float(jlong addr, jfloat localPointX, jfloat localPointY, const jarray &linVelLoc_object) {
	auto linVelLoc = (jfloat *)linVelLoc_object->data;

		b2Body* body = (b2Body*)addr;
		b2Vec2 w = body->GetLinearVelocityFromLocalPoint( b2Vec2( localPointX, localPointY ) );
		linVelLoc[0] = w.x;
		linVelLoc[1] = w.y;
}

jfloat com::badlogic::gdx::physics::box2d::Body::M_jniGetLinearDamping_R_float(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->GetLinearDamping();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetLinearDamping(jlong addr, jfloat linearDamping) {

		b2Body* body = (b2Body*)addr;
		body->SetLinearDamping(linearDamping);
}

jfloat com::badlogic::gdx::physics::box2d::Body::M_jniGetAngularDamping_R_float(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->GetAngularDamping();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetAngularDamping(jlong addr, jfloat angularDamping) {

		b2Body* body = (b2Body*)addr;
		body->SetAngularDamping(angularDamping);
}


inline b2BodyType getBodyType( int type )
{
	switch( type )
	{
	case 0: return b2_staticBody;
	case 1: return b2_kinematicBody;
	case 2: return b2_dynamicBody;
	default:
		return b2_staticBody;
	}
}	 

void com::badlogic::gdx::physics::box2d::Body::M_jniSetType(jlong addr, jint type) {

		b2Body* body = (b2Body*)addr;
		body->SetType(getBodyType(type));
}

jint com::badlogic::gdx::physics::box2d::Body::M_jniGetType_R_int(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->GetType();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetBullet(jlong addr, jbool flag) {

		b2Body* body = (b2Body*)addr;
		body->SetBullet(flag);
}

jbool com::badlogic::gdx::physics::box2d::Body::M_jniIsBullet_R_boolean(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->IsBullet();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetSleepingAllowed(jlong addr, jbool flag) {

		b2Body* body = (b2Body*)addr;
		body->SetSleepingAllowed(flag);
}

jbool com::badlogic::gdx::physics::box2d::Body::M_jniIsSleepingAllowed_R_boolean(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->IsSleepingAllowed();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetAwake(jlong addr, jbool flag) {

		b2Body* body = (b2Body*)addr;
		body->SetAwake(flag);
}

jbool com::badlogic::gdx::physics::box2d::Body::M_jniIsAwake_R_boolean(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->IsAwake();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetActive(jlong addr, jbool flag) {

		b2Body* body = (b2Body*)addr;
		body->SetActive(flag);
}

jbool com::badlogic::gdx::physics::box2d::Body::M_jniIsActive_R_boolean(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->IsActive();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetFixedRotation(jlong addr, jbool flag) {

		b2Body* body = (b2Body*)addr;
		body->SetFixedRotation(flag);
}

jbool com::badlogic::gdx::physics::box2d::Body::M_jniIsFixedRotation_R_boolean(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->IsFixedRotation();
}

jfloat com::badlogic::gdx::physics::box2d::Body::M_jniGetGravityScale_R_float(jlong addr) {

		b2Body* body = (b2Body*)addr;
		return body->GetGravityScale();
}

void com::badlogic::gdx::physics::box2d::Body::M_jniSetGravityScale(jlong addr, jfloat scale) {

		b2Body* body = (b2Body*)addr;
		body->SetGravityScale(scale);
}
