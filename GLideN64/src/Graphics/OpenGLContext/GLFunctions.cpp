#ifdef __LIBRETRO__
#include <glsm/glsmsym.h>
#define NO_GL_WRAP 1
#endif

#include "GLFunctions.h"

#define ASSIGN_PROC_ADR(proc_type, proc_name) ptr##proc_name = gl##proc_name

#ifdef OS_WINDOWS

#define glGetProcAddress wglGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) ptr##proc_name = (proc_type) glGetProcAddress("gl"#proc_name)

#elif defined(VERO4K) || defined(ODROID) || defined(VC) || defined(AMLOGIC)

#include <dlfcn.h>
#define GL_GET_PROC_ADR(proc_type, proc_name) ptr##proc_name = (proc_type) dlsym(gles2so, "gl"#proc_name);

#elif defined(EGL)

#define glGetProcAddress eglGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) ptr##proc_name = (proc_type) glGetProcAddress("gl"#proc_name)
#define GL_GET_PROC_ADR_EGL(proc_type, proc_name) ptr##proc_name = (proc_type) glGetProcAddress("egl"#proc_name)

#elif defined(OS_LINUX)

#include <X11/Xutil.h>
typedef XID GLXContextID;
typedef XID GLXPixmap;
typedef XID GLXDrawable;
typedef XID GLXPbuffer;
typedef XID GLXWindow;
typedef XID GLXFBConfigID;
typedef struct __GLXcontextRec *GLXContext;
typedef struct __GLXFBConfigRec *GLXFBConfig;
#define GLX_GLXEXT_PROTOTYPES
#include <GL/glxext.h>
#define glGetProcAddress glXGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) ptr##proc_name = (proc_type) glGetProcAddress((const GLubyte*)#proc_name)

#elif defined(OS_MAC_OS_X)
#include <dlfcn.h>

static void* AppleGLGetProcAddress (const char *name)
{
	static void* image = NULL;
	if (NULL == image)
		image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);

	return (image ? dlsym(image, name) : NULL);
}
#define glGetProcAddress AppleGLGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) ptr##proc_name = (proc_type) glGetProcAddress(#proc_name)

#elif defined(OS_IOS)
#include <dlfcn.h>

static void* IOSGLGetProcAddress (const char *name)
{
    return dlsym(RTLD_DEFAULT, name);
}

#define glGetProcAddress IOSGLGetProcAddress
#define GL_GET_PROC_ADR(proc_type, proc_name) ptr##proc_name = (proc_type)glGetProcAddress(#proc_name)

#endif

//GL Fucntions
PFNGLBLENDFUNCPROC ptrBlendFunc;
PFNGLPIXELSTOREIPROC ptrPixelStorei;
PFNGLCLEARCOLORPROC ptrClearColor;
PFNGLCULLFACEPROC ptrCullFace;
PFNGLDEPTHFUNCPROC ptrDepthFunc;
PFNGLDEPTHMASKPROC ptrDepthMask;
PFNGLDISABLEPROC ptrDisable;
PFNGLENABLEPROC ptrEnable;
PFNGLPOLYGONOFFSETPROC ptrPolygonOffset;
PFNGLSCISSORPROC ptrScissor;
PFNGLVIEWPORTPROC ptrViewport;
PFNGLBINDTEXTUREPROC ptrBindTexture;
PFNGLTEXIMAGE2DPROC ptrTexImage2D;
PFNGLTEXPARAMETERIPROC ptrTexParameteri;
PFNGLGETINTEGERVPROC ptrGetIntegerv;
PFNGLGETSTRINGPROC ptrGetString;
PFNGLREADPIXELSPROC ptrReadPixels;
PFNGLTEXSUBIMAGE2DPROC ptrTexSubImage2D;
PFNGLDRAWARRAYSPROC ptrDrawArrays;
PFNGLGETERRORPROC ptrGetError;
PFNGLDRAWELEMENTSPROC ptrDrawElements;
PFNGLLINEWIDTHPROC ptrLineWidth;
PFNGLCLEARPROC ptrClear;
PFNGLGETFLOATVPROC ptrGetFloatv;
PFNGLDELETETEXTURESPROC ptrDeleteTextures;
PFNGLGENTEXTURESPROC ptrGenTextures;
PFNGLTEXPARAMETERFPROC ptrTexParameterf;
PFNGLACTIVETEXTUREPROC ptrActiveTexture;
PFNGLBLENDCOLORPROC ptrBlendColor;
PFNGLREADBUFFERPROC ptrReadBuffer;
PFNGLFINISHPROC ptrFinish;
#if defined(OS_ANDROID)
PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC ptrGetNativeClientBufferANDROID;
#endif

