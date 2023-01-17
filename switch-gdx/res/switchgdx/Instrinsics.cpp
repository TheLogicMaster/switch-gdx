#include "Clearwing.hpp"
#include "Utils.hpp"
#include "Array.hpp"
#include "switchgdx/gdx_matrix4.h"
#include <com/badlogic/gdx/graphics/Texture.hpp>
#include <java/util/Comparator.hpp>
#include <java/lang/IllegalStateException.hpp>
#include <com/badlogic/gdx/graphics/g2d/CpuSpriteBatch.hpp>
#include <com/badlogic/gdx/graphics/g2d/Sprite.hpp>
#include <com/badlogic/gdx/scenes/scene2d/Group.hpp>
#include <com/badlogic/gdx/scenes/scene2d/Actor.hpp>
#include <com/badlogic/gdx/math/Affine2.hpp>
#include <com/badlogic/gdx/math/Matrix4.hpp>
#include <com/badlogic/gdx/utils/SnapshotArray.hpp>
#include <com/badlogic/gdx/utils/TimSort.hpp>

#include <numbers>

using namespace com::badlogic::gdx;

constexpr int X1 = 0;
constexpr int Y1 = 1;
constexpr int X2 = 5;
constexpr int Y2 = 6;
constexpr int X3 = 10;
constexpr int Y3 = 11;
constexpr int X4 = 15;
constexpr int Y4 = 16;

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<Texture> &texture, jfloat x, jfloat y, jfloat originX, jfloat originY, jfloat width, jfloat height, jfloat scaleX, jfloat scaleY, jfloat rotation, jint srcX, jint srcY, jint srcWidth, jint srcHeight, jbool flipX, jbool flipY) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto vertices = F_vertices->getData<float>();

    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else if (F_idx == F_vertices->length)
        M_flush();

    auto worldOriginX = x + originX;
    auto worldOriginY = y + originY;
    auto fx = -originX;
    auto fy = -originY;
    auto fx2 = width - originX;
    auto fy2 = height - originY;

    if (scaleX != 1.0f or scaleY != 1.0f) {
        fx *= scaleX;
        fy *= scaleY;
        fx2 *= scaleX;
        fy2 *= scaleY;
    }

    auto p1x = fx;
    auto p1y = fy;
    auto p2x = fx;
    auto p2y = fy2;
    auto p3x = fx2;
    auto p3y = fy2;
    auto p4x = fx2;
    auto p4y = fy;

    jfloat x1;
    jfloat y1;
    jfloat x2;
    jfloat y2;
    jfloat x3;
    jfloat y3;
    jfloat x4;
    jfloat y4;

    if (rotation != 0.0f) {
        auto rads = rotation / 180 * std::numbers::pi;
        auto cos = (float)std::cos(rads);
        auto sin = (float)std::sin(rads);

        x1 = cos * p1x - sin * p1y;
        y1 = sin * p1x + cos * p1y;
        x2 = cos * p2x - sin * p2y;
        y2 = sin * p2x + cos * p2y;
        x3 = cos * p3x - sin * p3y;
        y3 = sin * p3x + cos * p3y;
        x4 = x1 + (x3 - x2);
        y4 = y3 - (y2 - y1);
    } else {
        x1 = p1x;
        y1 = p1y;
        x2 = p2x;
        y2 = p2y;
        x3 = p3x;
        y3 = p3y;
        x4 = p4x;
        y4 = p4y;
    }

    x1 += worldOriginX;
    y1 += worldOriginY;
    x2 += worldOriginX;
    y2 += worldOriginY;
    x3 += worldOriginX;
    y3 += worldOriginY;
    x4 += worldOriginX;
    y4 += worldOriginY;

    auto u = (jfloat)srcX * F_invTexWidth;
    auto v = (jfloat)(srcY + srcHeight) * F_invTexHeight;
    auto u2 = (jfloat)(srcX + srcWidth) * F_invTexWidth;
    auto v2 = (jfloat)srcY * F_invTexHeight;

    if (flipX) {
        auto tmp = u;
        u = u2;
        u2 = tmp;
    }

    if (flipY) {
        auto tmp = v;
        v = v2;
        v2 = tmp;
    }

    auto color = F_colorPacked;
    auto idx = F_idx;
    vertices[idx] = x1;
    vertices[idx + 1] = y1;
    vertices[idx + 2] = color;
    vertices[idx + 3] = u;
    vertices[idx + 4] = v;

    vertices[idx + 5] = x2;
    vertices[idx + 6] = y2;
    vertices[idx + 7] = color;
    vertices[idx + 8] = u;
    vertices[idx + 9] = v2;

    vertices[idx + 10] = x3;
    vertices[idx + 11] = y3;
    vertices[idx + 12] = color;
    vertices[idx + 13] = u2;
    vertices[idx + 14] = v2;

    vertices[idx + 15] = x4;
    vertices[idx + 16] = y4;
    vertices[idx + 17] = color;
    vertices[idx + 18] = u2;
    vertices[idx + 19] = v;
    F_idx = idx + 20;
}

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<Texture> &texture, jfloat x, jfloat y, jfloat width, jfloat height, jint srcX, jint srcY, jint srcWidth, jint srcHeight, jbool flipX, jbool flipY) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto vertices = F_vertices->getData<float>();

    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else if (F_idx == F_vertices->length)
        M_flush();

    auto u = (jfloat)srcX * F_invTexWidth;
    auto v = (jfloat)(srcY + srcHeight) * F_invTexHeight;
    auto u2 = (jfloat)(srcX + srcWidth) * F_invTexWidth;
    auto v2 = (jfloat)srcY * F_invTexHeight;
    auto fx2 = x + width;
    auto fy2 = y + height;

    if (flipX) {
        auto tmp = u;
        u = u2;
        u2 = tmp;
    }

    if (flipY) {
        auto tmp = v;
        v = v2;
        v2 = tmp;
    }

    auto color = F_colorPacked;
    auto idx = F_idx;
    vertices[idx] = x;
    vertices[idx + 1] = y;
    vertices[idx + 2] = color;
    vertices[idx + 3] = u;
    vertices[idx + 4] = v;

    vertices[idx + 5] = x;
    vertices[idx + 6] = fy2;
    vertices[idx + 7] = color;
    vertices[idx + 8] = u;
    vertices[idx + 9] = v2;

    vertices[idx + 10] = fx2;
    vertices[idx + 11] = fy2;
    vertices[idx + 12] = color;
    vertices[idx + 13] = u2;
    vertices[idx + 14] = v2;

    vertices[idx + 15] = fx2;
    vertices[idx + 16] = y;
    vertices[idx + 17] = color;
    vertices[idx + 18] = u2;
    vertices[idx + 19] = v;
    F_idx = idx + 20;
}

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<Texture> &texture, jfloat x, jfloat y, jint srcX, jint srcY, jint srcWidth, jint srcHeight) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto vertices = F_vertices->getData<float>();

    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else if (F_idx == F_vertices->length)
        M_flush();

    auto u = (jfloat)srcX * F_invTexWidth;
    auto v = (jfloat)(srcY + srcHeight) * F_invTexHeight;
    auto u2 = (jfloat)(srcX + srcWidth) * F_invTexWidth;
    auto v2 = (jfloat)srcY * F_invTexHeight;
    auto fx2 = x + (jfloat)srcWidth;
    auto fy2 = y + (jfloat)srcHeight;

    auto color = F_colorPacked;
    auto idx = F_idx;
    vertices[idx] = x;
    vertices[idx + 1] = y;
    vertices[idx + 2] = color;
    vertices[idx + 3] = u;
    vertices[idx + 4] = v;

    vertices[idx + 5] = x;
    vertices[idx + 6] = fy2;
    vertices[idx + 7] = color;
    vertices[idx + 8] = u;
    vertices[idx + 9] = v2;

    vertices[idx + 10] = fx2;
    vertices[idx + 11] = fy2;
    vertices[idx + 12] = color;
    vertices[idx + 13] = u2;
    vertices[idx + 14] = v2;

    vertices[idx + 15] = fx2;
    vertices[idx + 16] = y;
    vertices[idx + 17] = color;
    vertices[idx + 18] = u2;
    vertices[idx + 19] = v;
    F_idx = idx + 20;
}

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<Texture> &texture, jfloat x, jfloat y, jfloat width, jfloat height, jfloat u, jfloat v, jfloat u2, jfloat v2) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto vertices = F_vertices->getData<float>();

    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else if (F_idx == F_vertices->length)
        M_flush();

    auto fx2 = x + width;
    auto fy2 = y + height;

    auto color = F_colorPacked;
    auto idx = F_idx;
    vertices[idx] = x;
    vertices[idx + 1] = y;
    vertices[idx + 2] = color;
    vertices[idx + 3] = u;
    vertices[idx + 4] = v;

    vertices[idx + 5] = x;
    vertices[idx + 6] = fy2;
    vertices[idx + 7] = color;
    vertices[idx + 8] = u;
    vertices[idx + 9] = v2;

    vertices[idx + 10] = fx2;
    vertices[idx + 11] = fy2;
    vertices[idx + 12] = color;
    vertices[idx + 13] = u2;
    vertices[idx + 14] = v2;

    vertices[idx + 15] = fx2;
    vertices[idx + 16] = y;
    vertices[idx + 17] = color;
    vertices[idx + 18] = u2;
    vertices[idx + 19] = v;
    F_idx = idx + 20;
}

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<Texture> &texture, jfloat x, jfloat y, jfloat width, jfloat height) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto vertices = F_vertices->getData<float>();

    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else if (F_idx == F_vertices->length)
        M_flush();

    auto fx2 = x + width;
    auto fy2 = y + height;
    auto u = 0.0f;
    auto v = 1.0f;
    auto u2 = 1.0f;
    auto v2 = 0.0f;

    auto color = F_colorPacked;
    auto idx = F_idx;
    vertices[idx] = x;
    vertices[idx + 1] = y;
    vertices[idx + 2] = color;
    vertices[idx + 3] = u;
    vertices[idx + 4] = v;

    vertices[idx + 5] = x;
    vertices[idx + 6] = fy2;
    vertices[idx + 7] = color;
    vertices[idx + 8] = u;
    vertices[idx + 9] = v2;

    vertices[idx + 10] = fx2;
    vertices[idx + 11] = fy2;
    vertices[idx + 12] = color;
    vertices[idx + 13] = u2;
    vertices[idx + 14] = v2;

    vertices[idx + 15] = fx2;
    vertices[idx + 16] = y;
    vertices[idx + 17] = color;
    vertices[idx + 18] = u2;
    vertices[idx + 19] = v;
    F_idx = idx + 20;
}

