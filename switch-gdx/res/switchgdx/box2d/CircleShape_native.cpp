#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/physics/box2d/CircleShape.hpp>

#include <Box2D/Box2D.h>
	 
jlong com::badlogic::gdx::physics::box2d::CircleShape::M_newCircleShape_R_long() {

		return (jlong)(new b2CircleShape( ));
}

void com::badlogic::gdx::physics::box2d::CircleShape::M_jniGetPosition_Array1_float(jlong addr, const jarray &position_object) {
	auto position = (jfloat *)position_object->data;

		b2CircleShape* circle = (b2CircleShape*)addr;
		position[0] = circle->m_p.x;
		position[1] = circle->m_p.y;
}

void com::badlogic::gdx::physics::box2d::CircleShape::M_jniSetPosition(jlong addr, jfloat positionX, jfloat positionY) {

		b2CircleShape* circle = (b2CircleShape*)addr;
		circle->m_p.x = positionX;
		circle->m_p.y = positionY;
}