PFNGLCREATESHADERPROC ptrCreateShader;
PFNGLCOMPILESHADERPROC ptrCompileShader;
PFNGLSHADERSOURCEPROC ptrShaderSource;
PFNGLCREATEPROGRAMPROC ptrCreateProgram;
PFNGLATTACHSHADERPROC ptrAttachShader;
PFNGLLINKPROGRAMPROC ptrLinkProgram;
PFNGLUSEPROGRAMPROC ptrUseProgram;
PFNGLGETUNIFORMLOCATIONPROC ptrGetUniformLocation;
PFNGLUNIFORM1IPROC ptrUniform1i;
PFNGLUNIFORM1FPROC ptrUniform1f;
PFNGLUNIFORM2FPROC ptrUniform2f;
PFNGLUNIFORM2IPROC ptrUniform2i;
PFNGLUNIFORM4IPROC ptrUniform4i;
PFNGLUNIFORM4FPROC ptrUniform4f;
PFNGLUNIFORM3FVPROC ptrUniform3fv;
PFNGLUNIFORM4FVPROC ptrUniform4fv;
PFNGLDETACHSHADERPROC ptrDetachShader;
PFNGLDELETESHADERPROC ptrDeleteShader;
PFNGLDELETEPROGRAMPROC ptrDeleteProgram;
PFNGLGETPROGRAMINFOLOGPROC ptrGetProgramInfoLog;
PFNGLGETSHADERINFOLOGPROC ptrGetShaderInfoLog;
PFNGLGETSHADERIVPROC ptrGetShaderiv;
PFNGLGETPROGRAMIVPROC ptrGetProgramiv;

PFNGLENABLEVERTEXATTRIBARRAYPROC ptrEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC ptrDisableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC ptrVertexAttribPointer;
PFNGLBINDATTRIBLOCATIONPROC ptrBindAttribLocation;
PFNGLVERTEXATTRIB1FPROC ptrVertexAttrib1f;
PFNGLVERTEXATTRIB4FPROC ptrVertexAttrib4f;
PFNGLVERTEXATTRIB4FVPROC ptrVertexAttrib4fv;

// multitexture functions
PFNGLDEPTHRANGEFPROC ptrDepthRangef;
PFNGLCLEARDEPTHFPROC ptrClearDepthf;

PFNGLDRAWBUFFERSPROC ptrDrawBuffers;
PFNGLBINDFRAMEBUFFERPROC ptrBindFramebuffer;
PFNGLDELETEFRAMEBUFFERSPROC ptrDeleteFramebuffers;
PFNGLGENFRAMEBUFFERSPROC ptrGenFramebuffers;
PFNGLFRAMEBUFFERTEXTURE2DPROC ptrFramebufferTexture2D;
PFNGLTEXIMAGE2DMULTISAMPLEPROC ptrTexImage2DMultisample;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC ptrTexStorage2DMultisample;
PFNGLGENRENDERBUFFERSPROC ptrGenRenderbuffers;
PFNGLBINDRENDERBUFFERPROC ptrBindRenderbuffer;
PFNGLRENDERBUFFERSTORAGEPROC ptrRenderbufferStorage;
PFNGLFRAMEBUFFERRENDERBUFFERPROC ptrFramebufferRenderbuffer;
PFNGLDELETERENDERBUFFERSPROC ptrDeleteRenderbuffers;
PFNGLCHECKFRAMEBUFFERSTATUSPROC ptrCheckFramebufferStatus;
PFNGLBLITFRAMEBUFFERPROC ptrBlitFramebuffer;
PFNGLGENVERTEXARRAYSPROC ptrGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC ptrBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC ptrDeleteVertexArrays;
PFNGLGENBUFFERSPROC ptrGenBuffers;
PFNGLBINDBUFFERPROC ptrBindBuffer;
PFNGLBUFFERDATAPROC ptrBufferData;
PFNGLMAPBUFFERPROC ptrMapBuffer;
PFNGLMAPBUFFERRANGEPROC ptrMapBufferRange;
PFNGLUNMAPBUFFERPROC ptrUnmapBuffer;
PFNGLDELETEBUFFERSPROC ptrDeleteBuffers;
PFNGLBINDIMAGETEXTUREPROC ptrBindImageTexture;
PFNGLMEMORYBARRIERPROC ptrMemoryBarrier;
PFNGLGETSTRINGIPROC ptrGetStringi;
PFNGLINVALIDATEFRAMEBUFFERPROC ptrInvalidateFramebuffer;
PFNGLBUFFERSTORAGEPROC ptrBufferStorage;
PFNGLFENCESYNCPROC ptrFenceSync;
PFNGLCLIENTWAITSYNCPROC ptrClientWaitSync;
PFNGLDELETESYNCPROC ptrDeleteSync;

