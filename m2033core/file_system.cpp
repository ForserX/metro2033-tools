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

#include "file_system.h"
#include "reader.h"

using namespace m2033;

static inline void fix_slashes( std::string &s )
{
	auto len = s.length();
	for(uint32_t i = 0; len != 0; i++)
	{
		len--;
		if(s[i] == '\\')
			s[i] = '/';
	}
}

std::string file_system::root_;

bool file_system::set_root_from_fname( const std::string& file )
{
	int size;
	std::string file_name;

	file_name = file;
	fix_slashes( file_name );
	size = file_name.rfind( "content" ) + 7;
	if( size == std::string::npos )
	{
		return 0;
	}
	file_name = file_name.substr( 0, size );
	file_system::set_root_dir( file_name );

	return 1;
}

std::string file_system::get_full_path( int path_id, const std::string& filename )
{
	std::string path = filename;
	fix_slashes(path);
	switch( path_id )
	{
	case ROOT:
		return root_ + std::string( "/" ) + path;
		break;
	case MESHES:
		return root_ + std::string( "/meshes/" ) + path;
		break;
	case TEXTURES:
		return root_ + std::string( "/textures/" ) + path;
		break;
	default:
		return "";
	}
}

reader_ptr file_system::open_reader( const std::string& name )
{
	FILE* file;
	uint8_t *data;
	size_t size;

	file = fopen( name.c_str(), "rb" );
	if( !file )
	{
		return reader_ptr();
	}

	fseek( file, 0, SEEK_END );
	size = ftell( file );
	fseek( file, 0, SEEK_SET );
	data = new uint8_t[size];
	fread( data, 1, size, file );
	fclose( file );

	reader *r = new reader( data, size );

	return reader_ptr( r );
}

bool file_system::file_exists( const std::string &path )
{
	FILE *f = fopen( path.c_str(), "r" );
	bool result = (f != 0);
	if( result )
		fclose(f);
	return result;
}
