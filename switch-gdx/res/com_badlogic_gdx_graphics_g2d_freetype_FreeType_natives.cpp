// Auto-generated C++ for ClearwingVM

extern "C" {
#include "cn1_globals.h"
#include "java_nio_ByteBuffer.h"
}

// @Line: 38

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

static jint lastError = 0;

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_getLastErrorCode___R_int(CODENAME_ONE_THREAD_STATE) {
    return lastError;
}

extern "C" JAVA_VOID com_badlogic_gdx_graphics_g2d_freetype_FreeType_Library_doneFreeType___long(CODENAME_ONE_THREAD_STATE, JAVA_LONG library) {
    FT_Done_FreeType((FT_Library)library);
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_Library_newMemoryFace___long_java_nio_ByteBuffer_int_int_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG library, JAVA_OBJECT data__object, JAVA_INT dataSize, JAVA_INT faceIndex) {
    auto data = (char*) ((obj__java_nio_ByteBuffer *) data__object)->java_nio_Buffer_address;
    FT_Face face = 0;
    FT_Error error = FT_New_Memory_Face((FT_Library)library, (const FT_Byte*)data, dataSize, faceIndex, &face);
    if(error) {
        lastError = error;
        return 0;
    }
    else return (jlong)face;
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_Library_strokerNew___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG library) {
    FT_Stroker stroker;
    FT_Error error = FT_Stroker_New((FT_Library)library, &stroker);
    if(error) {
        lastError = error;
        return 0;
    }
    else return (jlong)stroker;
}

extern "C" JAVA_VOID com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_doneFace___long(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    FT_Done_Face((FT_Face)face);
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getFaceFlags___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->face_flags;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getStyleFlags___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->style_flags;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getNumGlyphs___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->num_glyphs;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getAscender___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->ascender;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getDescender___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->descender;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getHeight___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->height;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getMaxAdvanceWidth___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->max_advance_width;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getMaxAdvanceHeight___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->max_advance_height;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getUnderlinePosition___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->underline_position;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getUnderlineThickness___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return ((FT_Face)face)->underline_thickness;
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_selectSize___long_int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_LONG face, JAVA_INT strike_index) {
    return !FT_Select_Size((FT_Face)face, strike_index);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_setCharSize___long_int_int_int_int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_LONG face, JAVA_INT charWidth, JAVA_INT charHeight, JAVA_INT horzResolution, JAVA_INT vertResolution) {
    return !FT_Set_Char_Size((FT_Face)face, charWidth, charHeight, horzResolution, vertResolution);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_setPixelSizes___long_int_int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_LONG face, JAVA_INT pixelWidth, JAVA_INT pixelHeight) {
    return !FT_Set_Pixel_Sizes((FT_Face)face, pixelWidth, pixelHeight);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_loadGlyph___long_int_int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_LONG face, JAVA_INT glyphIndex, JAVA_INT loadFlags) {
    return !FT_Load_Glyph((FT_Face)face, glyphIndex, loadFlags);
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_loadChar___long_int_int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_LONG face, JAVA_INT charCode, JAVA_INT loadFlags) {
    return !FT_Load_Char((FT_Face)face, charCode, loadFlags);
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getGlyph___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return (jlong)((FT_Face)face)->glyph;
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getSize___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return (jlong)((FT_Face)face)->size;
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_hasKerning___long_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_LONG face) {
    return FT_HAS_KERNING(((FT_Face)face));
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getKerning___long_int_int_int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face, JAVA_INT leftGlyph, JAVA_INT rightGlyph, JAVA_INT kernMode) {
    FT_Vector kerning;
    FT_Error error = FT_Get_Kerning((FT_Face)face, leftGlyph, rightGlyph, kernMode, &kerning);
    if(error) return 0;
    return kerning.x;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Face_getCharIndex___long_int_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG face, JAVA_INT charCode) {
    return FT_Get_Char_Index((FT_Face)face, charCode);
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_Size_getMetrics___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG address) {
    return (jlong)&((FT_Size)address)->metrics;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_SizeMetrics_getXppem___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Size_Metrics*)metrics)->x_ppem;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_SizeMetrics_getYppem___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Size_Metrics*)metrics)->y_ppem;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_SizeMetrics_getXscale___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Size_Metrics*)metrics)->x_scale;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_SizeMetrics_getYscale___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Size_Metrics*)metrics)->x_scale;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_SizeMetrics_getAscender___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Size_Metrics*)metrics)->ascender;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_SizeMetrics_getDescender___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Size_Metrics*)metrics)->descender;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_SizeMetrics_getHeight___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Size_Metrics*)metrics)->height;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_SizeMetrics_getMaxAdvance___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Size_Metrics*)metrics)->max_advance;
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getMetrics___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot) {
    return (jlong)&((FT_GlyphSlot)slot)->metrics;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getLinearHoriAdvance___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot) {
    return ((FT_GlyphSlot)slot)->linearHoriAdvance;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getLinearVertAdvance___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot) {
    return ((FT_GlyphSlot)slot)->linearVertAdvance;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getAdvanceX___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot) {
    return ((FT_GlyphSlot)slot)->advance.x;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getAdvanceY___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot) {
    return ((FT_GlyphSlot)slot)->advance.y;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getFormat___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot) {
    return ((FT_GlyphSlot)slot)->format;
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getBitmap___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot) {
    FT_GlyphSlot glyph = ((FT_GlyphSlot)slot);
    return (jlong)&(glyph->bitmap);
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getBitmapLeft___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot) {
    return ((FT_GlyphSlot)slot)->bitmap_left;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getBitmapTop___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot) {
    return ((FT_GlyphSlot)slot)->bitmap_top;
}