PFNGLGETUNIFORMBLOCKINDEXPROC ptrGetUniformBlockIndex;
PFNGLUNIFORMBLOCKBINDINGPROC ptrUniformBlockBinding;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC ptrGetActiveUniformBlockiv;
PFNGLGETUNIFORMINDICESPROC ptrGetUniformIndices;
PFNGLGETACTIVEUNIFORMSIVPROC ptrGetActiveUniformsiv;
PFNGLBINDBUFFERBASEPROC ptrBindBufferBase;
PFNGLBUFFERSUBDATAPROC ptrBufferSubData;

PFNGLGETPROGRAMBINARYPROC ptrGetProgramBinary;
PFNGLPROGRAMBINARYPROC ptrProgramBinary;
PFNGLPROGRAMPARAMETERIPROC ptrProgramParameteri;

PFNGLTEXSTORAGE2DPROC ptrTexStorage2D;
PFNGLTEXTURESTORAGE2DPROC ptrTextureStorage2D;
PFNGLTEXTURESUBIMAGE2DPROC ptrTextureSubImage2D;
PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC ptrTextureStorage2DMultisample;
PFNGLTEXTUREPARAMETERIPROC ptrTextureParameteri;
PFNGLTEXTUREPARAMETERFPROC ptrTextureParameterf;
PFNGLCREATETEXTURESPROC ptrCreateTextures;
PFNGLCREATEBUFFERSPROC ptrCreateBuffers;
PFNGLCREATEFRAMEBUFFERSPROC ptrCreateFramebuffers;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC ptrNamedFramebufferTexture;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC ptrDrawRangeElementsBaseVertex;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC ptrFlushMappedBufferRange;
PFNGLTEXTUREBARRIERPROC ptrTextureBarrier;
PFNGLTEXTUREBARRIERNVPROC ptrTextureBarrierNV;
PFNGLCLEARBUFFERFVPROC ptrClearBufferfv;
PFNGLENABLEIPROC ptrEnablei;
PFNGLDISABLEIPROC ptrDisablei;
PFNGLEGLIMAGETARGETTEXTURE2DOESPROC ptrEGLImageTargetTexture2DOES;

