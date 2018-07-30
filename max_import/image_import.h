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

#ifndef __3DSMAX_IMAGE_IMPORT_H__
#define __3DSMAX_IMAGE_IMPORT_H__

namespace m2033_3dsmax
{
class image_import : public BitmapIO
{
public:
	image_import() {}
	~image_import() {}

	int				ExtCount() { return 3; }
	const TCHAR*	LongDesc() { return _T("Metro2033 texture image file"); }
	const TCHAR*	ShortDesc() { return _T("Metro2033 texture image file"); }
	const TCHAR*	AuthorName() { return _T("Ivan Shishkin"); }
	const TCHAR*	CopyrightMessage() { return _T("Copyright (C) 2010 Ivan Shishkin <codingdude@gmail.com>"); }
	unsigned int	Version() { return 100; }
	int				Capability() { return BMMIO_READER | BMMIO_EXTENSION | BMMIO_CONTROLWRITE; }
	void			ShowAbout( HWND hWnd );
	BOOL			LoadConfigure( void *ptr, DWORD ) { return TRUE; }
	BOOL			SaveConfigure( void *ptr ) { return TRUE; }
	DWORD			EvaluateConfigure() { return 0; }
	BMMRES			GetImageInfo( BitmapInfo *bi );
	void			DeleteThis() { delete this; }

	const TCHAR* Ext( int n )
	{
		switch( n )
		{
		case 0:
			return _T("512");
		case 1:
			return _T("1024");
		case 2:
			return _T("2048");
		default:
			assert(0);
			return 0;
		}
	}

	BitmapStorage*  Load( BitmapInfo *bi, Bitmap *map, BMMRES *status ); 
};
}

#endif // __3DSMAX_IMAGE_IMPORT_H__