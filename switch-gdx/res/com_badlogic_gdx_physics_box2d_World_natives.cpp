// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
#include "com_badlogic_gdx_physics_box2d_World.h"
}

// @Line: 57

#include <Box2D/Box2D.h>

//static jclass worldClass = 0;
//static jmethodID shouldCollideID = 0;
//static jmethodID beginContactID = 0;
//static jmethodID endContactID = 0;
//static jmethodID preSolveID = 0;
//static jmethodID postSolveID = 0;
//static jmethodID reportFixtureID = 0;
//static jmethodID reportRayFixtureID = 0;

class CustomRayCastCallback : public b2RayCastCallback {
private:
//	JNIEnv* env;
    jobject obj;

public:
    CustomRayCastCallback( /*JNIEnv *env,*/ jobject obj) {
//		this->env = env;
        this->obj = obj;
    }

    virtual float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) {
//		return env->CallFloatMethod(obj, reportRayFixtureID, (jlong)fixture, (jfloat)point.x, (jfloat)point.y, (jfloat)normal.x, (jfloat)normal.y, (jfloat)fraction );
        return com_badlogic_gdx_physics_box2d_World_reportRayFixture___long_float_float_float_float_float_R_float(getThreadLocalData(), obj, (jlong) fixture, (jfloat) point.x, (jfloat) point.y, (jfloat) normal.x, (jfloat) normal.y, (jfloat) fraction);
    }
};

class CustomContactFilter : public b2ContactFilter {
private:
//	JNIEnv* env;
    jobject obj;

public:
    CustomContactFilter( /*JNIEnv* env,*/ jobject obj) {
//		this->env = env;
        this->obj = obj;
    }

    virtual bool ShouldCollide(b2Fixture *fixtureA, b2Fixture *fixtureB) {
//		if( shouldCollideID != 0 )
//            return env->CallBooleanMethod( obj, shouldCollideID, (jlong)fixtureA, (jlong)fixtureB );
//		else
//			return true;
        return com_badlogic_gdx_physics_box2d_World_contactFilter___long_long_R_boolean(getThreadLocalData(), obj, (jlong) fixtureA, (jlong) fixtureB);
    }
};

class CustomContactListener : public b2ContactListener {
private:
//	JNIEnv* env;
    jobject obj;

public:
    CustomContactListener( /*JNIEnv* env,*/ jobject obj) {
//			this->env = env;
        this->obj = obj;
    }

    /// Called when two fixtures begin to touch.
    virtual void BeginContact(b2Contact *contact) {
//			if( beginContactID != 0 )
//				env->CallVoidMethod(obj, beginContactID, (jlong)contact );
        com_badlogic_gdx_physics_box2d_World_beginContact___long(getThreadLocalData(), obj, (jlong) contact);
    }

    /// Called when two fixtures cease to touch.
    virtual void EndContact(b2Contact *contact) {
//			if( endContactID != 0 )
//				env->CallVoidMethod(obj, endContactID, (jlong)contact);
        com_badlogic_gdx_physics_box2d_World_endContact___long(getThreadLocalData(), obj, (jlong) contact);
    }

    /// This is called after a contact is updated.
    virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
//			if( preSolveID != 0 )
//				env->CallVoidMethod(obj, preSolveID, (jlong)contact, (jlong)oldManifold);
        com_badlogic_gdx_physics_box2d_World_preSolve___long_long(getThreadLocalData(), obj, (jlong) contact, (jlong) oldManifold);
    }

    /// This lets you inspect a contact after the solver is finished.
    virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
//			if( postSolveID != 0 )
//				env->CallVoidMethod(obj, postSolveID, (jlong)contact, (jlong)impulse);
        com_badlogic_gdx_physics_box2d_World_postSolve___long_long(getThreadLocalData(), obj, (jlong) contact, (jlong) impulse);
    }
};

class CustomQueryCallback : public b2QueryCallback {
private:
//	JNIEnv* env;
    jobject obj;

public:
    CustomQueryCallback( /*JNIEnv* env,*/ jobject obj) {
//		this->env = env;
        this->obj = obj;
    }

    virtual bool ReportFixture(b2Fixture *fixture) {
//		return env->CallBooleanMethod(obj, reportFixtureID, (jlong)fixture );
        return com_badlogic_gdx_physics_box2d_World_reportFixture___long_R_boolean(getThreadLocalData(), obj, (jlong) fixture);
    }
};