extern "C" void initGLFunctions()
{
#ifdef VC
	void *gles2so = dlopen("/opt/vc/lib/libbrcmGLESv2.so", RTLD_NOW);
#elif defined(ODROID)
	void *gles2so = dlopen("/usr/lib/arm-linux-gnueabihf/libGLESv2.so", RTLD_NOW);
#elif defined(VERO4K)
       void *gles2so = dlopen("/opt/vero3/lib/libGLESv2.so", RTLD_NOW);
#elif defined(AMLOGIC)
       void *gles2so = dlopen("/usr/lib/libGLESv2.so", RTLD_NOW);
#endif

#if defined(EGL) || defined(OS_IOS)
	ASSIGN_PROC_ADR(PFNGLBLENDFUNCPROC, BlendFunc);
	ASSIGN_PROC_ADR(PFNGLPIXELSTOREIPROC, PixelStorei);
	ASSIGN_PROC_ADR(PFNGLCLEARCOLORPROC, ClearColor);
	ASSIGN_PROC_ADR(PFNGLCULLFACEPROC, CullFace);
	ASSIGN_PROC_ADR(PFNGLDEPTHFUNCPROC, DepthFunc);
	ASSIGN_PROC_ADR(PFNGLDEPTHMASKPROC, DepthMask);
	GL_GET_PROC_ADR(PFNGLDISABLEPROC, Disable);
	GL_GET_PROC_ADR(PFNGLENABLEPROC, Enable);
	ASSIGN_PROC_ADR(PFNGLPOLYGONOFFSETPROC, PolygonOffset);
	ASSIGN_PROC_ADR(PFNGLSCISSORPROC, Scissor);
	ASSIGN_PROC_ADR(PFNGLVIEWPORTPROC, Viewport);
	ASSIGN_PROC_ADR(PFNGLBINDTEXTUREPROC, BindTexture);
	GL_GET_PROC_ADR(PFNGLTEXIMAGE2DPROC, TexImage2D);
	GL_GET_PROC_ADR(PFNGLTEXPARAMETERIPROC, TexParameteri);
	GL_GET_PROC_ADR(PFNGLGETINTEGERVPROC, GetIntegerv);
	GL_GET_PROC_ADR(PFNGLGETSTRINGPROC, GetString);
	ASSIGN_PROC_ADR(PFNGLREADPIXELSPROC, ReadPixels);
	ASSIGN_PROC_ADR(PFNGLTEXSUBIMAGE2DPROC, TexSubImage2D);
	ASSIGN_PROC_ADR(PFNGLDRAWARRAYSPROC, DrawArrays);
	ASSIGN_PROC_ADR(PFNGLGETERRORPROC, GetError);
	ASSIGN_PROC_ADR(PFNGLDRAWELEMENTSPROC, DrawElements);
	ASSIGN_PROC_ADR(PFNGLLINEWIDTHPROC, LineWidth);
	ASSIGN_PROC_ADR(PFNGLCLEARPROC, Clear);
	GL_GET_PROC_ADR(PFNGLGETFLOATVPROC, GetFloatv);
	ASSIGN_PROC_ADR(PFNGLDELETETEXTURESPROC, DeleteTextures);
	ASSIGN_PROC_ADR(PFNGLGENTEXTURESPROC, GenTextures);
	GL_GET_PROC_ADR(PFNGLTEXPARAMETERFPROC, TexParameterf);
	ASSIGN_PROC_ADR(PFNGLACTIVETEXTUREPROC, ActiveTexture);
	ASSIGN_PROC_ADR(PFNGLBLENDCOLORPROC, BlendColor);
	ASSIGN_PROC_ADR(PFNGLREADBUFFERPROC, ReadBuffer);
	GL_GET_PROC_ADR(PFNGLFINISHPROC, Finish);
#if defined(OS_ANDROID)
	GL_GET_PROC_ADR_EGL(PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC, GetNativeClientBufferANDROID);
#endif
#else
	ASSIGN_PROC_ADR(PFNGLACTIVETEXTUREPROC, ActiveTexture);
	ASSIGN_PROC_ADR(PFNGLBLENDCOLORPROC, BlendColor);
	ASSIGN_PROC_ADR(PFNGLBLENDFUNCPROC, BlendFunc);
	ASSIGN_PROC_ADR(PFNGLPIXELSTOREIPROC, PixelStorei);
	ASSIGN_PROC_ADR(PFNGLCLEARCOLORPROC, ClearColor);
	ASSIGN_PROC_ADR(PFNGLCULLFACEPROC, CullFace);
	ASSIGN_PROC_ADR(PFNGLDEPTHFUNCPROC, DepthFunc);
	ASSIGN_PROC_ADR(PFNGLDEPTHMASKPROC, DepthMask);
	ASSIGN_PROC_ADR(PFNGLDISABLEPROC, Disable);
	ASSIGN_PROC_ADR(PFNGLENABLEPROC, Enable);
	ASSIGN_PROC_ADR(PFNGLPOLYGONOFFSETPROC, PolygonOffset);
	ASSIGN_PROC_ADR(PFNGLSCISSORPROC, Scissor);
	ASSIGN_PROC_ADR(PFNGLVIEWPORTPROC, Viewport);
	ASSIGN_PROC_ADR(PFNGLBINDTEXTUREPROC, BindTexture);
	GL_GET_PROC_ADR(PFNGLTEXIMAGE2DPROC, TexImage2D);
	ASSIGN_PROC_ADR(PFNGLTEXPARAMETERIPROC, TexParameteri);
	ASSIGN_PROC_ADR(PFNGLGETINTEGERVPROC, GetIntegerv);
	ASSIGN_PROC_ADR(PFNGLGETSTRINGPROC, GetString);
	ASSIGN_PROC_ADR(PFNGLREADPIXELSPROC, ReadPixels);
	ASSIGN_PROC_ADR(PFNGLTEXSUBIMAGE2DPROC, TexSubImage2D);
	ASSIGN_PROC_ADR(PFNGLDRAWARRAYSPROC, DrawArrays);
	ASSIGN_PROC_ADR(PFNGLGETERRORPROC, GetError);
	ASSIGN_PROC_ADR(PFNGLDRAWELEMENTSPROC, DrawElements);
	ASSIGN_PROC_ADR(PFNGLLINEWIDTHPROC, LineWidth);
	ASSIGN_PROC_ADR(PFNGLCLEARPROC, Clear);
	ASSIGN_PROC_ADR(PFNGLGETFLOATVPROC, GetFloatv);
	ASSIGN_PROC_ADR(PFNGLDELETETEXTURESPROC, DeleteTextures);
	ASSIGN_PROC_ADR(PFNGLGENTEXTURESPROC, GenTextures);
	GL_GET_PROC_ADR(PFNGLTEXPARAMETERFPROC, TexParameterf);
	ASSIGN_PROC_ADR(PFNGLREADBUFFERPROC, ReadBuffer);
	ASSIGN_PROC_ADR(PFNGLFINISHPROC, Finish);
#endif

	ASSIGN_PROC_ADR(PFNGLCREATESHADERPROC, CreateShader);
	ASSIGN_PROC_ADR(PFNGLCOMPILESHADERPROC, CompileShader);
	ASSIGN_PROC_ADR(PFNGLSHADERSOURCEPROC, ShaderSource);
	ASSIGN_PROC_ADR(PFNGLCREATEPROGRAMPROC, CreateProgram);
	ASSIGN_PROC_ADR(PFNGLATTACHSHADERPROC, AttachShader);
	ASSIGN_PROC_ADR(PFNGLLINKPROGRAMPROC, LinkProgram);
	ASSIGN_PROC_ADR(PFNGLUSEPROGRAMPROC, UseProgram);
	ASSIGN_PROC_ADR(PFNGLGETUNIFORMLOCATIONPROC, GetUniformLocation);
	ASSIGN_PROC_ADR(PFNGLUNIFORM1IPROC, Uniform1i);
	ASSIGN_PROC_ADR(PFNGLUNIFORM1FPROC, Uniform1f);
	ASSIGN_PROC_ADR(PFNGLUNIFORM2FPROC, Uniform2f);
	ASSIGN_PROC_ADR(PFNGLUNIFORM2IPROC, Uniform2i);
	ASSIGN_PROC_ADR(PFNGLUNIFORM4IPROC, Uniform4i);
	ASSIGN_PROC_ADR(PFNGLUNIFORM4FPROC, Uniform4f);
	ASSIGN_PROC_ADR(PFNGLUNIFORM3FVPROC, Uniform3fv);
	ASSIGN_PROC_ADR(PFNGLUNIFORM4FVPROC, Uniform4fv);
	ASSIGN_PROC_ADR(PFNGLDETACHSHADERPROC, DetachShader);
	ASSIGN_PROC_ADR(PFNGLDELETESHADERPROC, DeleteShader);
	ASSIGN_PROC_ADR(PFNGLDELETEPROGRAMPROC, DeleteProgram);
	ASSIGN_PROC_ADR(PFNGLGETPROGRAMINFOLOGPROC, GetProgramInfoLog);
	ASSIGN_PROC_ADR(PFNGLGETSHADERINFOLOGPROC, GetShaderInfoLog);
	ASSIGN_PROC_ADR(PFNGLGETSHADERIVPROC, GetShaderiv);
	ASSIGN_PROC_ADR(PFNGLGETPROGRAMIVPROC, GetProgramiv);

	ASSIGN_PROC_ADR(PFNGLENABLEVERTEXATTRIBARRAYPROC, EnableVertexAttribArray);
	ASSIGN_PROC_ADR(PFNGLDISABLEVERTEXATTRIBARRAYPROC, DisableVertexAttribArray);
	ASSIGN_PROC_ADR(PFNGLVERTEXATTRIBPOINTERPROC, VertexAttribPointer);
	ASSIGN_PROC_ADR(PFNGLBINDATTRIBLOCATIONPROC, BindAttribLocation);
	GL_GET_PROC_ADR(PFNGLVERTEXATTRIB1FPROC, VertexAttrib1f);
	ASSIGN_PROC_ADR(PFNGLVERTEXATTRIB4FPROC, VertexAttrib4f);
	ASSIGN_PROC_ADR(PFNGLVERTEXATTRIB4FVPROC, VertexAttrib4fv);

	GL_GET_PROC_ADR(PFNGLDEPTHRANGEFPROC, DepthRangef);
	GL_GET_PROC_ADR(PFNGLCLEARDEPTHFPROC, ClearDepthf);

	ASSIGN_PROC_ADR(PFNGLDRAWBUFFERSPROC, DrawBuffers);
	ASSIGN_PROC_ADR(PFNGLBINDFRAMEBUFFERPROC, BindFramebuffer);
	ASSIGN_PROC_ADR(PFNGLDELETEFRAMEBUFFERSPROC, DeleteFramebuffers);
	ASSIGN_PROC_ADR(PFNGLGENFRAMEBUFFERSPROC, GenFramebuffers);
	ASSIGN_PROC_ADR(PFNGLFRAMEBUFFERTEXTURE2DPROC, FramebufferTexture2D);
	ASSIGN_PROC_ADR(PFNGLTEXIMAGE2DMULTISAMPLEPROC, TexImage2DMultisample);
	ASSIGN_PROC_ADR(PFNGLTEXSTORAGE2DMULTISAMPLEPROC, TexStorage2DMultisample);
	ASSIGN_PROC_ADR(PFNGLGENRENDERBUFFERSPROC, GenRenderbuffers);
	ASSIGN_PROC_ADR(PFNGLBINDRENDERBUFFERPROC, BindRenderbuffer);
	ASSIGN_PROC_ADR(PFNGLRENDERBUFFERSTORAGEPROC, RenderbufferStorage);
	ASSIGN_PROC_ADR(PFNGLFRAMEBUFFERRENDERBUFFERPROC, FramebufferRenderbuffer);
	GL_GET_PROC_ADR(PFNGLDELETERENDERBUFFERSPROC, DeleteRenderbuffers);
	ASSIGN_PROC_ADR(PFNGLCHECKFRAMEBUFFERSTATUSPROC, CheckFramebufferStatus);
	ASSIGN_PROC_ADR(PFNGLBLITFRAMEBUFFERPROC, BlitFramebuffer);
	ASSIGN_PROC_ADR(PFNGLGENVERTEXARRAYSPROC, GenVertexArrays);
	ASSIGN_PROC_ADR(PFNGLBINDVERTEXARRAYPROC, BindVertexArray);
	ASSIGN_PROC_ADR(PFNGLDELETEVERTEXARRAYSPROC, DeleteVertexArrays);
	ASSIGN_PROC_ADR(PFNGLGENBUFFERSPROC, GenBuffers);
	ASSIGN_PROC_ADR(PFNGLBINDBUFFERPROC, BindBuffer);
	ASSIGN_PROC_ADR(PFNGLBUFFERDATAPROC, BufferData);
	ASSIGN_PROC_ADR(PFNGLMAPBUFFERPROC, MapBuffer);
	ASSIGN_PROC_ADR(PFNGLMAPBUFFERRANGEPROC, MapBufferRange);
	ASSIGN_PROC_ADR(PFNGLUNMAPBUFFERPROC, UnmapBuffer);
	ASSIGN_PROC_ADR(PFNGLDELETEBUFFERSPROC, DeleteBuffers);
	ASSIGN_PROC_ADR(PFNGLBINDIMAGETEXTUREPROC, BindImageTexture);
	ASSIGN_PROC_ADR(PFNGLMEMORYBARRIERPROC, MemoryBarrier);
	ASSIGN_PROC_ADR(PFNGLGETSTRINGIPROC, GetStringi);
	GL_GET_PROC_ADR(PFNGLINVALIDATEFRAMEBUFFERPROC, InvalidateFramebuffer);
	ASSIGN_PROC_ADR(PFNGLBUFFERSTORAGEPROC, BufferStorage);
	ASSIGN_PROC_ADR(PFNGLFENCESYNCPROC, FenceSync);
	ASSIGN_PROC_ADR(PFNGLCLIENTWAITSYNCPROC, ClientWaitSync);
	ASSIGN_PROC_ADR(PFNGLDELETESYNCPROC, DeleteSync);

	ASSIGN_PROC_ADR(PFNGLGETUNIFORMBLOCKINDEXPROC, GetUniformBlockIndex);
	ASSIGN_PROC_ADR(PFNGLUNIFORMBLOCKBINDINGPROC, UniformBlockBinding);
	ASSIGN_PROC_ADR(PFNGLGETACTIVEUNIFORMBLOCKIVPROC, GetActiveUniformBlockiv);
	ASSIGN_PROC_ADR(PFNGLGETUNIFORMINDICESPROC, GetUniformIndices);
	ASSIGN_PROC_ADR(PFNGLGETACTIVEUNIFORMSIVPROC, GetActiveUniformsiv);
	ASSIGN_PROC_ADR(PFNGLBINDBUFFERBASEPROC, BindBufferBase);
	ASSIGN_PROC_ADR(PFNGLBUFFERSUBDATAPROC, BufferSubData);

	ASSIGN_PROC_ADR(PFNGLGETPROGRAMBINARYPROC, GetProgramBinary);
	ASSIGN_PROC_ADR(PFNGLPROGRAMBINARYPROC, ProgramBinary);
	ASSIGN_PROC_ADR(PFNGLPROGRAMPARAMETERIPROC, ProgramParameteri);

	ASSIGN_PROC_ADR(PFNGLTEXSTORAGE2DPROC, TexStorage2D);
	GL_GET_PROC_ADR(PFNGLTEXTURESTORAGE2DPROC, TextureStorage2D);
	GL_GET_PROC_ADR(PFNGLTEXTURESUBIMAGE2DPROC, TextureSubImage2D);
	GL_GET_PROC_ADR(PFNGLTEXTURESTORAGE2DMULTISAMPLEEXTPROC, TextureStorage2DMultisample);

	GL_GET_PROC_ADR(PFNGLTEXTUREPARAMETERIPROC, TextureParameteri);
	GL_GET_PROC_ADR(PFNGLTEXTUREPARAMETERFPROC, TextureParameterf);
	GL_GET_PROC_ADR(PFNGLCREATETEXTURESPROC, CreateTextures);
	GL_GET_PROC_ADR(PFNGLCREATEBUFFERSPROC, CreateBuffers);
	GL_GET_PROC_ADR(PFNGLCREATEFRAMEBUFFERSPROC, CreateFramebuffers);
	GL_GET_PROC_ADR(PFNGLNAMEDFRAMEBUFFERTEXTUREPROC, NamedFramebufferTexture);
	ASSIGN_PROC_ADR(PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC, DrawRangeElementsBaseVertex);
	ASSIGN_PROC_ADR(PFNGLFLUSHMAPPEDBUFFERRANGEPROC, FlushMappedBufferRange);
	GL_GET_PROC_ADR(PFNGLTEXTUREBARRIERPROC, TextureBarrier);
	GL_GET_PROC_ADR(PFNGLTEXTUREBARRIERNVPROC, TextureBarrierNV);
	ASSIGN_PROC_ADR(PFNGLCLEARBUFFERFVPROC, ClearBufferfv);
	GL_GET_PROC_ADR(PFNGLENABLEIPROC, Enablei);
	GL_GET_PROC_ADR(PFNGLDISABLEIPROC, Disablei);
	GL_GET_PROC_ADR(PFNGLEGLIMAGETARGETTEXTURE2DOESPROC, EGLImageTargetTexture2DOES);
}