void graphics::g2d::SpriteBatch::M_draw_Array1_float(const shared_ptr<Texture> &texture, const jarray &spriteVertices, jint offset, jint count) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();
    jint verticesLength = F_vertices->length;
    jint remainingVertices = verticesLength;
    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else {
        remainingVertices -= F_idx;
        if (remainingVertices == 0) {
            M_flush();
            remainingVertices = verticesLength;
        }
    }
    jint copyCount = std::min(remainingVertices, count);
    java::lang::System::SM_arraycopy(spriteVertices, offset, F_vertices, F_idx, copyCount);
    F_idx += copyCount;
    count -= copyCount;
    while (count > 0) {
        offset += copyCount;
        M_flush();
        copyCount = std::min(verticesLength, count);
        java::lang::System::SM_arraycopy(spriteVertices, offset, F_vertices, 0, copyCount);
        F_idx += copyCount;
        count -= copyCount;
    }
}

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<TextureRegion> &region, jfloat x, jfloat y) {
    M_draw(region, x, y, (jfloat)region->F_regionWidth, (jfloat)region->F_regionHeight);
}

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<TextureRegion> &region, jfloat x, jfloat y, jfloat width, jfloat height) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto &texture = region->F_texture;

    auto vertices = F_vertices->getData<float>();

    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else if (F_idx == F_vertices->length)
        M_flush();

    auto fx2 = x + width;
    auto fy2 = y + height;
    auto u = region->F_u;
    auto v = region->F_v2;
    auto u2 = region->F_u2;
    auto v2 = region->F_v;

    auto color = F_colorPacked;
    auto idx = F_idx;
    vertices[idx] = x;
    vertices[idx + 1] = y;
    vertices[idx + 2] = color;
    vertices[idx + 3] = u;
    vertices[idx + 4] = v;

    vertices[idx + 5] = x;
    vertices[idx + 6] = fy2;
    vertices[idx + 7] = color;
    vertices[idx + 8] = u;
    vertices[idx + 9] = v2;

    vertices[idx + 10] = fx2;
    vertices[idx + 11] = fy2;
    vertices[idx + 12] = color;
    vertices[idx + 13] = u2;
    vertices[idx + 14] = v2;

    vertices[idx + 15] = fx2;
    vertices[idx + 16] = y;
    vertices[idx + 17] = color;
    vertices[idx + 18] = u2;
    vertices[idx + 19] = v;
    F_idx = idx + 20;
}

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<TextureRegion> &region, jfloat x, jfloat y, jfloat originX, jfloat originY, jfloat width, jfloat height, jfloat scaleX, jfloat scaleY, jfloat rotation) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto &texture = region->F_texture;

    auto vertices = F_vertices->getData<float>();

    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else if (F_idx == F_vertices->length)
        M_flush();

    auto worldOriginX = x + originX;
    auto worldOriginY = y + originY;
    auto fx = -originX;
    auto fy = -originY;
    auto fx2 = width - originX;
    auto fy2 = height - originY;

    if (scaleX != 1.0f or scaleY != 1.0f) {
        fx *= scaleX;
        fy *= scaleY;
        fx2 *= scaleX;
        fy2 *= scaleY;
    }

    auto p1x = fx;
    auto p1y = fy;
    auto p2x = fx;
    auto p2y = fy2;
    auto p3x = fx2;
    auto p3y = fy2;
    auto p4x = fx2;
    auto p4y = fy;

    jfloat x1;
    jfloat y1;
    jfloat x2;
    jfloat y2;
    jfloat x3;
    jfloat y3;
    jfloat x4;
    jfloat y4;

    if (rotation != 0.0f) {
        auto rads = rotation / 180 * std::numbers::pi;
        auto cos = (float)std::cos(rads);
        auto sin = (float)std::sin(rads);

        x1 = cos * p1x - sin * p1y;
        y1 = sin * p1x + cos * p1y;
        x2 = cos * p2x - sin * p2y;
        y2 = sin * p2x + cos * p2y;
        x3 = cos * p3x - sin * p3y;
        y3 = sin * p3x + cos * p3y;
        x4 = x1 + (x3 - x2);
        y4 = y3 - (y2 - y1);
    } else {
        x1 = p1x;
        y1 = p1y;
        x2 = p2x;
        y2 = p2y;
        x3 = p3x;
        y3 = p3y;
        x4 = p4x;
        y4 = p4y;
    }

    x1 += worldOriginX;
    y1 += worldOriginY;
    x2 += worldOriginX;
    y2 += worldOriginY;
    x3 += worldOriginX;
    y3 += worldOriginY;
    x4 += worldOriginX;
    y4 += worldOriginY;

    auto u = region->F_u;
    auto v = region->F_v2;
    auto u2 = region->F_u2;
    auto v2 = region->F_v;

    auto color = F_colorPacked;
    auto idx = F_idx;
    vertices[idx] = x1;
    vertices[idx + 1] = y1;
    vertices[idx + 2] = color;
    vertices[idx + 3] = u;
    vertices[idx + 4] = v;

    vertices[idx + 5] = x2;
    vertices[idx + 6] = y2;
    vertices[idx + 7] = color;
    vertices[idx + 8] = u;
    vertices[idx + 9] = v2;

    vertices[idx + 10] = x3;
    vertices[idx + 11] = y3;
    vertices[idx + 12] = color;
    vertices[idx + 13] = u2;
    vertices[idx + 14] = v2;

    vertices[idx + 15] = x4;
    vertices[idx + 16] = y4;
    vertices[idx + 17] = color;
    vertices[idx + 18] = u2;
    vertices[idx + 19] = v;
    F_idx = idx + 20;
}

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<TextureRegion> &region, jfloat x, jfloat y, jfloat originX, jfloat originY, jfloat width, jfloat height, jfloat scaleX, jfloat scaleY, jfloat rotation, jbool clockwise) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto &texture = region->F_texture;

    auto vertices = F_vertices->getData<float>();

    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else if (F_idx == F_vertices->length)
        M_flush();

    auto worldOriginX = x + originX;
    auto worldOriginY = y + originY;
    auto fx = -originX;
    auto fy = -originY;
    auto fx2 = width - originX;
    auto fy2 = height - originY;

    if (scaleX != 1.0f or scaleY != 1.0f) {
        fx *= scaleX;
        fy *= scaleY;
        fx2 *= scaleX;
        fy2 *= scaleY;
    }

    auto p1x = fx;
    auto p1y = fy;
    auto p2x = fx;
    auto p2y = fy2;
    auto p3x = fx2;
    auto p3y = fy2;
    auto p4x = fx2;
    auto p4y = fy;

    jfloat x1;
    jfloat y1;
    jfloat x2;
    jfloat y2;
    jfloat x3;
    jfloat y3;
    jfloat x4;
    jfloat y4;

    if (rotation != 0.0f) {
        auto rads = rotation / 180 * std::numbers::pi;
        auto cos = (float)std::cos(rads);
        auto sin = (float)std::sin(rads);

        x1 = cos * p1x - sin * p1y;
        y1 = sin * p1x + cos * p1y;
        x2 = cos * p2x - sin * p2y;
        y2 = sin * p2x + cos * p2y;
        x3 = cos * p3x - sin * p3y;
        y3 = sin * p3x + cos * p3y;
        x4 = x1 + (x3 - x2);
        y4 = y3 - (y2 - y1);
    } else {
        x1 = p1x;
        y1 = p1y;
        x2 = p2x;
        y2 = p2y;
        x3 = p3x;
        y3 = p3y;
        x4 = p4x;
        y4 = p4y;
    }

    x1 += worldOriginX;
    y1 += worldOriginY;
    x2 += worldOriginX;
    y2 += worldOriginY;
    x3 += worldOriginX;
    y3 += worldOriginY;
    x4 += worldOriginX;
    y4 += worldOriginY;

    float u1, v1, u2, v2, u3, v3, u4, v4;
    if (clockwise) {
        u1 = region->F_u2;
        v1 = region->F_v2;
        u2 = region->F_u;
        v2 = region->F_v2;
        u3 = region->F_u;
        v3 = region->F_v;
        u4 = region->F_u2;
        v4 = region->F_v;
    } else {
        u1 = region->F_u;
        v1 = region->F_v;
        u2 = region->F_u2;
        v2 = region->F_v;
        u3 = region->F_u2;
        v3 = region->F_v2;
        u4 = region->F_u;
        v4 = region->F_v2;
    }

    auto color = F_colorPacked;
    auto idx = F_idx;
    vertices[idx] = x1;
    vertices[idx + 1] = y1;
    vertices[idx + 2] = color;
    vertices[idx + 3] = u1;
    vertices[idx + 4] = v1;

    vertices[idx + 5] = x2;
    vertices[idx + 6] = y2;
    vertices[idx + 7] = color;
    vertices[idx + 8] = u2;
    vertices[idx + 9] = v2;

    vertices[idx + 10] = x3;
    vertices[idx + 11] = y3;
    vertices[idx + 12] = color;
    vertices[idx + 13] = u3;
    vertices[idx + 14] = v3;

    vertices[idx + 15] = x4;
    vertices[idx + 16] = y4;
    vertices[idx + 17] = color;
    vertices[idx + 18] = u4;
    vertices[idx + 19] = v4;
    F_idx = idx + 20;
}

