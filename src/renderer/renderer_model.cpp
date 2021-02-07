#include <renderer_model.h>


Renderable::Renderable()
{

}

Renderable::~Renderable()
{
}


void Renderable::deleteRenderable()
{
	glDeleteBuffers(1, &this->ebo);
	glDeleteBuffers(1, &this->vbo);
	glDeleteVertexArrays(1, &this->vao);
}

bool Renderable::initializeFromScratch(GLsizei stride, std::vector<VertexData> renderable_vertex_data, std::vector<GLuint>& indices)
{
#pragma region initialize_renderable



	//Fails if this function is called before renderable_vertex_data is initialized:
	if (renderable_vertex_data.empty())
	{
		printf("create_sprite_data failed. renderable_vertex_data must cotain data and is empty\n");
		return false;
	}
	//Create Vertex_Array_Object:
	/** Now create the VAO for it */
	glCreateVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
//	this->shader = shader;
	//Create vbo:
	glCreateBuffers(1, &this->vbo);
	glNamedBufferStorage(vbo, renderable_vertex_data.size() * sizeof(VertexData), renderable_vertex_data.data(), GL_MAP_WRITE_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if (!indices.empty())
	{
		//Create a buffer of indices that we will use for our indexed drawing:
		this->indexCount = (GLuint)indices.size();
		//Create element buffer object:
		glCreateBuffers(1, &this->ebo);
		glNamedBufferStorage(ebo, indices.size() * sizeof(GLuint), indices.data(), GL_MAP_WRITE_BIT);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		
	}

	glVertexArrayVertexBuffer(this->vao, 0, this->vbo, 0, stride);
	glVertexArrayAttribBinding(this->vao, this->vertexPositionLocation, 0);
	glVertexArrayAttribFormat(this->vao,this->vertexPositionLocation,2,GL_FLOAT,GL_FALSE,offsetof(VertexData,position));
	glEnableVertexArrayAttrib(this->vao, this->vertexPositionLocation);

	glVertexArrayAttribBinding(this->vao, this->vertexTextureLocation, 0);
	glVertexArrayAttribFormat(this->vao, this->vertexTextureLocation, 2, GL_FLOAT, GL_FALSE, offsetof(VertexData, texcoord));
	glEnableVertexArrayAttrib(this->vao, this->vertexTextureLocation);
	this->numberOfVertecies = renderable_vertex_data.size();
//	glVertexAttribPointer(this->vertex_color_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_Data), reinterpret_cast<void*>(offsetof(Vertex_Data, color)));
//	glVertexAttribPointer(this->vertex_texture_location, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offsetof(Vertex_Data, texture_cordinates)));c
#pragma endregion
}


bool Renderable::initializeWithObj(const std::string& file_name)
{
	//If failed to load object:
	//if (!this->load_object(file_name)) {
	//	std::cout << "initialize_with_obj(..) Failed to load object.\n";
	//	return false;
	//}
	if (!this->load(file_name)) {
		std::cout << "initialize_with_obj(..) Failed to load object.\n";
		return false;
	}

	//Fails if this function is called before renderable_vertex_data is initialized:
	if (this->vertices.empty())
	{
		printf("create_sprite_data failed. renderable_vertex_data must cotain data and is empty\n");
		return false;
	}
	//Create Vertex_Array_Object:
	/** Now create the VAO for it */
	glCreateVertexArrays(1, &this->vao);
	//glBindVertexArray(this->vao);
	//	this->shader = shader;
		//Create vbo:
	glCreateBuffers(1, &this->vbo);
	glNamedBufferStorage(vbo, this->vertices.size() * sizeof(VertexData), this->vertices.data(), GL_MAP_WRITE_BIT);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if (!this->indices.empty())
	{
		//Create a buffer of indices that we will use for our indexed drawing:
		this->indexCount = (GLuint)this->indices.size();
		//Create element buffer object:
		glCreateBuffers(1, &this->ebo);
		glNamedBufferStorage(ebo, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_MAP_WRITE_BIT);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

	}
	//Attributes:
	glVertexArrayVertexBuffer(this->vao, 0, this->vbo, 0, sizeof(VertexData));
	glVertexArrayAttribBinding(this->vao, this->vertexPositionLocation, 0);
	glVertexArrayAttribFormat(this->vao, this->vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, position));
	glEnableVertexArrayAttrib(this->vao, this->vertexPositionLocation);

	//glVertexArrayVertexBuffer(this->vao, 0, this->vbo, 0, sizeof(Vertex_Data));
	glVertexArrayAttribBinding(this->vao, this->vertexColorLocation, 0);
	glVertexArrayAttribFormat(this->vao, this->vertexColorLocation, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, color));
	glEnableVertexArrayAttrib(this->vao, this->vertexColorLocation);


	glVertexArrayAttribBinding(this->vao, this->vertexTextureLocation, 0);
	glVertexArrayAttribFormat(this->vao, this->vertexTextureLocation, 2, GL_FLOAT, GL_FALSE, offsetof(VertexData, texcoord));
	glEnableVertexArrayAttrib(this->vao, this->vertexTextureLocation);

	//normal attributes:
	glVertexArrayAttribBinding(this->vao, this->vertexNormalLocation, 0);
	glVertexArrayAttribFormat(this->vao, this->vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, normal));
	glEnableVertexArrayAttrib(this->vao, this->vertexNormalLocation);
	//VIKITG:
	glVertexArrayElementBuffer(this->vao, this->ebo);
	this->numberOfVertecies = this->vertices.size();
	return true;
}