inline b2BodyType getBodyType(int type) {
    switch (type) {
        case 0:
            return b2_staticBody;
        case 1:
            return b2_kinematicBody;
        case 2:
            return b2_dynamicBody;
        default:
            return b2_staticBody;
    }
}

b2ContactFilter defaultFilter;

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_World_newWorld___float_float_boolean_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_FLOAT gravityX, JAVA_FLOAT gravityY, JAVA_BOOLEAN doSleep) {
    // we leak one global ref.
//		if(!worldClass) {
//			worldClass = (jclass)env->NewGlobalRef(env->GetObjectClass(object));
//			beginContactID = env->GetMethodID(worldClass, "beginContact", "(J)V" );
//			endContactID = env->GetMethodID( worldClass, "endContact", "(J)V" );
//			preSolveID = env->GetMethodID( worldClass, "preSolve", "(JJ)V" );
//			postSolveID = env->GetMethodID( worldClass, "postSolve", "(JJ)V" );
//			reportFixtureID = env->GetMethodID(worldClass, "reportFixture", "(J)Z" );
//			reportRayFixtureID = env->GetMethodID(worldClass, "reportRayFixture", "(JFFFFF)F" );
//			shouldCollideID = env->GetMethodID( worldClass, "contactFilter", "(JJ)Z");
//		}

    b2World *world = new b2World(b2Vec2(gravityX, gravityY));
    world->SetAllowSleeping(doSleep);
    return (jlong) world;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_setUseDefaultContactFilter___boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_BOOLEAN use) {
    // FIXME
}

