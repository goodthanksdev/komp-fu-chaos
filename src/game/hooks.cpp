// Hooks for default.xbe. A strong definition replaces the recompiled function at that address.
#include "xdk/hle.h"

using namespace kernel;

// Library code that programs the GPU's registers through the miniport ([miniport] is the register base, which the
// runtime has none of): the tile slots (the game inlines D3DDevice_SetTile and calls these itself). They succeed
// doing nothing. Address, stack bytes popped.
#define KFC_STUB(addr, pops)          \
    X86_FUNC(sub_##addr) {            \
        (void)base;                   \
        ctx.eax = 0;                  \
        ctx.esp += 4 + (pops);        \
    }
KFC_STUB(002C1C1C, 0x20)  // the miniport's tile set: 8 arguments
KFC_STUB(002C1E08, 0xC)   // the miniport's tile release (miniport, index, ...): 0xC6D49 after clearing the slot at +0x1660

// DirectSound calls the runtime has no part for: their library code reads the voice of a buffer the runtime made.
KFC_STUB(00250142, 0xC)   // IDirectSoundBuffer_SetRolloffFactor (this, float, apply)

// 0x2B8DF0 (rt, depth, viewport) sets the render target in this XDK. The runtime's SetRenderTarget (rt, depth) does it
// and sets the viewport to the whole target, as the library constant 0x2C72AC {0, 0, max, max, 0, 1} asks; any other
// viewport (the game passes a copy of the current one to keep it, 640x240 in field mode) is set after it.
X86_EXTERN_FUNC(GUEST(D3DDevice_SetRenderTarget));
X86_EXTERN_FUNC(GUEST(D3DDevice_SetViewport));
X86_FUNC(sub_002B8DF0) {
    uint32_t ret = R32(ctx.esp), rt = R32(ctx.esp + 4), zs = R32(ctx.esp + 8), vp = R32(ctx.esp + 12);
    ctx.esp += 4;
    W32(ctx.esp, ret);
    W32(ctx.esp + 4, rt);
    W32(ctx.esp + 8, zs);
    GUEST(D3DDevice_SetRenderTarget)(ctx, base);
    if (vp && vp != 0x2C72AC) {
        // SetViewport(vp) returning to the same caller
        ctx.esp -= 8;
        W32(ctx.esp, ret);
        W32(ctx.esp + 4, vp);
        GUEST(D3DDevice_SetViewport)(ctx, base);
    }
}
