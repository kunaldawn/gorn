#ifndef __gorn__Enums__
#define __gorn__Enums__

#include <gorn/gl/Base.hpp>
#include <cstddef>

namespace gorn
{
    enum class FrameBufferAttachType
    {
        Depth,
        Color,
        Stencil
    };

    enum class StencilFunction
    {
        Always,
        Never,
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        Equal,
        NotEqual
    };

    enum class StencilAction
    {
        Keep,
        Zero,
        Replace,
        Increment,
        IncrementWrap,
        Decrement,
        DecrementWrap,
        Invert
    };

    enum class ClearType
    {
        Color,
        Depth,
        Stencil
    };

    enum class CapabilityType
    {
        DepthTest,
        StencilTest
    };

    enum class MaskType
    {
        Depth,
        Red,
        Green,
        Blue,
        Alpha
    };

    enum class DrawMode
    {
        Quads,
        Triangles,
        Lines,
        Points
    };

    enum class BasicType
    {
        None,
        Float,
        Integer,
        UnsignedInteger,
        Byte,
        UnsignedByte,
        Short,
        UnsignedShort
    };

	enum class BlendFactor
	{
		None,
		Zero,
		One,
		SrcColor,
		OneMinusSrcColor,
		DstColor,
		OneMinusDstColor,
		SrcAlpha,
		OneMinusSrcAlpha,
		DstAlpha,
		OneMinusDstAlpha,
		ConstantColor,
		OneMinusConstantColor,
		ConstantAlpha,
		OneMinusConstantAlpha,
		SrcAlphaSaturate
	};

    size_t getBasicTypeSize(BasicType type);

    GLenum getGlDrawMode(DrawMode mode);
    GLenum getGlBasicType(BasicType type);

    StencilFunction getStencilFunctionFromGl(GLenum gl);
    GLenum getGlStencilFunction(StencilFunction func);
    StencilAction getStencilActionFromGl(GLenum gl);
    GLenum getGlStencilAction(StencilAction act);

    GLbitfield getGlClearBufferBit(ClearType type);
    GLenum getGlCapability(CapabilityType type);

	GLenum getGlBlendFactor(BlendFactor factor);
}

#endif