extern "C" JAVA_BOOLEAN com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_renderGlyph___long_int_R_boolean(CODENAME_ONE_THREAD_STATE, JAVA_LONG slot, JAVA_INT renderMode) {
    return !FT_Render_Glyph((FT_GlyphSlot)slot, (FT_Render_Mode)renderMode);
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphSlot_getGlyph___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG glyphSlot) {
    FT_Glyph glyph;
    FT_Error error = FT_Get_Glyph((FT_GlyphSlot)glyphSlot, &glyph);
    if(error) {
        lastError = error;
        return 0;
    }
    else return (jlong)glyph;
}

extern "C" JAVA_VOID com_badlogic_gdx_graphics_g2d_freetype_FreeType_Glyph_done___long(CODENAME_ONE_THREAD_STATE, JAVA_LONG glyph) {
    FT_Done_Glyph((FT_Glyph)glyph);
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_Glyph_strokeBorder___long_long_boolean_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG glyph, JAVA_LONG stroker, JAVA_BOOLEAN inside) {
    FT_Glyph border_glyph = (FT_Glyph)glyph;
    FT_Glyph_StrokeBorder(&border_glyph, (FT_Stroker)stroker, inside, 1);
    return (jlong)border_glyph;
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_Glyph_toBitmap___long_int_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG glyph, JAVA_INT renderMode) {
    FT_Glyph bitmap = (FT_Glyph)glyph;
    FT_Error error = FT_Glyph_To_Bitmap(&bitmap, (FT_Render_Mode)renderMode, NULL, 1);
    if(error) {
        lastError = error;
        return 0;
    }
    return (jlong)bitmap;
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_Glyph_getBitmap___long_R_long(CODENAME_ONE_THREAD_STATE, JAVA_LONG glyph) {
    FT_BitmapGlyph glyph_bitmap = ((FT_BitmapGlyph)glyph);
    return (jlong)&(glyph_bitmap->bitmap);
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Glyph_getLeft___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG glyph) {
    FT_BitmapGlyph glyph_bitmap = ((FT_BitmapGlyph)glyph);
    return glyph_bitmap->left;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Glyph_getTop___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG glyph) {
    FT_BitmapGlyph glyph_bitmap = ((FT_BitmapGlyph)glyph);
    return glyph_bitmap->top;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Bitmap_getRows___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG bitmap) {
    return ((FT_Bitmap*)bitmap)->rows;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Bitmap_getWidth___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG bitmap) {
    return ((FT_Bitmap*)bitmap)->width;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Bitmap_getPitch___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG bitmap) {
    return ((FT_Bitmap*)bitmap)->pitch;
}

extern "C" JAVA_OBJECT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Bitmap_getBuffer___long_R_java_nio_ByteBuffer(CODENAME_ONE_THREAD_STATE, JAVA_LONG bitmap) {
    FT_Bitmap *bmp = (FT_Bitmap *) bitmap;
//    return env->NewDirectByteBuffer((void*)bmp->buffer, bmp->rows * abs(bmp->pitch));
    auto buffer = __NEW_java_nio_ByteBuffer(threadStateData);
    java_nio_ByteBuffer___INIT_____long_int_boolean(threadStateData, buffer, (long) bmp->buffer, bmp->rows * abs(bmp->pitch), false);
    return buffer;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Bitmap_getNumGray___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG bitmap) {
    return ((FT_Bitmap*)bitmap)->num_grays;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_Bitmap_getPixelMode___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG bitmap) {
    return ((FT_Bitmap*)bitmap)->pixel_mode;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphMetrics_getWidth___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Glyph_Metrics*)metrics)->width;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphMetrics_getHeight___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Glyph_Metrics*)metrics)->height;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphMetrics_getHoriBearingX___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Glyph_Metrics*)metrics)->horiBearingX;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphMetrics_getHoriBearingY___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Glyph_Metrics*)metrics)->horiBearingY;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphMetrics_getHoriAdvance___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Glyph_Metrics*)metrics)->horiAdvance;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphMetrics_getVertBearingX___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Glyph_Metrics*)metrics)->vertBearingX;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphMetrics_getVertBearingY___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Glyph_Metrics*)metrics)->vertBearingY;
}

extern "C" JAVA_INT com_badlogic_gdx_graphics_g2d_freetype_FreeType_GlyphMetrics_getVertAdvance___long_R_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG metrics) {
    return ((FT_Glyph_Metrics*)metrics)->vertAdvance;
}

extern "C" JAVA_VOID com_badlogic_gdx_graphics_g2d_freetype_FreeType_Stroker_set___long_int_int_int_int(CODENAME_ONE_THREAD_STATE, JAVA_LONG stroker, JAVA_INT radius, JAVA_INT lineCap, JAVA_INT lineJoin, JAVA_INT miterLimit) {
    FT_Stroker_Set((FT_Stroker)stroker, radius, (FT_Stroker_LineCap)lineCap, (FT_Stroker_LineJoin)lineJoin, miterLimit);
}

extern "C" JAVA_VOID com_badlogic_gdx_graphics_g2d_freetype_FreeType_Stroker_done___long(CODENAME_ONE_THREAD_STATE, JAVA_LONG stroker) {
    FT_Stroker_Done((FT_Stroker)stroker);
}

extern "C" JAVA_LONG com_badlogic_gdx_graphics_g2d_freetype_FreeType_initFreeTypeJni___R_long(CODENAME_ONE_THREAD_STATE) {
    FT_Library library = 0;
    FT_Error error = FT_Init_FreeType(&library);
    if(error) {
        lastError = error;
        return 0;
    }
    else return (jlong)library;
}

