#include "Clearwing.hpp"
#include "Utils.hpp"
#include "RuntimeTypes.hpp"
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType_Bitmap.hpp>
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType_SizeMetrics.hpp>
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType.hpp>
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType_Face.hpp>
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType_Stroker.hpp>
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType_Glyph.hpp>
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType_Library.hpp>
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType_GlyphSlot.hpp>
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType_GlyphMetrics.hpp>
#include <com/badlogic/gdx/graphics/g2d/freetype/FreeType_Size.hpp>
#include <java/nio/ByteBuffer.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

static jint lastError = 0;

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType::SM_getLastErrorCode_R_int() {

    return lastError;
}

void com::badlogic::gdx::graphics::g2d::freetype::FreeType$Library::SM_doneFreeType(jlong library) {

    FT_Done_FreeType((FT_Library)library);
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$Library::SM_newMemoryFace_R_long(jlong library, const shared_ptr<ByteBuffer> &data_object, jint dataSize, jint faceIndex) {
    auto data = (jbyte *)data_object->F_address;

    FT_Face face = 0;
    FT_Error error = FT_New_Memory_Face((FT_Library)library, (const FT_Byte*)data, dataSize, faceIndex, &face);
    if(error) {
        lastError = error;
        return 0;
    }
    else return (jlong)face;
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$Library::SM_strokerNew_R_long(jlong library) {

    FT_Stroker stroker;
    FT_Error error = FT_Stroker_New((FT_Library)library, &stroker);
    if(error) {
        lastError = error;
        return 0;
    }
    else return (jlong)stroker;
}

void com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_doneFace(jlong face) {

    FT_Done_Face((FT_Face)face);
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getFaceFlags_R_int(jlong face) {

    return ((FT_Face)face)->face_flags;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getStyleFlags_R_int(jlong face) {

    return ((FT_Face)face)->style_flags;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getNumGlyphs_R_int(jlong face) {

    return ((FT_Face)face)->num_glyphs;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getAscender_R_int(jlong face) {

    return ((FT_Face)face)->ascender;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getDescender_R_int(jlong face) {

    return ((FT_Face)face)->descender;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getHeight_R_int(jlong face) {

    return ((FT_Face)face)->height;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getMaxAdvanceWidth_R_int(jlong face) {

    return ((FT_Face)face)->max_advance_width;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getMaxAdvanceHeight_R_int(jlong face) {

    return ((FT_Face)face)->max_advance_height;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getUnderlinePosition_R_int(jlong face) {

    return ((FT_Face)face)->underline_position;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getUnderlineThickness_R_int(jlong face) {

    return ((FT_Face)face)->underline_thickness;
}

jbool com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_selectSize_R_boolean(jlong face, jint strike_index) {

    return !FT_Select_Size((FT_Face)face, strike_index);
}

jbool com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_setCharSize_R_boolean(jlong face, jint charWidth, jint charHeight, jint horzResolution, jint vertResolution) {

    return !FT_Set_Char_Size((FT_Face)face, charWidth, charHeight, horzResolution, vertResolution);
}

jbool com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_setPixelSizes_R_boolean(jlong face, jint pixelWidth, jint pixelHeight) {

    return !FT_Set_Pixel_Sizes((FT_Face)face, pixelWidth, pixelHeight);
}

jbool com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_loadGlyph_R_boolean(jlong face, jint glyphIndex, jint loadFlags) {

    return !FT_Load_Glyph((FT_Face)face, glyphIndex, loadFlags);
}

jbool com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_loadChar_R_boolean(jlong face, jint charCode, jint loadFlags) {

    return !FT_Load_Char((FT_Face)face, charCode, loadFlags);
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getGlyph_R_long(jlong face) {

    return (jlong)((FT_Face)face)->glyph;
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getSize_R_long(jlong face) {

    return (jlong)((FT_Face)face)->size;
}

jbool com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_hasKerning_R_boolean(jlong face) {

    return FT_HAS_KERNING(((FT_Face)face));
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getKerning_R_int(jlong face, jint leftGlyph, jint rightGlyph, jint kernMode) {

    FT_Vector kerning;
    FT_Error error = FT_Get_Kerning((FT_Face)face, leftGlyph, rightGlyph, kernMode, &kerning);
    if(error) return 0;
    return kerning.x;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Face::SM_getCharIndex_R_int(jlong face, jint charCode) {

    return FT_Get_Char_Index((FT_Face)face, charCode);
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$Size::SM_getMetrics_R_long(jlong address) {

    return (jlong)&((FT_Size)address)->metrics;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$SizeMetrics::SM_getXppem_R_int(jlong metrics) {

    return ((FT_Size_Metrics*)metrics)->x_ppem;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$SizeMetrics::SM_getYppem_R_int(jlong metrics) {

    return ((FT_Size_Metrics*)metrics)->y_ppem;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$SizeMetrics::SM_getXscale_R_int(jlong metrics) {

    return ((FT_Size_Metrics*)metrics)->x_scale;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$SizeMetrics::SM_getYscale_R_int(jlong metrics) {

    return ((FT_Size_Metrics*)metrics)->x_scale;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$SizeMetrics::SM_getAscender_R_int(jlong metrics) {

    return ((FT_Size_Metrics*)metrics)->ascender;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$SizeMetrics::SM_getDescender_R_int(jlong metrics) {

    return ((FT_Size_Metrics*)metrics)->descender;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$SizeMetrics::SM_getHeight_R_int(jlong metrics) {

    return ((FT_Size_Metrics*)metrics)->height;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$SizeMetrics::SM_getMaxAdvance_R_int(jlong metrics) {

    return ((FT_Size_Metrics*)metrics)->max_advance;
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getMetrics_R_long(jlong slot) {

    return (jlong)&((FT_GlyphSlot)slot)->metrics;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getLinearHoriAdvance_R_int(jlong slot) {

    return ((FT_GlyphSlot)slot)->linearHoriAdvance;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getLinearVertAdvance_R_int(jlong slot) {

    return ((FT_GlyphSlot)slot)->linearVertAdvance;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getAdvanceX_R_int(jlong slot) {

    return ((FT_GlyphSlot)slot)->advance.x;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getAdvanceY_R_int(jlong slot) {

    return ((FT_GlyphSlot)slot)->advance.y;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getFormat_R_int(jlong slot) {

    return ((FT_GlyphSlot)slot)->format;
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getBitmap_R_long(jlong slot) {

    FT_GlyphSlot glyph = ((FT_GlyphSlot)slot);
    return (jlong)&(glyph->bitmap);
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getBitmapLeft_R_int(jlong slot) {

    return ((FT_GlyphSlot)slot)->bitmap_left;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getBitmapTop_R_int(jlong slot) {

    return ((FT_GlyphSlot)slot)->bitmap_top;
}

jbool com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_renderGlyph_R_boolean(jlong slot, jint renderMode) {

    return !FT_Render_Glyph((FT_GlyphSlot)slot, (FT_Render_Mode)renderMode);
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphSlot::SM_getGlyph_R_long(jlong glyphSlot) {

    FT_Glyph glyph;
    FT_Error error = FT_Get_Glyph((FT_GlyphSlot)glyphSlot, &glyph);
    if(error) {
        lastError = error;
        return 0;
    }
    else return (jlong)glyph;
}

void com::badlogic::gdx::graphics::g2d::freetype::FreeType$Glyph::SM_done(jlong glyph) {

    FT_Done_Glyph((FT_Glyph)glyph);
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$Glyph::SM_strokeBorder_R_long(jlong glyph, jlong stroker, jbool inside) {

    FT_Glyph border_glyph = (FT_Glyph)glyph;
    FT_Glyph_StrokeBorder(&border_glyph, (FT_Stroker)stroker, inside, 1);
    return (jlong)border_glyph;
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$Glyph::SM_toBitmap_R_long(jlong glyph, jint renderMode) {

    FT_Glyph bitmap = (FT_Glyph)glyph;
    FT_Error error = FT_Glyph_To_Bitmap(&bitmap, (FT_Render_Mode)renderMode, NULL, 1);
    if(error) {
        lastError = error;
        return 0;
    }
    return (jlong)bitmap;
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType$Glyph::SM_getBitmap_R_long(jlong glyph) {

    FT_BitmapGlyph glyph_bitmap = ((FT_BitmapGlyph)glyph);
    return (jlong)&(glyph_bitmap->bitmap);
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Glyph::SM_getLeft_R_int(jlong glyph) {

    FT_BitmapGlyph glyph_bitmap = ((FT_BitmapGlyph)glyph);
    return glyph_bitmap->left;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Glyph::SM_getTop_R_int(jlong glyph) {

    FT_BitmapGlyph glyph_bitmap = ((FT_BitmapGlyph)glyph);
    return glyph_bitmap->top;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Bitmap::SM_getRows_R_int(jlong bitmap) {

    return ((FT_Bitmap*)bitmap)->rows;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Bitmap::SM_getWidth_R_int(jlong bitmap) {

    return ((FT_Bitmap*)bitmap)->width;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Bitmap::SM_getPitch_R_int(jlong bitmap) {

    return ((FT_Bitmap*)bitmap)->pitch;
}

shared_ptr<ByteBuffer> com::badlogic::gdx::graphics::g2d::freetype::FreeType$Bitmap::SM_getBuffer_R_java_nio_ByteBuffer(jlong bitmap) {

    FT_Bitmap* bmp = (FT_Bitmap*)bitmap;
    auto buffer = make_shared<java::nio::ByteBuffer>();
    buffer->init((jlong)bmp->buffer, bmp->rows * abs(bmp->pitch), false);
    return buffer;
//    return env->NewDirectByteBuffer((void*)bmp->buffer, bmp->rows * abs(bmp->pitch));
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Bitmap::SM_getNumGray_R_int(jlong bitmap) {

    return ((FT_Bitmap*)bitmap)->num_grays;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$Bitmap::SM_getPixelMode_R_int(jlong bitmap) {

    return ((FT_Bitmap*)bitmap)->pixel_mode;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphMetrics::SM_getWidth_R_int(jlong metrics) {

    return ((FT_Glyph_Metrics*)metrics)->width;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphMetrics::SM_getHeight_R_int(jlong metrics) {

    return ((FT_Glyph_Metrics*)metrics)->height;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphMetrics::SM_getHoriBearingX_R_int(jlong metrics) {

    return ((FT_Glyph_Metrics*)metrics)->horiBearingX;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphMetrics::SM_getHoriBearingY_R_int(jlong metrics) {

    return ((FT_Glyph_Metrics*)metrics)->horiBearingY;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphMetrics::SM_getHoriAdvance_R_int(jlong metrics) {

    return ((FT_Glyph_Metrics*)metrics)->horiAdvance;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphMetrics::SM_getVertBearingX_R_int(jlong metrics) {

    return ((FT_Glyph_Metrics*)metrics)->vertBearingX;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphMetrics::SM_getVertBearingY_R_int(jlong metrics) {

    return ((FT_Glyph_Metrics*)metrics)->vertBearingY;
}

jint com::badlogic::gdx::graphics::g2d::freetype::FreeType$GlyphMetrics::SM_getVertAdvance_R_int(jlong metrics) {

    return ((FT_Glyph_Metrics*)metrics)->vertAdvance;
}

void com::badlogic::gdx::graphics::g2d::freetype::FreeType$Stroker::SM_set(jlong stroker, jint radius, jint lineCap, jint lineJoin, jint miterLimit) {

    FT_Stroker_Set((FT_Stroker)stroker, radius, (FT_Stroker_LineCap)lineCap, (FT_Stroker_LineJoin)lineJoin, miterLimit);
}

void com::badlogic::gdx::graphics::g2d::freetype::FreeType$Stroker::SM_done(jlong stroker) {

    FT_Stroker_Done((FT_Stroker)stroker);
}

jlong com::badlogic::gdx::graphics::g2d::freetype::FreeType::SM_initFreeTypeJni_R_long() {

    FT_Library library = 0;
    FT_Error error = FT_Init_FreeType(&library);
    if(error) {
        lastError = error;
        return 0;
    }
    else return (jlong)library;
}

