//
// math.s
// x86 assembly-language math routines.

#include "qasm.h"


#if	id386

	.data

	.text

#define	in	4
#define out	8

	.align 2
.globl C(TransformVector)
C(TransformVector):
	movl	in(%esp),%eax
	movl	out(%esp),%edx

	flds	(%eax)		// in[0]
	fmuls	C(vright)		// in[0]*vright[0]
	flds	(%eax)		// in[0] | in[0]*vright[0]
	fmuls	C(vup)		// in[0]*vup[0] | in[0]*vright[0]
	flds	(%eax)		// in[0] | in[0]*vup[0] | in[0]*vright[0]
	fmuls	C(vpn)		// in[0]*vpn[0] | in[0]*vup[0] | in[0]*vright[0]

	flds	4(%eax)		// in[1] | ...
	fmuls	C(vright)+4	// in[1]*vright[1] | ...
	flds	4(%eax)		// in[1] | in[1]*vright[1] | ...
	fmuls	C(vup)+4		// in[1]*vup[1] | in[1]*vright[1] | ...
	flds	4(%eax)		// in[1] | in[1]*vup[1] | in[1]*vright[1] | ...
	fmuls	C(vpn)+4		// in[1]*vpn[1] | in[1]*vup[1] | in[1]*vright[1] | ...
	fxch	%st(2)		// in[1]*vright[1] | in[1]*vup[1] | in[1]*vpn[1] | ...

	faddp	%st(0),%st(5)	// in[1]*vup[1] | in[1]*vpn[1] | ...
	faddp	%st(0),%st(3)	// in[1]*vpn[1] | ...
	faddp	%st(0),%st(1)	// vpn_accum | vup_accum | vright_accum

	flds	8(%eax)		// in[2] | ...
	fmuls	C(vright)+8	// in[2]*vright[2] | ...
	flds	8(%eax)		// in[2] | in[2]*vright[2] | ...
	fmuls	C(vup)+8		// in[2]*vup[2] | in[2]*vright[2] | ...
	flds	8(%eax)		// in[2] | in[2]*vup[2] | in[2]*vright[2] | ...
	fmuls	C(vpn)+8		// in[2]*vpn[2] | in[2]*vup[2] | in[2]*vright[2] | ...
	fxch	%st(2)		// in[2]*vright[2] | in[2]*vup[2] | in[2]*vpn[2] | ...

	faddp	%st(0),%st(5)	// in[2]*vup[2] | in[2]*vpn[2] | ...
	faddp	%st(0),%st(3)	// in[2]*vpn[2] | ...
	faddp	%st(0),%st(1)	// vpn_accum | vup_accum | vright_accum

	fstps	8(%edx)		// out[2]
	fstps	4(%edx)		// out[1]
	fstps	(%edx)		// out[0]

	ret

#endif	// id386