void Renderable::drawElements(GLenum mode)
{

	glBindVertexArray(this->vao);

	if (this->ebo > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		glDrawElements(mode, this->indexCount, GL_UNSIGNED_INT, nullptr);
	}
	else {
		glDrawArrays(mode, 0, this->numberOfVertecies);
	}
	//

	//unbinds the VAO:
	glBindVertexArray(0);


//	GLCall(glDrawElements(GL_TRIANGLES, this->index_count, GL_UNSIGNED_INT, nullptr));
}
void Renderable::addToScene(GLenum mode,GLuint amount_of_vertecies) 
{

}


//WARNING a lot of bad if and else incoming:
//Stolen from https://github.com/Headturna/OpenGL-C---Tutorials/blob/master/OBJLoader.h:
bool Renderable::loadObject(const char* file_name)
{
	//Vertex portions
	std::vector<glm::fvec3> vertex_positions;
	std::vector<glm::fvec2> vertex_texcoords;
	std::vector<glm::fvec3> vertex_normals;

	//Face vectors
	std::vector<GLint> vertexPositionIndicies;
	std::vector<GLint> vertexTexcoordIndicies;
	std::vector<GLint> vertexNormalIndicies;


	std::stringstream string_stream;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;
	int x = 0;

	//each face (each triangle) contains 3 points. To define the 
	//position and color of each point we would need a list of indices to tell OpenGL what
	//to draw. this isn't possible when we need the UV/texture coordinates and normal vector
	//of the face. With these 2 we need 2 more indices and therefore we need more vertices 
	//for each point. f 5/1/1 3/2/1 1/3/1 could describe a triangle 
	// where the structure is as following: position_index/texture_index/normal_vector_index
	//
	//You can't draw with several indices representing a point, BUT!
	//This doesn't mean that indices become obsolete. the same combination of indices can
	//occur. In a cube I think the following 5/1/1 occur twice, and if each point occurs 
	//twice you could save half of the memory (minus the amount for indices) on that cube.


	//valid_vertex_indices is used for creating vertices with respect to the following indices
	//each Vertex_Indices contain. This will contain unique Vertex_Indices and eventually create
	//the actual indices and vertices:
	std::vector<VertexIndices> valid_vertex_indices{};
	VertexIndices temporary_vertex_indices;
	//actual indices:
	std::vector<GLuint> actual_vertex_indices{};
	//Vertex array
	std::vector<VertexData> vertices;

	//File open error check
	if (!in_file.is_open())
	{
//		throw "ERROR::OBJLOADER::Could not open file.";
		std::cout << "couldn't load file: " << file_name << std::endl;
		return false;
	}

	//Read one line at a time
	while (std::getline(in_file, line))
	{
		//Get the prefix of the line
		string_stream.clear();
		string_stream.str(line);
		string_stream >> prefix;
		//doing nothing:
		if (prefix == "#");
		else if (prefix == "mtllib");
		else if (prefix == "o");
		else if (prefix == "s");
		else if (prefix == "usemtl");
		//vertex position:
		else if (prefix == "v") //Vertex position
		{
			string_stream >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		//texture coordinates:
		else if (prefix == "vt")
		{
			string_stream >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);
		}
		//normal vectors:
		else if (prefix == "vn")
		{
			string_stream >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		//Indices:
		else if (prefix == "f")
		{
			int counter = 0;
			while (string_stream >> temp_glint)
			{
				//Pushing indices into correct arrays
				if (counter == 0)
					temporary_vertex_indices.vertexPositionIndicies = temp_glint;
				//	vertex_position_indicies.push_back(temp_glint);
				else if (counter == 1)
					temporary_vertex_indices.vertexTexcoordIndicies = temp_glint;

				//	vertex_texcoord_indicies.push_back(temp_glint);
				else if (counter == 2)
					{
					//Checking to see if we can find this new vertex_index in the list of valid ones:
					//auto index_iterator = std::find(valid_vertex_indices.begin(), valid_vertex_indices.end(), temporary_vertex_indices);
						temporary_vertex_indices.vertexNormalIndicies = temp_glint;
							bool vertex_indices_is_unique = true;
					int indices_index{};
					//Debugging:
					std::cout << temporary_vertex_indices.vertexPositionIndicies 
						<< "/"<< temporary_vertex_indices.vertexTexcoordIndicies 
						<<"/" << temporary_vertex_indices.vertexNormalIndicies << std::endl;
					while (indices_index < valid_vertex_indices.size() && vertex_indices_is_unique)
					{
						//if it's alike:
						if (temporary_vertex_indices.isEqual(valid_vertex_indices[indices_index]))
						{
							vertex_indices_is_unique = false;
						}
						else
						{
							//Iterate to the next vertex:
							indices_index++;
						}
					}
					//checking if the new newly read vertex is unique:
					if (vertex_indices_is_unique)
					{
						//including it to valid, unique vertices:
						valid_vertex_indices.push_back(temporary_vertex_indices);
						//pushing back the new index for the actual vertex:
						actual_vertex_indices.push_back(valid_vertex_indices.size()-1);
						std::cout << ++x << "unique!" << actual_vertex_indices[indices_index] << std::endl;

					}
					else
					{
						//Finding where the unique index is positioned:
						//GLint index = std::distance(valid_vertex_indices.begin(), index_iterator) + 1;
						//pushing back the new index for the actual vertex:
						actual_vertex_indices.push_back(indices_index);
						std::cout << ++x << "seen it before..." << actual_vertex_indices[indices_index] << std::endl;

					}
					temporary_vertex_indices.vertexNormalIndicies = temp_glint;
					}
				//	vertex_normal_indicies.push_back(temp_glint);

				//Handling characters
				if (string_stream.peek() == '/')
				{
					++counter;
					string_stream.ignore(1, '/');
				}
				else if (string_stream.peek() == ' ')
				{
					++counter;
					string_stream.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
				{
					counter = 0;
					/*
					//Going through valid vertices to see if the vertex already exsists.
					bool vertex_indices_is_unique = true;
					int indices_index{};
					while (indices_index < valid_vertex_indices.size() && vertex_indices_is_unique)
					{
						//if it's alike:
						if (temporary_vertex_indices.is_equal(valid_vertex_indices[indices_index]))
						{
							vertex_indices_is_unique = false;
						}
						else
						{
							//Iterate to the next vertex:
							indices_index++;
						}
					}
					//checking if the new newly read vertex is unique:
					if (vertex_indices_is_unique)
					{
						//including it to valid, unique vertices:
						valid_vertex_indices.push_back(temporary_vertex_indices);
						//pushing back the new index for the actual vertex:
						actual_vertex_indices.push_back(valid_vertex_indices.size());
					}
					else
					{
						//Finding where the unique index is positioned:
						//GLint index = std::distance(valid_vertex_indices.begin(), index_iterator) + 1;
						//pushing back the new index for the actual vertex:
						actual_vertex_indices.push_back(indices_index);
					}
					*/
				}
			}
		}
		else;





	}
		//DEBUG
		std::cout << "Nr of indices: " << actual_vertex_indices.size() << "\n";
		std::cout << "Nr of valid vertices indices: " << valid_vertex_indices.size() << "\n";
		std::cout << "Nr of vertices: " << vertices.size() << "\n";













	//Build final vertex array (mesh)
	vertices.resize(valid_vertex_indices.size(), VertexData());
	//		vertices.resize(vertex_position_indicies.size(), Vertex_Data());


	//Putting together all the indices to one vertex vector:
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		//vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
		//vertices[i].texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
		//vertices[i].normal = vertex_normals[vertex_norm


		//Notice: the -1 is because the indices start at 1, but the vertex vector starts at 0:
		vertices[i].position = vertex_positions[valid_vertex_indices[i].vertexPositionIndicies - 1];
		vertices[i].texcoord = vertex_texcoords[valid_vertex_indices[i].vertexTexcoordIndicies - 1];
		vertices[i].normal = vertex_normals[valid_vertex_indices[i].vertexNormalIndicies - 1];
		vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
	}

	this->vertices = vertices;
	this->indices = actual_vertex_indices;
	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";
	return true;
}

bool Renderable::load(const std::string& filepath_obj)
{
	/**
	 * Task 1: Load the model by creating a vbo, ebo and vao and then use your own model loader or tiny_obj_loader
	 *
	 *  - The vertices should be stored in the vbo
	 *  - The indices should be stored in the ebo
	 *  - The vao should hold the layout
	 *  - The texture should be a handle to the texture of the model
	 */

//	m_texture.load_texture(diffuse_path);

	/** Load OBJ Data */
	tinyobj::attrib_t attributes{};
	std::vector<tinyobj::shape_t> shapes{};
	std::vector<tinyobj::material_t> materials{};
	std::string warning{}, error{};

	if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, filepath_obj.c_str()))
	{
		GFX_ERROR("Could not load model: W(%s) E(%s)", warning.c_str(), error.c_str());
		return false;
	}

	/** Success loading, so we can extract data here */
	std::vector<VertexData> out_vertices{};
	std::vector<unsigned> out_indices{};
	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			/** Uses non-deal index loading, this does not remove duplicate vertices, it's naive, but works for demo purposes */