void graphics::g2d::SpriteBatch::M_draw(const shared_ptr<TextureRegion> &region, jfloat width, jfloat height, const shared_ptr<math::Affine2> &transform) {
    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto &texture = region->F_texture;

    auto vertices = F_vertices->getData<float>();

    if (texture != F_lastTexture)
        M_switchTexture(texture);
    else if (F_idx == F_vertices->length)
        M_flush();

    jfloat x1 = transform->F_m02;
    jfloat y1 = transform->F_m12;
    jfloat x2 = transform->F_m01 * height +transform->F_m02;
    jfloat y2 = transform->F_m11 * height +transform->F_m12;
    jfloat x3 = transform->F_m00 * width + transform->F_m01 * height + transform->F_m02;
    jfloat y3 = transform->F_m10 * width + transform->F_m11 * height + transform->F_m12;
    jfloat x4 = transform->F_m00 * width + transform->F_m02;
    jfloat y4 = transform->F_m10 * width + transform->F_m12;

    auto u = region->F_u;
    auto v = region->F_v2;
    auto u2 = region->F_u2;
    auto v2 = region->F_v;

    auto color = F_colorPacked;
    auto idx = F_idx;
    vertices[idx] = x1;
    vertices[idx + 1] = y1;
    vertices[idx + 2] = color;
    vertices[idx + 3] = u;
    vertices[idx + 4] = v;

    vertices[idx + 5] = x2;
    vertices[idx + 6] = y2;
    vertices[idx + 7] = color;
    vertices[idx + 8] = u;
    vertices[idx + 9] = v2;

    vertices[idx + 10] = x3;
    vertices[idx + 11] = y3;
    vertices[idx + 12] = color;
    vertices[idx + 13] = u2;
    vertices[idx + 14] = v2;

    vertices[idx + 15] = x4;
    vertices[idx + 16] = y4;
    vertices[idx + 17] = color;
    vertices[idx + 18] = u2;
    vertices[idx + 19] = v;
    F_idx = idx + 20;
}

