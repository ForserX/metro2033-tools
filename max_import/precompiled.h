/******************************************************************************
This source file is part of metro2033-tools
For the latest info, see http://code.google.com/p/metro2033-tools/

Copyright (c) 2010-2011 Ivan Shishkin <codingdude@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
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
******************************************************************************/

#ifndef __3DSMAX_PRECOMPILED_H__
#define __3DSMAX_PRECOMPILED_H__

#pragma warning( disable : 4996 )

#include "max.h"
#include "iparamb2.h"
#include "modstack.h"
#include "iskin.h"
#include "stdmat.h"
#include "bmmlib.h"
#include "bitmap.h"
#include "simpobj.h"

#include <m2033core/model.h>
#include <m2033core/mesh.h>
#include <m2033core/skeleton.h>
#include <m2033core/level.h>
#include <m2033core/reader.h>
#include <m2033core/file_system.h>

#include <string>
#include <list>
#include <map>
#include <deque>
#include <vector>

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <codecvt>

inline std::string ToNarrow(const std::wstring& wide)
{
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> g_converter;
	return g_converter.to_bytes(wide);
}

inline std::wstring ToWide(const std::string& narrow)
{
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> g_converter;
	return g_converter.from_bytes(narrow);
}


#endif // __3DSMAX_PRECOMPILED_H__