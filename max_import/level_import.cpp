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

#include "precompiled.h"
#include "level_import.h"
#include "model_import.h"

using namespace m2033_3dsmax;

int level_import::DoImport( const TCHAR *name, ImpInterface *ii, Interface *i, BOOL suppressPrompts )
{
	m2033::file_system fs;
	fs.set_root_from_fname( ToNarrow(name) );

	m2033::level lvl;
	bool res = lvl.load( ToNarrow(name) );
	if( !res )
		return IMPEXP_FAIL;

	m2033::model model = lvl.get_geometry();
	model_import model_imp;
	return model_imp.import( model );
}

void level_import::ShowAbout( HWND hwnd )
{
	MessageBox( hwnd,
				_T("Metro 2033 Level import plugin.\n")
				_T("Please visit http://code.google.com/p/metro2033-tools/ for more information.\n")
				_T("Copyright (C) 2010 Ivan Shishkin <codingdude@gmail.com>\n"),
				_T("About"),
				MB_ICONINFORMATION );
}