void graphics::g2d::SpriteBatch::M_switchTexture(const shared_ptr<Texture> &texture) {
    M_flush();
    F_lastTexture = texture;
    F_invTexWidth = 1.0f / (jfloat)texture->M_getWidth_R_int();
    F_invTexHeight = 1.0f / (jfloat)texture->M_getHeight_R_int();
}

void graphics::g2d::Sprite::M_setPosition(jfloat x, jfloat y) {
    F_x = x;
    F_y = y;

    if (F_dirty)
        return;
    if (F_rotation != 0.0f or F_scaleX != 1.0f or F_scaleY != 1.0f) {
        F_dirty = true;
        return;
    }

    auto x2 = x + F_width;
    auto y2 = y + F_height;
    auto vertices = F_vertices->getData<float>();
    vertices[X1] = x;
    vertices[Y1] = y;

    vertices[X2] = x;
    vertices[Y2] = y2;

    vertices[X3] = x2;
    vertices[Y3] = y2;

    vertices[X4] = x2;
    vertices[Y4] = y;
}

jarray graphics::g2d::Sprite::M_getVertices_R_Array1_float() {
    if (F_dirty) {
        F_dirty = false;
        auto vertices = F_vertices->getData<float>();
        auto localX = -F_originX;
        auto localY = -F_originY;
        auto localX2 = localX + F_width;
        auto localY2 = localY + F_height;
        auto worldOriginX = F_x - localX;
        auto worldOriginY = F_y - localY;
        if (F_scaleX != 1 || F_scaleY != 1) {
            localX *= F_scaleX;
            localY *= F_scaleY;
            localX2 *= F_scaleX;
            localY2 *= F_scaleY;
        }
        if (F_rotation != 0) {
            auto rads = F_rotation / 180 * std::numbers::pi;
            auto cos = (float)std::cos(rads);
            auto sin = (float)std::sin(rads);
            auto localXCos = localX * cos;
            auto localXSin = localX * sin;
            auto localYCos = localY * cos;
            auto localYSin = localY * sin;
            auto localX2Cos = localX2 * cos;
            auto localX2Sin = localX2 * sin;
            auto localY2Cos = localY2 * cos;
            auto localY2Sin = localY2 * sin;

            auto x1 = localXCos - localYSin + worldOriginX;
            auto y1 = localYCos + localXSin + worldOriginY;
            vertices[X1] = x1;
            vertices[Y1] = y1;

            auto x2 = localXCos - localY2Sin + worldOriginX;
            auto y2 = localY2Cos + localXSin + worldOriginY;
            vertices[X2] = x2;
            vertices[Y2] = y2;

            auto x3 = localX2Cos - localY2Sin + worldOriginX;
            auto y3 = localY2Cos + localX2Sin + worldOriginY;
            vertices[X3] = x3;
            vertices[Y3] = y3;

            vertices[X4] = x1 + (x3 - x2);
            vertices[Y4] = y3 - (y2 - y1);
        } else {
            auto x1 = localX + worldOriginX;
            auto y1 = localY + worldOriginY;
            auto x2 = localX2 + worldOriginX;
            auto y2 = localY2 + worldOriginY;

            vertices[X1] = x1;
            vertices[Y1] = y1;

            vertices[X2] = x1;
            vertices[Y2] = y2;

            vertices[X3] = x2;
            vertices[Y3] = y2;

            vertices[X4] = x2;
            vertices[Y4] = y1;
        }
    }
    return F_vertices;
}

