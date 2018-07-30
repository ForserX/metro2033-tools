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
#include "model_import.h"
#include "image_import.h"
#include "level_import.h"

using namespace m2033_3dsmax;

class model_import_class_desc : public ClassDesc
{
public:
	int				IsPublic() { return TRUE; }
	void*			Create( BOOL loading ) { return new model_import; }
	const TCHAR*	ClassName() { return _T("ModelImport"); }
	SClass_ID		SuperClassID() { return SCENE_IMPORT_CLASS_ID; }
	Class_ID		ClassID() { return Class_ID(0xc9a5a4d, 0x40a2064b); }
	const TCHAR*    Category() { return _T(""); }
};

class image_import_class_desc : public ClassDesc
{
public:
	int				IsPublic() { return TRUE; }
	void*			Create( BOOL loading ) { return new image_import; }
	const TCHAR*	ClassName() { return _T("ImageImport"); }
	SClass_ID		SuperClassID() { return BMM_IO_CLASS_ID; }
	Class_ID		ClassID() { return Class_ID(0x52ae1ac0, 0x6d1845d8); }
	const TCHAR    *InternalName ( ) { return _T("4a_image"); }
	const TCHAR*    Category() { return _T(""); }
};

class level_import_class_desc : public ClassDesc
{
public:
	int				IsPublic() { return TRUE; }
	void*			Create( BOOL loading ) { return new level_import; }
	const TCHAR*	ClassName() { return _T("LevelImport"); }
	SClass_ID		SuperClassID() { return SCENE_IMPORT_CLASS_ID; }
	Class_ID		ClassID() { return Class_ID(0x50346607, 0x31fc2c42); }
	const TCHAR*    Category() { return _T(""); }
};

model_import_class_desc	model_import_description;
image_import_class_desc	image_import_description;
level_import_class_desc level_import_description;

BOOL WINAPI DllMain( HINSTANCE hinst,ULONG reason, LPVOID reserved )
{
	return TRUE;
}

__declspec( dllexport ) const TCHAR* LibDescription()
{
	return _T("Metro 2033 Import Plugin. Please visit ")
		_T("http://code.google.com/p/metro2033-tools/ for more information.");
}

__declspec( dllexport ) int LibInitialize(void)
{
	return 1;
}

__declspec( dllexport ) int LibShutdown(void)
{
	return 1;
}

__declspec( dllexport ) int LibNumberClasses()
{
	return 3;
}

__declspec( dllexport ) ClassDesc *LibClassDesc( int i ) 
{
	switch( i )
	{
	case 0:
		return (ClassDesc*) &model_import_description;
	case 1:
		return (ClassDesc*) &image_import_description;
	case 2:
		return (ClassDesc*) &level_import_description;
	}

	return 0;
}

__declspec( dllexport ) ULONG LibVersion()
{
	return VERSION_3DSMAX;
}