//				out_vertices.push_back({});
//				out_indices.push_back(out_indices.size());

			VertexData temp_vertex; //out_vertices.back();
			temp_vertex.position = { attributes.vertices[3 * index.vertex_index + 0],
							   attributes.vertices[3 * index.vertex_index + 1],
							   attributes.vertices[3 * index.vertex_index + 2] };

			temp_vertex.normal = { attributes.normals[3 * index.normal_index + 0],
							  attributes.normals[3 * index.normal_index + 1],
							  attributes.normals[3 * index.normal_index + 2] };

			temp_vertex.texcoord = { attributes.texcoords[2 * index.texcoord_index + 0],
							   attributes.texcoords[2 * index.texcoord_index + 1] };
			//Checking if the
			auto actual_index = getVertexVectorPosition(&temp_vertex);

			if (actual_index < this->vertices.size())
			{

				this->indices.push_back(actual_index);
			}
			else
			{
				//Pushing back the vertex:
				this->vertices.push_back(temp_vertex);
				this->indices.push_back(actual_index);
			}
		}
	}

	/** Set index count */
	//m_index_count = out_indices.size();
	indexCount = this->indices.size();
	//this->vertices = out_vertices;
	//this->indices = out_indices;
	/** Create VAO / VBO / EBO */
	/*
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * out_vertices.size(), out_vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * out_indices.size(), out_indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(this->va_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(this->va_normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	glVertexAttribPointer(this->va_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));

	glEnableVertexAttribArray(va_position);
	glEnableVertexAttribArray(va_normal);
	glEnableVertexAttribArray(va_texcoord);
	*/
	//VAO:
	glCreateVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	//VBO:
	glCreateBuffers(1, &this->vbo);
	glNamedBufferStorage(this->vbo, this->vertices.size() * sizeof(VertexData), this->vertices.data(), GL_MAP_WRITE_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	//Create element buffer object:
	glCreateBuffers(1, &this->ebo);
	glNamedBufferStorage(this->ebo, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_MAP_WRITE_BIT);

	//Attributes:
	glVertexArrayVertexBuffer(this->vao, 0, this->vbo, 0, sizeof(VertexData));
	glVertexArrayAttribBinding(this->vao, this->vertexPositionLocation, 0);
	glVertexArrayAttribFormat(this->vao, this->vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, position));
	glEnableVertexArrayAttrib(this->vao, this->vertexPositionLocation);

	//glVertexArrayVertexBuffer(this->vao, 0, this->vbo, 0, sizeof(Vertex_Data));
	//glVertexArrayAttribBinding(this->vao, this->vertex_color_location, 0);
	//glVertexArrayAttribFormat(this->vao, this->vertex_color_location, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));
	//glEnableVertexArrayAttrib(this->vao, this->vertex_color_location);


	glVertexArrayAttribBinding(this->vao, this->vertexTextureLocation, 0);
	glVertexArrayAttribFormat(this->vao, this->vertexTextureLocation, 2, GL_FLOAT, GL_FALSE, offsetof(VertexData, texcoord));
	glEnableVertexArrayAttrib(this->vao, this->vertexTextureLocation);

	//normal attributes:
	glVertexArrayAttribBinding(this->vao, this->vertexNormalLocation, 0);
	glVertexArrayAttribFormat(this->vao, this->vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, offsetof(VertexData, normal));
	glEnableVertexArrayAttrib(this->vao, this->vertexNormalLocation);


	glVertexArrayElementBuffer(this->vao, this->ebo);

	GFX_INFO("Loaded model %s (%u vertices).", filepath_obj.c_str(), this->vertices.size());
	GFX_INFO("             %s (%u indices).", filepath_obj.c_str(), this->indexCount);
	return true;
}

int Renderable::getVertexVectorPosition(VertexData* temp_vertex)
{
	int i{};
	for (; i < this->vertices.size(); i++)
	{
		if (checkIfEqual(&vertices[i], temp_vertex)) return i;
	}
	return i;
}

bool Renderable::checkIfEqual(VertexData* temp_vertex1, VertexData* temp_vertex2)
{
	//check if equal:
	if (
		(temp_vertex1->position == temp_vertex2->position) &&
		(temp_vertex1->texcoord == temp_vertex2->texcoord) &&
		(temp_vertex1->normal == temp_vertex2->normal))
		return true;

	//Isn't equal:
	return false;
}