void utils::TimSort::SM_binarySort_Array1_java_lang_Object(const jarray &aObj, jint lo, jint hi, jint start, const shared_ptr<java::util::Comparator> &c) {
    auto a = aObj->getData<jobject>();

    if (start == lo)
        start++;

    for (; start < hi; start++) {
        auto pivot = a[start];
        jint left = lo;
        jint right = start;
        while (left < right) {
            jint mid = (left + right) / 2;
            if (c->M_compare_R_int(pivot, a[mid]) < 0)
                right = mid;
            else
                left = mid + 1;
        }
        jint n = start - left;
        switch (n) {
            case 2:
                a[left + 2] = a[left + 1];
            case 1:
                a[left + 1] = a[left];
                break;
            default:
                java::lang::System::SM_arraycopy(aObj, left, aObj, left + 1, n);
        }
        a[left] = pivot;
    }
}

void math::Matrix4::SM_mul_Array1_float_Array1_float(const jarray &a, const jarray &b) {
    matrix4_mul(a->getData<float>(), b->getData<float>());
}

void math::Matrix4::SM_mulVec_Array1_float_Array1_float(const jarray &mat, const jarray &vec) {
    matrix4_mulVec(mat->getData<float>(), vec->getData<float>());
}

void math::Matrix4::SM_prj_Array1_float_Array1_float(const jarray &mat, const jarray &vec) {
    matrix4_proj(mat->getData<float>(), vec->getData<float>());
}

