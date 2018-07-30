#include "model.h"
#include "file_system.h"
#include "reader.h"
#include "mesh.h"
#include "skeleton.h"

#include <windows.h>

using namespace m2033;

bool model::load( const std::string & path )
{
	file_system fs;
	size_t size;
	std::string name;
	char buffer[1024];
	string_list names;
	string_list::iterator it;

	meshes_.clear();

	reader_ptr r = fs.open_reader( path );
	if( r.is_null() )
		return 0;

	bool repeat = false;
	int i = 0, j = 0;

	do {
		if( r->open_chunk( MODEL_CHUNK_ID ) != 0 ) {
			meshes_.clear();
			uint32_t type = load_meshes( r );
			if( type == mesh::STATIC_MESH )
				set_type( STATIC );
			else if( type == mesh::DYNAMIC_MESH )
				set_type( DYNAMIC );
			r->close_chunk();
			r->close_chunk();
		}
		else if( r->open_chunk( SKELETON_NAME_CHUNK_ID ) != 0 ) {
			// read skeleton
			size = r->size();
			r->r_data( buffer, size );
			/*name = fs.get_full_path( file_system::MESHES, std::string( buffer ) + std::string( ".skeleton" ) );
			reader_ptr sr = fs.open_reader( name );
			if( sr.is_null() )
				return 0;
			skeleton s;
			s.load( sr );
			set_skeleton( s );*/
			r->close_chunk();

			if( r->open_chunk( MESH_NAMES_CHUNK_ID ) == 0 )
				return 0;

			size = r->size() - 4;
			assert( size < 1024 );
			r->advance( 4 );
			r->r_data( buffer, size );
			split_string( buffer, ',', names );

			meshes_.clear();
			for( it = names.begin(); it != names.end(); it++ ) {
				name = (*it);
				name = fs.get_full_path( file_system::MESHES, name + std::string( ".mesh" ) );
				reader_ptr mr = fs.open_reader( name );

				if (!mr.is_null())
				{
					if (mr->size() == 0)
						return 0;

					if (mr->open_chunk(MODEL_CHUNK_ID) == 0)
						return 0;

					load_meshes(mr);
				}
				else
				{
					MessageBoxA(nullptr, name.c_str(), "Couldn't find file", MB_OK);
				}
			}

			r->close_chunk();
			r->close_chunk();;

			set_type( DYNAMIC );
		}

		if (repeat) {
			r->close_chunk();
			r->close_chunk();
		}

		repeat = false;
		if (r->open_chunk(0x0f)) {
			if (r->open_chunk(i)) {
				if (!r->open_chunk(j++))
					i++;
				repeat = true;
			}
		}
 
	} while (repeat);

	return 1;
}

void model::split_string( const std::string& string, char splitter, string_list& result )
{
	size_t len = 0, size;
	std::string temp, val;

	temp = string;

	while( len != std::string::npos )
	{
		len = temp.find_first_of( splitter );
		if( len != std::string::npos )
		{
			size = temp.size();
			val = temp.substr( 0, len );
			temp = temp.substr( len+1, size-len-1 );
		}
		else
		{
			val = temp;
		}

		result.push_back( val );
	}
}

uint32_t model::load_meshes( reader_ptr r )
{
	mesh m;
	char texname[255];
	std::string name, tname;
	uint32_t type, size, i = 0;
	file_system fs;

	do
	{
		r->open_chunk();

		// get texture string
		r->open_chunk( TEXTURE_NAME_CHUNK_ID );
		size = r->size();
		assert( size < 255 );
		r->r_data( texname, size );
		r->close_chunk();

		tname = fs.get_full_path( file_system::TEXTURES, std::string( texname ) );
		name = texname;
		size = name.find_last_of( "\\" );
		if( size != 0 )
			name = name.substr( ++size, name.length() - size );

		type = m.load( r );
		m.set_name( name );
		m.set_texture_name( tname );
		meshes_.push_back( mesh_ptr( new mesh( m ) ) );
		m.clear();

		r->close_chunk();

		i++;
	}
	while( r->elapsed() > 64 );

	return type;
}

void model::add_mesh( mesh &m )
{
	meshes_.push_back( mesh_ptr( new mesh( m ) ) );
}

void model::set_skeleton( const skeleton &s )
{
	skeleton_ = skeleton_ptr( new skeleton( s ) );
}