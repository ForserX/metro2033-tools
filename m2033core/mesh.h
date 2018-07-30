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

#ifndef __M2033_MESH_H__
#define __M2033_MESH_H__

#include "prerequisites.h"

#include <tuple>

namespace m2033
{
	class mesh
	{
	public:
		enum
		{
			STATIC_MESH,
			DYNAMIC_MESH,
			LEVEL_GEOM
		};

		typedef std::vector<vec3> vertices;
		typedef std::vector<vec3> normals;
		typedef std::vector<vec2> texcoords;
		typedef std::vector<short> indices;
		typedef std::vector<std::tuple<char, char, char, char>> bones;
		typedef std::vector<std::tuple<float, float, float, float>> weights;

		mesh();
		~mesh();

		uint32_t load( reader_ptr r );

		void init( uint32_t type, void *vertices,
			uint32_t num_vertices, void *indices, uint32_t num_indices );
		void clear();

		void set_name( const std::string &name );
		void set_texture_name( const std::string &name );

		std::string get_name() const;
		std::string get_texture_name() const;
		vertices get_vertices() const;
		normals get_normals() const;
		texcoords get_tex_coords() const;
		indices get_indices() const;
		weights get_weights() const;
		bones get_bones() const;

	private:
		vertices	vertices_;
		normals		normals_;
		texcoords	texcoords_;
		indices		indices_;
		bones		bones_;
		weights		weights_;

		std::string	texname_;
		std::string	name_;
	};

	inline mesh::mesh() {}
	inline mesh::~mesh() {}

	inline void mesh::set_name( const std::string &name ) { name_ = name; }

	inline std::string mesh::get_name() const { return name_; }
	inline std::string mesh::get_texture_name() const { return texname_; }
	inline mesh::vertices mesh::get_vertices() const { return vertices_; }
	inline mesh::normals mesh::get_normals() const { return normals_; }
	inline mesh::texcoords mesh::get_tex_coords() const { return texcoords_; }
	inline mesh::indices mesh::get_indices() const { return indices_; }
	inline mesh::bones mesh::get_bones() const { return bones_; }
	inline mesh::weights mesh::get_weights() const { return weights_; }
}

#endif // __M2033_MESH_H__