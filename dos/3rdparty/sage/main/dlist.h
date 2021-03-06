#ifndef DLIST_H_included
#define DLIST_H_included

typedef enum {
    OP_INVALID = -1,
    OP_CONTINUE,

    OP_BEGIN,
    OP_END,
    OP_VERTEX2F,
    OP_VERTEX3F,
    OP_VERTEX4F,
    OP_COLOR3F,
    OP_COLOR4F,
    OP_SECONDARYCOLOR3F,
    OP_NORMAL3F,
    OP_TEXCOORD1F,
    OP_TEXCOORD2F,
    OP_TEXCOORD3F,
    OP_TEXCOORD4F,
    OP_MULTITEXCOORD1F,
    OP_MULTITEXCOORD2F,
    OP_MULTITEXCOORD3F,
    OP_MULTITEXCOORD4F,
    OP_MATERIALF,	/* kept as 1F */
    OP_MATERIALFV,	/* kept as 4F */
    OP_FOGCOORDF,
    OP_EDGEFLAG,
    OP_RECTF,

    OP_PUSHMATRIX,
    OP_POPMATRIX,
    OP_TRANSLATEF,
    OP_ROTATEF,
    OP_SCALEF,
    OP_LOADIDENTITY,
    OP_MATRIXMODE,

    OP_ENABLE,
    OP_DISABLE,
    OP_FRONTFACE,
    OP_SHADEMODEL,
    OP_CULLFACE,

    OP_BLENDFUNC,
    OP_DEPTHMASK,
    OP_DEPTHFUNC,
    OP_ALPHAFUNC,

    OP_BINDTEX,
    OP_ACTIVETEX,
    OP_TEXENV,
    OP_TEXGEN,
    OP_TEXPARAM,

    OP_CALLLIST,

    OP_EOL
} DL_OPCODE;

typedef union {
    DL_OPCODE op;
    GLint i;
    GLfloat f;
    void *p;
    void *next;
} DL_NODE;

DL_NODE *dlist_new_operation (DL_OPCODE op);

#endif
