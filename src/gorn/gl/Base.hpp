#ifndef __gorn__Base__
#define __gorn__Base__

#ifdef GORN_PLATFORM_IOS
#import <OpenGLES/ES2/glext.h>

#define glClearDepth                glClearDepthf
#define glDeleteVertexArrays        glDeleteVertexArraysOES
#define glGenVertexArrays           glGenVertexArraysOES
#define glBindVertexArray           glBindVertexArrayOES
#define glMapBuffer                 glMapBufferOES
#define glUnmapBuffer               glUnmapBufferOES

#elif GORN_PLATFORM_ANDROID

#define glClearDepth                glClearDepthf
#define glDeleteVertexArrays        glDeleteVertexArraysOES
#define glGenVertexArrays           glGenVertexArraysOES
#define glBindVertexArray           glBindVertexArrayOES
#define glMapBuffer                 glMapBufferOES
#define glUnmapBuffer               glUnmapBufferOES
#define glDrawBuffers               glDrawBuffersOES

#define GL_DEPTH24_STENCIL8         GL_DEPTH24_STENCIL8_OES
#define GL_WRITE_ONLY               GL_WRITE_ONLY_OES


#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif

#include <GLES2/gl2platform.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

typedef char GLchar;

#ifndef GL_BGRA
#define GL_BGRA  0x80E1
#endif

extern PFNGLGENVERTEXARRAYSOESPROC    glGenVertexArraysOESEXT;
extern PFNGLBINDVERTEXARRAYOESPROC    glBindVertexArrayOESEXT;
extern PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT;

#define glGenVertexArraysOES        glGenVertexArraysOESEXT
#define glBindVertexArrayOES        glBindVertexArrayOESEXT
#define glDeleteVertexArraysOES     glDeleteVertexArraysOESEXT

void gornInitGlExtensions();

#elif GORN_PLATFORM_MACOS

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#define glClearDepth                glClearDepthf
#define glDeleteVertexArrays        glDeleteVertexArraysAPPLE
#define glGenVertexArrays           glGenVertexArraysAPPLE
#define glBindVertexArray           glBindVertexArrayAPPLE
#define glMapBuffer                 glMapBufferAPPLE
#define glUnmapBuffer               glUnmapBufferAPPLE

#else

#include <GL/glew.h>
#include <GL/gl.h>

#endif

namespace gorn
{
    void checkGlError(const char* what);
}

#endif
