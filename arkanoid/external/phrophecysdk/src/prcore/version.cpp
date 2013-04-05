/*
	Twilight Prophecy SDK
	A multi-platform development system for virtual reality and multimedia.

	Copyright (C) 1997-2003 Twilight 3D Finland Oy Ltd.


    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.


	source:
		version information

	revision history:
		Feb/24/2001 - Jukka Liimatta - initial revision
*/
#include <prcore/version.hpp>

namespace prcore {    

    int prcore::GetLibraryBuild()
    {
        return 350;
    }

    float prcore::GetLibraryVersion()
    {
        return 1.212f;
    }

    const char* prcore::GetLibraryDate()
    {
        return __DATE__;
    }

    const char* prcore::GetLibraryTime()
    {
        return __TIME__;
    }

} // prcore
