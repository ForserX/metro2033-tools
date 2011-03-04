/******************************************************************************
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
                    Version 2, December 2004 

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net> 

 Everyone is permitted to copy and distribute verbatim or modified 
 copies of this license document, and changing it is allowed as long 
 as the name is changed. 

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 

  0. You just DO WHAT THE FUCK YOU WANT TO.
******************************************************************************/

#ifndef __M2033_MESH_H__
#define __M2033_MESH_H__

#include "prerequisites.h"

namespace m2033
{
	class mesh
	{
	public:
		enum
		{
			STATIC_MESH,
			DYNAMIC_MESH
		};

		typedef std::vector<vec3> vertices;
		typedef std::vector<vec3> normals;
		typedef std::vector<vec2> texcoords;
		typedef std::vector<short> indices;

		inline mesh();
		inline ~mesh();

		void init( int type, void *vertices, unsigned num_vertices, void *indices,
			unsigned num_indices, const std::string &name, const std::string &texture_name );
		void clear();

		inline std::string get_name() const;
		inline std::string get_texture_name() const;
		inline vertices get_vertices() const;
		inline normals get_normals() const;
		inline texcoords get_tex_coords() const;
		inline indices get_indices() const;

	private:
		vertices	vertices_;
		normals		normals_;
		texcoords	texcoords_;
		indices		indices_;

		std::string	texname_;
		std::string	name_;
	};

	inline mesh::mesh() {}
	inline mesh::~mesh() {}

	inline std::string mesh::get_name() const { return name_; }
	inline std::string mesh::get_texture_name() const { return texname_; }
	inline mesh::vertices mesh::get_vertices() const { return vertices_; }
	inline mesh::normals mesh::get_normals() const { return normals_; }
	inline mesh::texcoords mesh::get_tex_coords() const { return texcoords_; }
	inline mesh::indices mesh::get_indices() const { return indices_; }
}

#endif // __M2033_MESH_H__