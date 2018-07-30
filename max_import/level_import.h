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

#ifndef __3DSMAX_LEVEL_IMPORT_H__
#define __3DSMAX_LEVEL_IMPORT_H__

namespace m2033_3dsmax
{
	class level_import : public SceneImport
	{
	public:
		int				ExtCount() { return 1; }
		const TCHAR* Ext( int i ) { return _T("geom_pc"); }
		const TCHAR*	LongDesc() { return _T("Metro2033 Level Importer"); }
		const TCHAR*	ShortDesc() { return _T("Metro2033 Level Importer"); }
		const TCHAR*	AuthorName() { return _T("Ivan Shishkin"); }
		const TCHAR*	CopyrightMessage() { return _T("Copyright (C) 2010 Ivan Shishkin <codingdude@gmail.com>"); }
		const TCHAR*	OtherMessage1() { return _T(""); }
		const TCHAR*	OtherMessage2() { return _T(""); }
		unsigned int	Version() { return 100; }
		int				ZoomExtents() { return ZOOMEXT_NOT_IMPLEMENTED; }
		void			DeleteThis() { delete this; }

		void ShowAbout( HWND hwnd );

		int DoImport( const TCHAR *name, ImpInterface *ii, Interface *i, BOOL suppressPrompts );
	};
}

#endif // __3DSMAX_LEVEL_IMPORT_H__