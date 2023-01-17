#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/Fixture.hpp>

#include <Box2D/Box2D.h>
	 
jint com::badlogic::gdx::physics::box2d::Fixture::M_jniGetType_R_int(jlong addr) {

		b2Fixture* fixture = (b2Fixture*)addr;
		b2Shape::Type type = fixture->GetType();
		switch( type )
		{
		case b2Shape::e_circle: return 0;
		case b2Shape::e_edge: return 1;
		case b2Shape::e_polygon: return 2;
		case b2Shape::e_chain: return 3;
		default:
			return -1;
		}
}

jlong com::badlogic::gdx::physics::box2d::Fixture::M_jniGetShape_R_long(jlong addr) {

		b2Fixture* fixture = (b2Fixture*)addr;
		return (jlong)fixture->GetShape();
}

void com::badlogic::gdx::physics::box2d::Fixture::M_jniSetSensor(jlong addr, jbool sensor) {

		b2Fixture* fixture = (b2Fixture*)addr;
		fixture->SetSensor(sensor);
}

jbool com::badlogic::gdx::physics::box2d::Fixture::M_jniIsSensor_R_boolean(jlong addr) {

		b2Fixture* fixture = (b2Fixture*)addr;
		return fixture->IsSensor();
}

void com::badlogic::gdx::physics::box2d::Fixture::M_jniSetFilterData(jlong addr, jshort categoryBits, jshort maskBits, jshort groupIndex) {

		b2Fixture* fixture = (b2Fixture*)addr;
		b2Filter filter;
		filter.categoryBits = categoryBits;
		filter.maskBits = maskBits;
		filter.groupIndex = groupIndex;
		fixture->SetFilterData(filter);
}

void com::badlogic::gdx::physics::box2d::Fixture::M_jniGetFilterData_Array1_short(jlong addr, const jarray &filter_object) {
	auto filter = (jshort *)filter_object->data;

		b2Fixture* fixture = (b2Fixture*)addr;
		unsigned short* filterOut = (unsigned short*)filter;
		b2Filter f = fixture->GetFilterData();
		filterOut[0] = f.maskBits;
		filterOut[1] = f.categoryBits;
		filterOut[2] = f.groupIndex;
}

void com::badlogic::gdx::physics::box2d::Fixture::M_jniRefilter(jlong addr) {

		b2Fixture* fixture = (b2Fixture*)addr;
		fixture->Refilter();
}

jbool com::badlogic::gdx::physics::box2d::Fixture::M_jniTestPoint_R_boolean(jlong addr, jfloat x, jfloat y) {

		b2Fixture* fixture = (b2Fixture*)addr;
		return fixture->TestPoint( b2Vec2( x, y ) );
}

void com::badlogic::gdx::physics::box2d::Fixture::M_jniSetDensity(jlong addr, jfloat density) {

		b2Fixture* fixture = (b2Fixture*)addr;
		fixture->SetDensity(density);
}

jfloat com::badlogic::gdx::physics::box2d::Fixture::M_jniGetDensity_R_float(jlong addr) {

		b2Fixture* fixture = (b2Fixture*)addr;
		return fixture->GetDensity();
}

jfloat com::badlogic::gdx::physics::box2d::Fixture::M_jniGetFriction_R_float(jlong addr) {

		b2Fixture* fixture = (b2Fixture*)addr;
		return fixture->GetFriction();
}

void com::badlogic::gdx::physics::box2d::Fixture::M_jniSetFriction(jlong addr, jfloat friction) {

		b2Fixture* fixture = (b2Fixture*)addr;
		fixture->SetFriction(friction);
}

jfloat com::badlogic::gdx::physics::box2d::Fixture::M_jniGetRestitution_R_float(jlong addr) {

		b2Fixture* fixture = (b2Fixture*)addr;
		return fixture->GetRestitution();
}

void com::badlogic::gdx::physics::box2d::Fixture::M_jniSetRestitution(jlong addr, jfloat restitution) {

		b2Fixture* fixture = (b2Fixture*)addr;
		fixture->SetRestitution(restitution);
}

