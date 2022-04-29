// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 27

#include <Box2D/Box2D.h>

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_Body_jniCreateFixture___long_long_float_float_float_boolean_short_short_short_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG shapeAddr, JAVA_FLOAT friction, JAVA_FLOAT restitution, JAVA_FLOAT density, JAVA_BOOLEAN isSensor, JAVA_SHORT filterCategoryBits, JAVA_SHORT filterMaskBits, JAVA_SHORT filterGroupIndex) {
    b2Body *body = (b2Body *) addr;
    b2Shape *shape = (b2Shape *) shapeAddr;
    b2FixtureDef fixtureDef;

    fixtureDef.shape = shape;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.density = density;
    fixtureDef.isSensor = isSensor;
    fixtureDef.filter.maskBits = filterMaskBits;
    fixtureDef.filter.categoryBits = filterCategoryBits;
    fixtureDef.filter.groupIndex = filterGroupIndex;

    return (jlong) body->CreateFixture(&fixtureDef);
}

extern "C" JAVA_LONG com_badlogic_gdx_physics_box2d_Body_jniCreateFixture___long_long_float_R_long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_LONG shapeAddr, JAVA_FLOAT density) {
    b2Body *body = (b2Body *) addr;
    b2Shape *shape = (b2Shape *) shapeAddr;
    return (jlong) body->CreateFixture(shape, density);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetTransform___long_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT positionX, JAVA_FLOAT positionY, JAVA_FLOAT angle) {
    b2Body *body = (b2Body *) addr;
    body->SetTransform(b2Vec2(positionX, positionY), angle);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetTransform___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT vals__object) {
    auto vals = (float *) ((JAVA_ARRAY) vals__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Transform t = body->GetTransform();
    vals[0] = t.p.x;
    vals[1] = t.p.y;
    vals[2] = t.q.c;
    vals[3] = t.q.s;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetPosition___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT position__object) {
    auto position = (float *) ((JAVA_ARRAY) position__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 p = body->GetPosition();
    position[0] = p.x;
    position[1] = p.y;
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Body_jniGetAngle___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->GetAngle();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetWorldCenter___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT worldCenter__object) {
    auto worldCenter = (float *) ((JAVA_ARRAY) worldCenter__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 w = body->GetWorldCenter();
    worldCenter[0] = w.x;
    worldCenter[1] = w.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetLocalCenter___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT localCenter__object) {
    auto localCenter = (float *) ((JAVA_ARRAY) localCenter__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 w = body->GetLocalCenter();
    localCenter[0] = w.x;
    localCenter[1] = w.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetLinearVelocity___long_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT x, JAVA_FLOAT y) {
    b2Body *body = (b2Body *) addr;
    body->SetLinearVelocity(b2Vec2(x, y));
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetLinearVelocity___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT linearVelocity__object) {
    auto linearVelocity = (float *) ((JAVA_ARRAY) linearVelocity__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 l = body->GetLinearVelocity();
    linearVelocity[0] = l.x;
    linearVelocity[1] = l.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetAngularVelocity___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT omega) {
    b2Body *body = (b2Body *) addr;
    body->SetAngularVelocity(omega);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Body_jniGetAngularVelocity___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->GetAngularVelocity();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniApplyForce___long_float_float_float_float_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT forceX, JAVA_FLOAT forceY, JAVA_FLOAT pointX, JAVA_FLOAT pointY, JAVA_BOOLEAN wake) {
    b2Body *body = (b2Body *) addr;
    body->ApplyForce(b2Vec2(forceX, forceY), b2Vec2(pointX, pointY), wake);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniApplyForceToCenter___long_float_float_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT forceX, JAVA_FLOAT forceY, JAVA_BOOLEAN wake) {
    b2Body *body = (b2Body *) addr;
    body->ApplyForceToCenter(b2Vec2(forceX, forceY), wake);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniApplyTorque___long_float_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT torque, JAVA_BOOLEAN wake) {
    b2Body *body = (b2Body *) addr;
    body->ApplyTorque(torque, wake);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniApplyLinearImpulse___long_float_float_float_float_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT impulseX, JAVA_FLOAT impulseY, JAVA_FLOAT pointX, JAVA_FLOAT pointY, JAVA_BOOLEAN wake) {
    b2Body *body = (b2Body *) addr;
    body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), b2Vec2(pointX, pointY), wake);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniApplyAngularImpulse___long_float_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT impulse, JAVA_BOOLEAN wake) {
    b2Body *body = (b2Body *) addr;
    body->ApplyAngularImpulse(impulse, wake);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Body_jniGetMass___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->GetMass();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Body_jniGetInertia___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->GetInertia();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetMassData___long_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_OBJECT massData__object) {
    auto massData = (float *) ((JAVA_ARRAY) massData__object)->data;
    b2Body *body = (b2Body *) addr;
    b2MassData m;
    body->GetMassData(&m);
    massData[0] = m.mass;
    massData[1] = m.center.x;
    massData[2] = m.center.y;
    massData[3] = m.I;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetMassData___long_float_float_float_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT mass, JAVA_FLOAT centerX, JAVA_FLOAT centerY, JAVA_FLOAT I) {
    b2Body *body = (b2Body *) addr;
    b2MassData m;
    m.mass = mass;
    m.center.x = centerX;
    m.center.y = centerY;
    m.I = I;
    body->SetMassData(&m);
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniResetMassData___long(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    body->ResetMassData();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetWorldPoint___long_float_float_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT localPointX, JAVA_FLOAT localPointY, JAVA_OBJECT worldPoint__object) {
    auto worldPoint = (float *) ((JAVA_ARRAY) worldPoint__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 w = body->GetWorldPoint(b2Vec2(localPointX, localPointY));
    worldPoint[0] = w.x;
    worldPoint[1] = w.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetWorldVector___long_float_float_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT localVectorX, JAVA_FLOAT localVectorY, JAVA_OBJECT worldVector__object) {
    auto worldVector = (float *) ((JAVA_ARRAY) worldVector__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 w = body->GetWorldVector(b2Vec2(localVectorX, localVectorY));
    worldVector[0] = w.x;
    worldVector[1] = w.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetLocalPoint___long_float_float_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT worldPointX, JAVA_FLOAT worldPointY, JAVA_OBJECT localPoint__object) {
    auto localPoint = (float *) ((JAVA_ARRAY) localPoint__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 w = body->GetLocalPoint(b2Vec2(worldPointX, worldPointY));
    localPoint[0] = w.x;
    localPoint[1] = w.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetLocalVector___long_float_float_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT worldVectorX, JAVA_FLOAT worldVectorY, JAVA_OBJECT worldVector__object) {
    auto worldVector = (float *) ((JAVA_ARRAY) worldVector__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 w = body->GetLocalVector(b2Vec2(worldVectorX, worldVectorY));
    worldVector[0] = w.x;
    worldVector[1] = w.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetLinearVelocityFromWorldPoint___long_float_float_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT worldPointX, JAVA_FLOAT worldPointY, JAVA_OBJECT linVelWorld__object) {
    auto linVelWorld = (float *) ((JAVA_ARRAY) linVelWorld__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 w = body->GetLinearVelocityFromWorldPoint(b2Vec2(worldPointX, worldPointY));
    linVelWorld[0] = w.x;
    linVelWorld[1] = w.y;
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniGetLinearVelocityFromLocalPoint___long_float_float_float_1ARRAY(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT localPointX, JAVA_FLOAT localPointY, JAVA_OBJECT linVelLoc__object) {
    auto linVelLoc = (float *) ((JAVA_ARRAY) linVelLoc__object)->data;
    b2Body *body = (b2Body *) addr;
    b2Vec2 w = body->GetLinearVelocityFromLocalPoint(b2Vec2(localPointX, localPointY));
    linVelLoc[0] = w.x;
    linVelLoc[1] = w.y;
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Body_jniGetLinearDamping___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->GetLinearDamping();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetLinearDamping___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT linearDamping) {
    b2Body *body = (b2Body *) addr;
    body->SetLinearDamping(linearDamping);
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Body_jniGetAngularDamping___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->GetAngularDamping();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetAngularDamping___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT angularDamping) {
    b2Body *body = (b2Body *) addr;
    body->SetAngularDamping(angularDamping);
}


// @Line: 623

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

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetType___long_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_INT type) {
    b2Body *body = (b2Body *) addr;
    body->SetType(getBodyType(type));
}

extern "C" JAVA_INT com_badlogic_gdx_physics_box2d_Body_jniGetType___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->GetType();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetBullet___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2Body *body = (b2Body *) addr;
    body->SetBullet(flag);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Body_jniIsBullet___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->IsBullet();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetSleepingAllowed___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2Body *body = (b2Body *) addr;
    body->SetSleepingAllowed(flag);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Body_jniIsSleepingAllowed___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->IsSleepingAllowed();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetAwake___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2Body *body = (b2Body *) addr;
    body->SetAwake(flag);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Body_jniIsAwake___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->IsAwake();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetActive___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2Body *body = (b2Body *) addr;
    body->SetActive(flag);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Body_jniIsActive___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->IsActive();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetFixedRotation___long_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_BOOLEAN flag) {
    b2Body *body = (b2Body *) addr;
    body->SetFixedRotation(flag);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_physics_box2d_Body_jniIsFixedRotation___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->IsFixedRotation();
}

extern "C" JAVA_FLOAT com_badlogic_gdx_physics_box2d_Body_jniGetGravityScale___long_R_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr) {
    b2Body *body = (b2Body *) addr;
    return body->GetGravityScale();
}

extern "C" JAVA_VOID com_badlogic_gdx_physics_box2d_Body_jniSetGravityScale___long_float(CODENAME_ONE_THREAD_STATE, JAVA_OBJECT object, JAVA_LONG addr, JAVA_FLOAT scale) {
    b2Body *body = (b2Body *) addr;
    body->SetGravityScale(scale);
}

