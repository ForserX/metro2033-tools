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

#include "mesh.h"
#include "reader.h"
#include "math.h"
#include "file_system.h"

using namespace m2033;

struct static_model_vertex
{
    float x, y, z, w;
    unsigned normal;
	unsigned tangent;
    float u, v;
};

struct dynamic_model_vertex
{
    short x, y, z;
    short unknown;
    unsigned normal;
    unsigned tangent;
    unsigned binormal;
    char  bones[4];
    unsigned char weights[4];
    short u, v;
};

struct level_geom_vertex
{
    float x, y, z;
    unsigned normal;
	unsigned tangent;
	unsigned binormal;
    short u, v;
	unsigned unused; // ?
};

void mesh::init( uint32_t type, void *vertices, uint32_t num_vertices, void *indices, uint32_t num_indices )
{
	assert( vertices );
	assert( indices );
	assert( num_vertices );
	assert( num_indices );
	if( vertices == 0 || indices == 0 || num_vertices == 0 || num_indices == 0 )
	{
		return;
	}

	clear();

	if( type == mesh::STATIC_MESH ) {
		static_model_vertex *v = (static_model_vertex*) vertices;

		for( uint32_t i = 0; i < num_vertices; i++ ) {
			vec3 vert = vec3( v[i].x, v[i].y, v[i].z );
			vertices_.push_back( vert );

			vec3 norm = vec3( ((v[i].normal << 16) & 0xFF) / 255.0f,
				((v[i].normal << 8) & 0xFF) / 255.0f,
				(v[i].normal & 0xFF) / 255.0f );
			norm.normalize();
			normals_.push_back( norm );

			vec2 tc = vec2( v[i].u, v[i].v );
			texcoords_.push_back( tc );
		}
	}
	else if( type == mesh::DYNAMIC_MESH ) {
		dynamic_model_vertex *v = (dynamic_model_vertex*) vertices;

		for( uint32_t i = 0; i < num_vertices; i++ ) {
			vec3 vert = vec3( v[i].x  / 2720.0f, v[i].y / 2720.0f, v[i].z / 2720.0f );
			vertices_.push_back( vert );

			vec3 norm = vec3( ((v[i].normal << 16) & 0xFF) / 255.0f,
				((v[i].normal << 8) & 0xFF) / 255.0f,
				(v[i].normal & 0xFF) / 255.0f );

			normals_.push_back( norm );

			vec2 tc = vec2( v[i].u / 2048.0f, v[i].v / 2048.0f );
			texcoords_.push_back( tc );

			bones_.emplace_back( v[i].bones[0], v[i].bones[1], v[i].bones[2], v[i].bones[3] );
			weights_.emplace_back( v[i].weights[0] / 255.0f, v[i].weights[1] / 255.0f, v[i].weights[2] / 255.0f, v[i].weights[3] / 255.0f );
		}
	}
	else if( type == mesh::LEVEL_GEOM ) {
		level_geom_vertex *v = (level_geom_vertex*) vertices;

		for( uint32_t i = 0; i < num_vertices; i++ ) {
			vec3 vert = vec3( v[i].x, v[i].y, v[i].z );
			vertices_.push_back( vert );

			vec3 norm = vec3( ((v[i].normal << 16) & 0xFF) / 255.0f,
				((v[i].normal << 8) & 0xFF) / 255.0f,
				(v[i].normal & 0xFF) / 255.0f );

			normals_.push_back( norm );

			vec2 tc = vec2( v[i].u / 1024.0f, v[i].v / 1024.0f );
			texcoords_.push_back( tc );
		}
	}

	uint16_t *idx = (uint16_t*) indices;

	for( uint32_t i = 0; i < num_indices; i++ )
		indices_.push_back( idx[i] );
}

void mesh::clear()
{
	vertices_.clear();
	normals_.clear();
	texcoords_.clear();
	indices_.clear();
	texname_.clear();
	bones_.clear();
	weights_.clear();
	name_.clear();
}

uint32_t mesh::load( reader_ptr r )
{
	void *vb, *ib;
	uint32_t size, vnum, inum1, inum2, i = 0;
	uint8_t n;
	uint32_t type;

	// read vertices
	if( r->open_chunk( DYNAMIC_VERTEX_CHUNK_ID ) != 0 ) {

		// skip unused data
		n = r->r_u8();
		size = n * 61;
		r->advance( size );

		// calculate vertices size
		vnum = r->r_u32();
		size = vnum * 32;

		type = DYNAMIC_MESH;
	}
	else if( r->open_chunk( STATIC_VERTEX_CHUNK_ID ) != 0 ) {
		size = r->size() - 8;
		r->advance( 4 );
		vnum = r->r_u32();

		type = STATIC_MESH;
	}
	else {
		assert(0);
		return -1;
	}

	vb = malloc( size );
	r->r_data( vb, size );
	r->close_chunk();

	// read indices
	r->open_chunk();
	size = r->size() - 4;
	inum1 = r->r_u16();
	inum2 = r->r_u16();
	ib = malloc( size );
	r->r_data( ib, size );
	r->close_chunk();

	inum1 = inum2 ? inum1 *3 : size / 2;
	init( type, vb, vnum, ib, inum1 );

	free( vb);
	free( ib );

	return type;
}

void mesh::set_texture_name( const std::string &name )
{
	file_system fs;
	std::string dds_texture = name + std::string(".dds");
	std::string native_texture = name  + std::string(".512");
	if( fs.file_exists(dds_texture) )
		texname_ = dds_texture;
	else
		texname_ = native_texture;
}