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

#ifndef __3DSMAX_MODEL_IMPORT_H__
#define __3DSMAX_MODEL_IMPORT_H__

#include <set>

namespace m2033_3dsmax
{
class model_import : public SceneImport
{
public:
	int				ExtCount() { return 3; }
	const TCHAR* Ext( int i ) { return i ? _T("mesh") : _T("model"); }
	const TCHAR*	LongDesc() { return _T("Metro2033 Model Importer"); }
	const TCHAR*	ShortDesc() { return _T("Metro2033 Model Importer"); }
	const TCHAR*	AuthorName() { return _T("Ivan Shishkin"); }
	const TCHAR*	CopyrightMessage() { return _T("Copyright (C) 2010 Ivan Shishkin <codingdude@gmail.com>"); }
	const TCHAR*	OtherMessage1() { return _T(""); }
	const TCHAR*	OtherMessage2() { return _T(""); }
	unsigned int	Version() { return 100; }
	int				ZoomExtents() { return ZOOMEXT_NOT_IMPLEMENTED; }
	void			DeleteThis() { delete this; }

	void ShowAbout( HWND hwnd );

	int DoImport( const TCHAR *name, ImpInterface *ii, Interface *i, BOOL suppressPrompts );
	int import( m2033::model &m );

private:
	typedef std::map<std::string, Mtl*> mtl_map;
	typedef std::map<std::string, INode*> bone_map;
	typedef std::map<int, INode*> bone_idx_map;

private:
	Modifier* create_skin_modifier( INode* node );
	void create_material( INode *node, const std::string& texture );
	void set_mesh( Mesh &m1, m2033::mesh_ptr m2 );
	void build_skeleton( m2033::skeleton_ptr s );
	void update_bone_length( const m2033::skeleton::bone& b );
	void build_bone_obj( INode* bone_node, float length, float side );
	INode* get_bone_node( const std::string& name );

private:
	Interface		*interface_;
	ImpInterface	*imp_interface_;

	mtl_map			materials_;
	bone_map		bones_;
	bone_idx_map	bones_idx_;

	std::set<int>   bone_ints_;
};
}

#endif // __3DSMAX_MODEL_IMPORT_H__