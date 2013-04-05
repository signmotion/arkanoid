
	#ifndef PRCORE_CONFIGURE_HPP
	#error "NEVER manually include this header."
	#endif

	#define PRCORE_CONFIGURED

	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/Xatom.h>

	// ad-hoc, fix this in makefile
	#ifndef PRCORE_PLATFORM_LINUX
	#define PRCORE_PLATFORM_LINUX
	#endif

	#ifdef PRCORE_PLATFORM_LINUX
	#include <X11/extensions/XShm.h>
	#endif

	struct WindowHandle
	{
		Display*		display;
		Window			window;
		Cursor			cursor;
		Pixmap			pixmap;
		XVisualInfo		visual;
		Atom			deleteatom;

		#ifdef PRCORE_PLATFORM_LINUX

		GC gc;
		XImage* xImage; 
		XShmSegmentInfo* shmSegmentInfo;

		#endif
	};

	// misc

	#define PRCORE_EXPORT
	#define PRCORE_IMPORT
	#define PRAPI
	#define __cdecl

	// floating-point types

	#include "../src/extlib/openexr/Half/half.h"

	typedef half                float16;
	typedef float               float32;
	typedef double				float64;

	// integer types

	typedef	signed char		    int8;
	typedef	signed short		int16;
	typedef signed int			int32;
	typedef signed long long	int64;
	typedef	unsigned char		uint8;
	typedef	unsigned short		uint16;
	typedef unsigned int		uint32;
	typedef unsigned long long	uint64;

	// unicode chartype

	typedef unsigned short		uchar16;

	// runtime main() declaration

	#ifdef PRCORE_IMPLEMENT_MAIN

		#include "../prcore/exception.hpp"

		// user entry point

		extern int prmain(int argc, char** argv);

		// system entry point

		int main(int argc, char** argv)
		{
			int result;
			try	{
				result = prmain(argc,argv);
			}
			catch (prcore::Exception& e) {
				e.DrawDialog();
			}
			return result;
		}

	#endif