extern "C" JAVA_LONG
com_badlogic_gdx_physics_box2d_World_jniCreateBody___long_int_float_float_float_float_float_float_float_float_boolean_boolean_boolean_boolean_boolean_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_INT type, JAVA_FLOAT positionX, JAVA_FLOAT positionY, JAVA_FLOAT angle, JAVA_FLOAT linearVelocityX, JAVA_FLOAT linearVelocityY, JAVA_FLOAT angularVelocity, JAVA_FLOAT linearDamping, JAVA_FLOAT angularDamping, JAVA_BOOLEAN allowSleep, JAVA_BOOLEAN awake, JAVA_BOOLEAN fixedRotation, JAVA_BOOLEAN bullet, JAVA_BOOLEAN active, JAVA_FLOAT inertiaScale) {
    b2BodyDef bodyDef;
    bodyDef.type = getBodyType(type);
    bodyDef.position.Set(positionX, positionY);
    bodyDef.angle = angle;
    bodyDef.linearVelocity.Set(linearVelocityX, linearVelocityY);
    bodyDef.angularVelocity = angularVelocity;
    bodyDef.linearDamping = linearDamping;
    bodyDef.angularDamping = angularDamping;
    bodyDef.allowSleep = allowSleep;
    bodyDef.awake = awake;
    bodyDef.fixedRotation = fixedRotation;
    bodyDef.bullet = bullet;
    bodyDef.active = active;
    bodyDef.gravityScale = inertiaScale;

    b2World *world = (b2World *) addr;
    b2Body *body = world->CreateBody(&bodyDef);
    return (jlong) body;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniDestroyBody___long_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyAddr) {
    b2World *world = (b2World *) addr;
    b2Body *body = (b2Body *) bodyAddr;
    CustomContactFilter contactFilter(/*env,*/ object);
    CustomContactListener contactListener(/*env,*/ object);
    world->SetContactFilter(&contactFilter);
    world->SetContactListener(&contactListener);
    world->DestroyBody(body);
    world->SetContactFilter(&defaultFilter);
    world->SetContactListener(0);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniDestroyFixture___long_long_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyAddr, JAVA_LONG fixtureAddr) {
    b2World *world = (b2World *) (addr);
    b2Body *body = (b2Body *) (bodyAddr);
    b2Fixture *fixture = (b2Fixture *) (fixtureAddr);
    CustomContactFilter contactFilter(/*env,*/ object);
    CustomContactListener contactListener(/*env,*/ object);
    world->SetContactFilter(&contactFilter);
    world->SetContactListener(&contactListener);
    body->DestroyFixture(fixture);
    world->SetContactFilter(&defaultFilter);
    world->SetContactListener(0);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniDeactivateBody___long_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyAddr) {
    b2World *world = (b2World *) (addr);
    b2Body *body = (b2Body *) (bodyAddr);
    CustomContactFilter contactFilter(/*env,*/ object);
    CustomContactListener contactListener(/*env,*/ object);
    world->SetContactFilter(&contactFilter);
    world->SetContactListener(&contactListener);
    body->SetActive(false);
    world->SetContactFilter(&defaultFilter);
    world->SetContactListener(0);
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_World_jniCreateWheelJoint___long_long_long_boolean_float_float_float_float_float_float_boolean_float_float_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT localAnchorAX, JAVA_FLOAT localAnchorAY, JAVA_FLOAT localAnchorBX, JAVA_FLOAT localAnchorBY, JAVA_FLOAT localAxisAX, JAVA_FLOAT localAxisAY, JAVA_BOOLEAN enableMotor, JAVA_FLOAT maxMotorTorque, JAVA_FLOAT motorSpeed, JAVA_FLOAT frequencyHz, JAVA_FLOAT dampingRatio) {
    b2World *world = (b2World *) addr;
    b2WheelJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.localAnchorA = b2Vec2(localAnchorAX, localAnchorAY);
    def.localAnchorB = b2Vec2(localAnchorBX, localAnchorBY);
    def.localAxisA = b2Vec2(localAxisAX, localAxisAY);
    def.enableMotor = enableMotor;
    def.maxMotorTorque = maxMotorTorque;
    def.motorSpeed = motorSpeed;
    def.frequencyHz = frequencyHz;
    def.dampingRatio = dampingRatio;

    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG
com_badlogic_gdx_physics_box2d_World_jniCreateRopeJoint___long_long_long_boolean_float_float_float_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT localAnchorAX, JAVA_FLOAT localAnchorAY, JAVA_FLOAT localAnchorBX, JAVA_FLOAT localAnchorBY, JAVA_FLOAT maxLength) {
    b2World *world = (b2World *) addr;
    b2RopeJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.localAnchorA = b2Vec2(localAnchorAX, localAnchorAY);
    def.localAnchorB = b2Vec2(localAnchorBX, localAnchorBY);
    def.maxLength = maxLength;

    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_World_jniCreateDistanceJoint___long_long_long_boolean_float_float_float_float_float_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT localAnchorAX, JAVA_FLOAT localAnchorAY, JAVA_FLOAT localAnchorBX, JAVA_FLOAT localAnchorBY, JAVA_FLOAT length, JAVA_FLOAT frequencyHz, JAVA_FLOAT dampingRatio) {
    b2World *world = (b2World *) addr;
    b2DistanceJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.localAnchorA = b2Vec2(localAnchorAX, localAnchorAY);
    def.localAnchorB = b2Vec2(localAnchorBX, localAnchorBY);
    def.length = length;
    def.frequencyHz = frequencyHz;
    def.dampingRatio = dampingRatio;

    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG
com_badlogic_gdx_physics_box2d_World_jniCreateFrictionJoint___long_long_long_boolean_float_float_float_float_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT localAnchorAX, JAVA_FLOAT localAnchorAY, JAVA_FLOAT localAnchorBX, JAVA_FLOAT localAnchorBY, JAVA_FLOAT maxForce, JAVA_FLOAT maxTorque) {
    b2World *world = (b2World *) addr;
    b2FrictionJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.localAnchorA = b2Vec2(localAnchorAX, localAnchorAY);
    def.localAnchorB = b2Vec2(localAnchorBX, localAnchorBY);
    def.maxForce = maxForce;
    def.maxTorque = maxTorque;
    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_World_jniCreateGearJoint___long_long_long_boolean_long_long_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_LONG joint1, JAVA_LONG joint2, JAVA_FLOAT ratio) {
    b2World *world = (b2World *) addr;
    b2GearJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.joint1 = (b2Joint *) joint1;
    def.joint2 = (b2Joint *) joint2;
    def.ratio = ratio;
    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG
com_badlogic_gdx_physics_box2d_World_jniCreateMotorJoint___long_long_long_boolean_float_float_float_float_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT linearOffsetX, JAVA_FLOAT linearOffsetY, JAVA_FLOAT angularOffset, JAVA_FLOAT maxForce, JAVA_FLOAT maxTorque, JAVA_FLOAT correctionFactor) {
    b2World *world = (b2World *) addr;
    b2MotorJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.linearOffset = b2Vec2(linearOffsetX, linearOffsetY);
    def.angularOffset = angularOffset;
    def.maxForce = maxForce;
    def.maxTorque = maxTorque;
    def.correctionFactor = correctionFactor;
    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG
com_badlogic_gdx_physics_box2d_World_jniCreateMouseJoint___long_long_long_boolean_float_float_float_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT targetX, JAVA_FLOAT targetY, JAVA_FLOAT maxForce, JAVA_FLOAT frequencyHz, JAVA_FLOAT dampingRatio) {
    b2World *world = (b2World *) addr;
    b2MouseJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.target = b2Vec2(targetX, targetY);
    def.maxForce = maxForce;
    def.frequencyHz = frequencyHz;
    def.dampingRatio = dampingRatio;
    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG
com_badlogic_gdx_physics_box2d_World_jniCreatePrismaticJoint___long_long_long_boolean_float_float_float_float_float_float_float_boolean_float_float_boolean_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT localAnchorAX, JAVA_FLOAT localAnchorAY, JAVA_FLOAT localAnchorBX, JAVA_FLOAT localAnchorBY, JAVA_FLOAT localAxisAX, JAVA_FLOAT localAxisAY, JAVA_FLOAT referenceAngle, JAVA_BOOLEAN enableLimit, JAVA_FLOAT lowerTranslation, JAVA_FLOAT upperTranslation, JAVA_BOOLEAN enableMotor, JAVA_FLOAT maxMotorForce, JAVA_FLOAT motorSpeed) {
    b2World *world = (b2World *) addr;
    b2PrismaticJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.localAnchorA = b2Vec2(localAnchorAX, localAnchorAY);
    def.localAnchorB = b2Vec2(localAnchorBX, localAnchorBY);
    def.localAxisA = b2Vec2(localAxisAX, localAxisAY);
    def.referenceAngle = referenceAngle;
    def.enableLimit = enableLimit;
    def.lowerTranslation = lowerTranslation;
    def.upperTranslation = upperTranslation;
    def.enableMotor = enableMotor;
    def.maxMotorForce = maxMotorForce;
    def.motorSpeed = motorSpeed;
    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_World_jniCreatePulleyJoint___long_long_long_boolean_float_float_float_float_float_float_float_float_float_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT groundAnchorAX, JAVA_FLOAT groundAnchorAY, JAVA_FLOAT groundAnchorBX, JAVA_FLOAT groundAnchorBY, JAVA_FLOAT localAnchorAX, JAVA_FLOAT localAnchorAY, JAVA_FLOAT localAnchorBX, JAVA_FLOAT localAnchorBY, JAVA_FLOAT lengthA, JAVA_FLOAT lengthB, JAVA_FLOAT ratio) {
    b2World *world = (b2World *) addr;
    b2PulleyJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.groundAnchorA = b2Vec2(groundAnchorAX, groundAnchorAY);
    def.groundAnchorB = b2Vec2(groundAnchorBX, groundAnchorBY);
    def.localAnchorA = b2Vec2(localAnchorAX, localAnchorAY);
    def.localAnchorB = b2Vec2(localAnchorBX, localAnchorBY);
    def.lengthA = lengthA;
    def.lengthB = lengthB;
    def.ratio = ratio;

    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG
com_badlogic_gdx_physics_box2d_World_jniCreateRevoluteJoint___long_long_long_boolean_float_float_float_float_float_boolean_float_float_boolean_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT localAnchorAX, JAVA_FLOAT localAnchorAY, JAVA_FLOAT localAnchorBX, JAVA_FLOAT localAnchorBY, JAVA_FLOAT referenceAngle, JAVA_BOOLEAN enableLimit, JAVA_FLOAT lowerAngle, JAVA_FLOAT upperAngle, JAVA_BOOLEAN enableMotor, JAVA_FLOAT motorSpeed, JAVA_FLOAT maxMotorTorque) {
    b2World *world = (b2World *) addr;
    b2RevoluteJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.localAnchorA = b2Vec2(localAnchorAX, localAnchorAY);
    def.localAnchorB = b2Vec2(localAnchorBX, localAnchorBY);
    def.referenceAngle = referenceAngle;
    def.enableLimit = enableLimit;
    def.lowerAngle = lowerAngle;
    def.upperAngle = upperAngle;
    def.enableMotor = enableMotor;
    def.motorSpeed = motorSpeed;
    def.maxMotorTorque = maxMotorTorque;
    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_World_jniCreateWeldJoint___long_long_long_boolean_float_float_float_float_float_float_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG bodyA, JAVA_LONG bodyB, JAVA_BOOLEAN collideConnected, JAVA_FLOAT localAnchorAX, JAVA_FLOAT localAnchorAY, JAVA_FLOAT localAnchorBX, JAVA_FLOAT localAnchorBY, JAVA_FLOAT referenceAngle, JAVA_FLOAT frequencyHz, JAVA_FLOAT dampingRatio) {
    b2World *world = (b2World *) addr;
    b2WeldJointDef def;
    def.bodyA = (b2Body *) bodyA;
    def.bodyB = (b2Body *) bodyB;
    def.collideConnected = collideConnected;
    def.localAnchorA = b2Vec2(localAnchorAX, localAnchorAY);
    def.localAnchorB = b2Vec2(localAnchorBX, localAnchorBY);
    def.referenceAngle = referenceAngle;
    def.frequencyHz = frequencyHz;
    def.dampingRatio = dampingRatio;

    return (jlong) world->CreateJoint(&def);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniDestroyJoint___long_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG jointAddr) {
    b2World *world = (b2World *) addr;
    b2Joint *joint = (b2Joint *) jointAddr;
    CustomContactFilter contactFilter(/*env,*/ object);
    CustomContactListener contactListener(/*env,*/ object);
    world->SetContactFilter(&contactFilter);
    world->SetContactListener(&contactListener);
    world->DestroyJoint(joint);
    world->SetContactFilter(&defaultFilter);
    world->SetContactListener(0);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniStep___long_float_int_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT timeStep, JAVA_INT velocityIterations, JAVA_INT positionIterations) {
    b2World *world = (b2World *) addr;
    CustomContactFilter contactFilter(/*env,*/ object);
    CustomContactListener contactListener(/*env,*/ object);
    world->SetContactFilter(&contactFilter);
    world->SetContactListener(&contactListener);
    world->Step(timeStep, velocityIterations, positionIterations);
    world->SetContactFilter(&defaultFilter);
    world->SetContactListener(0);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniClearForces___long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2World *world = (b2World *) addr;
    world->ClearForces();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniSetWarmStarting___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2World *world = (b2World *) addr;
    world->SetWarmStarting(flag);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniSetContiousPhysics___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2World *world = (b2World *) addr;
    world->SetContinuousPhysics(flag);
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_World_jniGetProxyCount___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2World *world = (b2World *) addr;
    return world->GetProxyCount();
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_World_jniGetBodyCount___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2World *world = (b2World *) addr;
    return world->GetBodyCount();
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_World_jniGetJointcount___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2World *world = (b2World *) addr;
    return world->GetJointCount();
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_World_jniGetContactCount___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2World *world = (b2World *) addr;
    return world->GetContactCount();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniSetGravity___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT gravityX, JAVA_FLOAT gravityY) {
    b2World *world = (b2World *) addr;
    world->SetGravity(b2Vec2(gravityX, gravityY));
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniGetGravity___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT gravity__object) {
    auto gravity = (float *) ((JAVA_ARRAY) gravity__object)->data;
    b2World *world = (b2World *) addr;
    b2Vec2 g = world->GetGravity();
    gravity[0] = g.x;
    gravity[1] = g.y;
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_World_jniIsLocked___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2World *world = (b2World *) addr;
    return world->IsLocked();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniSetAutoClearForces___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2World *world = (b2World *) addr;
    world->SetAutoClearForces(flag);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_World_jniGetAutoClearForces___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2World *world = (b2World *) addr;
    return world->GetAutoClearForces();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniQueryAABB___long_float_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT lowX, JAVA_FLOAT lowY, JAVA_FLOAT upX, JAVA_FLOAT upY) {
    b2World *world = (b2World *) addr;
    b2AABB aabb;
    aabb.lowerBound = b2Vec2(lowX, lowY);
    aabb.upperBound = b2Vec2(upX, upY);

    CustomQueryCallback callback( /*env,*/ object);
    world->QueryAABB(&callback, aabb);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniGetContactList___long_long_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT contacts__object) {
    auto contacts = (long long *) ((JAVA_ARRAY) contacts__object)->data;
    b2World *world = (b2World *) addr;

    b2Contact *contact = world->GetContactList();
    int i = 0;
    while (contact != 0) {
        contacts[i++] = (long long) contact;
        contact = contact->GetNext();
    }
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniDispose___long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2World *world = (b2World *) (addr);
    delete world;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_setVelocityThreshold___float(CODENAME_ONE_THREAD_STATE, JAVA_FLOAT threshold) {
    b2_velocityThreshold = threshold;
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_World_getVelocityThreshold___R_float(CODENAME_ONE_THREAD_STATE) {
    return b2_velocityThreshold;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_World_jniRayCast___long_float_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT aX, JAVA_FLOAT aY, JAVA_FLOAT bX, JAVA_FLOAT bY) {
    b2World *world = (b2World *) addr;
    CustomRayCastCallback callback( /*env,*/ object);
    world->RayCast(&callback, b2Vec2(aX, aY), b2Vec2(bX, bY));
}
