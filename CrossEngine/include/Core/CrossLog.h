/****************************************************************************
Copyright (c) 2017 LiangYue.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sub license, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#pragma once
#include "CrossEngine.h"


namespace CrossEngine {

	CROSS_EXPORT void EnableLog(BOOL bEnable, const char *szFileName);

	CROSS_EXPORT void WriteLogI(const char *szFileName, int nLineNumber, const char *szFormat, ...);
	CROSS_EXPORT void WriteLogW(const char *szFileName, int nLineNumber, const char *szFormat, ...);
	CROSS_EXPORT void WriteLogE(const char *szFileName, int nLineNumber, const char *szFormat, ...);

}

#define LOGI(...) CrossEngine::WriteLogI(__FILE__, __LINE__, __VA_ARGS__);
#define LOGW(...) CrossEngine::WriteLogW(__FILE__, __LINE__, __VA_ARGS__);
#define LOGE(...) CrossEngine::WriteLogE(__FILE__, __LINE__, __VA_ARGS__);
