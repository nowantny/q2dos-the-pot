#ifndef GLINTERNAL_H_included
#define GLINTERNAL_H_included

typedef GLfloat GLfloat4[4];

/* unapproved stuff (to be moved in gl.h when ready) */

#define GL_TEXTURE_BORDER_COLOR			0x1004

#define GL_POINT_SMOOTH				0x0B10

#define GL_TEXTURE_RECTANGLE_ARB		0x84F5

#define GL_STENCIL_BITS				0x0D57
#define GL_ALPHA_BITS				0x0D55
#define GL_RED_BITS				0x0D52
#define GL_GREEN_BITS				0x0D53
#define GL_BLUE_BITS				0x0D54

/* UT2003 woes */
#define GL_TEXTURE_WRAP_R			0x8072
#define GL_TEXTURE_CUBE_MAP			0x8513
#define GL_COMBINE_RGB				0x8571
#define GL_COMBINE_ALPHA			0x8572
#define GL_RGB_SCALE				0x8573
#define GL_ALPHA_SCALE				0x0D1C
#define GL_SOURCE0_RGB				0x8580
#define GL_SOURCE1_RGB				0x8581
#define GL_SOURCE2_RGB				0x8582
#define GL_SOURCE0_ALPHA			0x8588
#define GL_SOURCE1_ALPHA			0x8589
#define GL_SOURCE2_ALPHA			0x858A
#define GL_OPERAND0_RGB				0x8590
#define GL_OPERAND1_RGB				0x8591
#define GL_OPERAND2_RGB				0x8592
#define GL_OPERAND0_ALPHA			0x8598
#define GL_OPERAND1_ALPHA			0x8599
#define GL_OPERAND2_ALPHA			0x859A
#define GL_CONSTANT				0x8576
#define GL_PRIMARY_COLOR			0x8577
#define GL_PREVIOUS				0x8578
#define GL_INTERPOLATE				0x8575

/* texture compression */
#define GL_COMPRESSED_RGB			0x84ED
#define GL_COMPRESSED_RGBA			0x84EE
#define GL_RGB_S3TC				0x83A0
#define GL_RGB4_S3TC				0x83A1
#define GL_RGBA_S3TC				0x83A2
#define GL_RGBA4_S3TC				0x83A3
#define GL_COMPRESSED_RGB_FXT1_3DFX		0x86B0
#define GL_COMPRESSED_RGBA_FXT1_3DFX		0x86B1
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT		0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT	0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT	0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT	0x83F3

/* Buffers, Pixel Drawing/Reading */
#define GL_NONE					0x0
#define GL_LEFT					0x0406
#define GL_RIGHT				0x0407
/*GL_FRONT					0x0404 */
/*GL_BACK					0x0405 */
/*GL_FRONT_AND_BACK				0x0408 */
#define GL_FRONT_LEFT				0x0400
#define GL_FRONT_RIGHT				0x0401
#define GL_BACK_LEFT				0x0402
#define GL_BACK_RIGHT				0x0403

#define GL_DEPTH_COMPONENT			0x1902

#define GL_MAX_TEXTURE_COORDS_ARB		0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB		0x8872

/* SWKotOR2 */
#define GL_TEXTURE_MAX_ANISOTROPY_EXT		0x84FE

#define GL_COLOR_CLEAR_VALUE			0x0C22

#define GL_ENABLE_BIT				0x00002000

#define GL_DEPTH_WRITEMASK			0x0B72

/* Homeworld2 */
#define GL_INDEX_ARRAY				0x8077

#endif