void math::Matrix4::SM_rot_Array1_float_Array1_float(const jarray &mat, const jarray &vec) {
    matrix4_rot(mat->getData<float>(), vec->getData<float>());
}

void scenes::scene2d::Group::M_act(jfloat delta) {
    scenes::scene2d::Actor::M_act(delta);
    auto children = F_children;
    auto actors = children->M_begin_R_Array1_java_lang_Object();
    for (int i = 0, n = children->F_size; i < n; i++)
        object_cast<scenes::scene2d::Actor>(actors->get<jobject>(i))->M_act(delta);
    children->M_end();
}

void com::badlogic::gdx::graphics::g2d::CpuSpriteBatch::M_drawAdjustedUV(const shared_ptr<Texture> &texture, jfloat x, jfloat y, jfloat originX, jfloat originY, jfloat width, jfloat height, jfloat scaleX, jfloat scaleY, jfloat rotation, jfloat u, jfloat v, jfloat u2, jfloat v2, jbool flipX, jbool flipY) {
#if USE_STACK_TRACES
    CallStackObserver stackObserver {com::badlogic::gdx::graphics::g2d::CpuSpriteBatch::NAME, "drawAdjustedUV"};
#endif

    if (!F_drawing)
        vm::throwNew<java::lang::IllegalStateException>();

    auto verticesArray = F_vertices;
    if (texture.get() != F_lastTexture.get())
        M_switchTexture(texture);
    else if (F_idx == verticesArray->length)
        com::badlogic::gdx::graphics::g2d::SpriteBatch::M_flush();

    auto worldOriginX = x + originX;
    auto worldOriginY = y + originY;
    auto fx = -originX;
    auto fy = -originY;
    auto fx2 = width - originX;
    auto fy2 = height - originY;

    if (scaleX != 1.0f or scaleY != 1.0f) {
        fx *= scaleX;
        fy *= scaleY;
        fx2 *= scaleX;
        fy2 *= scaleY;
    }

    auto p1x = fx;
    auto p1y = fy;
    auto p2x = fx;
    auto p2y = fy2;
    auto p3x = fx2;
    auto p3y = fy2;
    auto p4x = fx2;
    auto p4y = fy;

    jfloat x1;
    jfloat y1;
    jfloat x2;
    jfloat y2;
    jfloat x3;
    jfloat y3;
    jfloat x4;
    jfloat y4;

    if (rotation != 0.0f) {
        auto rads = rotation / 180 * std::numbers::pi;
        auto cos = (float)std::cos(rads);
        auto sin = (float)std::sin(rads);

        x1 = cos * p1x - sin * p1y;
        y1 = sin * p1x + cos * p1y;
        x2 = cos * p2x - sin * p2y;
        y2 = sin * p2x + cos * p2y;
        x3 = cos * p3x - sin * p3y;
        y3 = sin * p3x + cos * p3y;
        x4 = x1 + (x3 - x2);
        y4 = y3 - (y2 - y1);
    } else {
        x1 = p1x;
        y1 = p1y;
        x2 = p2x;
        y2 = p2y;
        x3 = p3x;
        y3 = p3y;
        x4 = p4x;
        y4 = p4y;
    }

    x1 += worldOriginX;
    y1 += worldOriginY;
    x2 += worldOriginX;
    y2 += worldOriginY;
    x3 += worldOriginX;
    y3 += worldOriginY;
    x4 += worldOriginX;
    y4 += worldOriginY;

    if (flipX) {
        auto tmp = u;
        u = u2;
        u2 = tmp;
    }
    if (flipY) {
        auto tmp = v;
        v = v2;
        v2 = tmp;
    }

    auto t = F_adjustAffine;
    auto vertices = verticesArray->getData<jfloat>();

    vertices[F_idx + 0] = t->F_m00 * x1 + t->F_m01 * y1 + t->F_m02;
    vertices[F_idx + 1] = t->F_m10 * x1 + t->F_m11 * y1 + t->F_m12;
    vertices[F_idx + 2] = F_colorPacked;
    vertices[F_idx + 3] = u;
    vertices[F_idx + 4] = v;

    vertices[F_idx + 5] = t->F_m00 * x2 + t->F_m01 * y2 + t->F_m02;
    vertices[F_idx + 6] = t->F_m10 * x2 + t->F_m11 * y2 + t->F_m12;
    vertices[F_idx + 7] = F_colorPacked;
    vertices[F_idx + 8] = u;
    vertices[F_idx + 9] = v2;

    vertices[F_idx + 10] = t->F_m00 * x3 + t->F_m01 * y3 + t->F_m02;
    vertices[F_idx + 11] = t->F_m10 * x3 + t->F_m11 * y3 + t->F_m12;
    vertices[F_idx + 12] = F_colorPacked;
    vertices[F_idx + 13] = u2;
    vertices[F_idx + 14] = v2;

    vertices[F_idx + 15] = t->F_m00 * x4 + t->F_m01 * y4 + t->F_m02;
    vertices[F_idx + 16] = t->F_m10 * x4 + t->F_m11 * y4 + t->F_m12;
    vertices[F_idx + 17] = F_colorPacked;
    vertices[F_idx + 18] = u2;
    vertices[F_idx + 19] = v;

    F_idx += 20;
}
