#include <renderer_texture.h>



Texture::Texture() : ResourceManager()
{
}

Texture::~Texture()
{

}



//Bind this texture:
void Texture::bindTexture()
{

	glBindTextureUnit(this->textureSamplerLocation, this->textureID);
	glUniform1i(this->textureSamplerLayerLocation, this->currentFrame);
	glBindTexture(this->savedTarget, this->textureID);
}

void Texture::deleteTexture()
{
	glDeleteTextures(1, &this->textureID);
}


/**
 * Load the texture at the given relative filepath and put it into OpenGL for use in rendering
 *
 * @warning This function is NOT implemented by tutors
 *
 * @param filepath The relative filepath to the texture
 * @return An OpenGL handle to a 2D Texture
 * wrapping_param could be GL_REPEAT:
 * mipmap_param could be GL_NEAREST_MIPMAP_NEAREST:
 */
GLuint Texture::loadOpenglTexture(const std::string& imagefilepath/*, Shader* shader_reference*/, GLenum wrapping_param = GL_REPEAT, GLenum minification_filter = GL_NEAREST, GLenum magnification_filter = GL_NEAREST)
{
	int nrChannels{};
	//Setting flipped image to true so that the image that is loaded won't be upside down:
	stbi_set_flip_vertically_on_load(true);
	//Loading image to 1Byte array:
	unsigned char* image = stbi_load(imagefilepath.c_str(), &textureHeight, &textureWidth, &nrChannels, STBI_rgb_alpha);
	if (!image)
	{
		printf("failed to load image, \"%s\"\n", imagefilepath.c_str());
		return 0;
	}

	//If it is already assigned a  texture:
	if (this->textureID != 0)
	{
		std::cout << "This object has already been assigned a texture (texID: " << this->textureID << ").\n";
		return 0;
	}



	//getting the shaderprogramID:
//	this->usedShaderProgram = shader_reference->getShaderProgram();



	//Creating texture:
	glCreateTextures(GL_TEXTURE_2D, 1, &this->textureID);
	//getting the sampler location:
	this->textureSamplerLocation = TEXTURE_UNIT_SAMPLER_LOCATION;//glGetUniformLocation(this->used_shader_program, "image_sampler");
	glBindTextureUnit(this->textureSamplerLocation, this->textureID);
	//getting the sampler location for texture array layer (z-axis)
	//NOTE! this will always be 0 if the texture isn't an array:
	this->textureSamplerLayerLocation = TEXTURE_ARRAY_LAYER_LOCATION;
	
	std::cout << "texture unit is: " << this->textureSamplerLocation << std::endl << "and texture layer id is:" << this->textureSamplerLayerLocation << std::endl;
	GLint id;
	glGetIntegerv(GL_ACTIVE_TEXTURE, &id);
	std::cout << "current active texture is: " << id << " - while this->texture_sampler_location is:" << this->textureSamplerLocation;




	glTextureStorage2D(this->textureID, 4, GL_RGBA8, this->textureWidth, this->textureHeight);
	//Creating a sampler to assign to texture:
	GLuint sampler{};
	glCreateSamplers(1, &sampler);
	//Binding sampler:
	glBindSampler(this->textureSamplerLocation, sampler);

	//set the texture wrapping parametersawdas
	// set texture wrapping to GL_REPEAT (default wrapping method)
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrapping_param);
	//glBindSampler(this->sampler_binding_location, samplers[1]);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrapping_param);
	// set texture filtering parameters
	//glBindSampler(this->sampler_binding_location, samplers[2]);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minification_filter);
	//glBindSampler(this->sampler_binding_location, samplers[3]);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magnification_filter);

	

	glTextureParameteri(this->textureID, GL_TEXTURE_BASE_LEVEL, 0);
	glTextureParameteri(this->textureID, GL_TEXTURE_MAX_LEVEL, 4);


	glTextureSubImage2D(this->textureID, 0, 0, 0, this->textureWidth, this->textureHeight, GL_RGBA, GL_UNSIGNED_BYTE, image);
	//Generating mipmap:
	glGenerateTextureMipmap(this->textureID);


	stbi_image_free(image);

	std::cout << "Texture " << this->textureID << "loaded\n";
	this->savedTarget = GL_TEXTURE_2D;
	return this->textureID;
}


/////////ANIMATED SPRITE SHEETS:
//load_opengl_texture_array(...) uploads a 2Dtexture array to opengl as long as this texture object hasn't already been assigned:
GLuint Texture::loadOpenGLTextureArray(const std::string& imagefilepath/*, Shader* shader_reference*/,
	GLuint start_frame = 0, GLuint last_frame = 1, GLuint number_of_columns = 1, GLuint number_of_rows = 1,
	GLenum wrapping_param = GL_REPEAT, GLenum minification_filter = GL_NEAREST, GLenum magnification_filter = GL_NEAREST
)
{
	//Error Handling: If these parameters are invalid values (Must be above 0):
	if (last_frame == 0 || number_of_columns == 0 || number_of_rows == 0)
	{
		std::cout << "load_opengl_texture_array(..) missused. number_of.. variables must be over 0: "
			<< last_frame << " " << number_of_columns << " " << number_of_rows << "\n";
		return 0;
	}
	//Total frames:
	int total_frames = last_frame - start_frame + 1;
	if (total_frames < 1)
	{
		std::cout << "total_frames is invalid\n";
		return 0;	
	}

	//Don't know what nrChannels does. not used:
	int nrChannels{};
	//Height and Width of the image being loaded:
	int textureHeight, textureWidth;
	//Flipping the image loader to get right orientation on load:
	stbi_set_flip_vertically_on_load(true);
	//Getting the image:
	unsigned char* image = stbi_load(imagefilepath.c_str(), &textureWidth, &textureHeight, &nrChannels, STBI_rgb_alpha);
	//Cutting image into several frames:
	//Error Handling if the image wasn't loaded:
	if (!image)
	{
		printf("failed to load image for texture_array, \"%s\"\n", imagefilepath.c_str());
		return 0;
	}
	std::cout << "entire image: " << unsigned(image) << std::endl;
	//Cutting image into each frame:
	auto frames = cutImageIntoVectorlist(image, textureWidth, textureHeight, number_of_rows, number_of_columns);

	//If it is already assigned a  texture:
	if (this->textureID != 0)
	{
		std::cout << "This object has already been assigned a texture (texID: " << this->textureID << ").\n";
		return 0;
	}
	//getting the shaderprogramID:
	//this->usedShaderProgram = shader_reference->getShaderProgram();






	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &this->textureID);
	//getting the sampler location:
//	this->textureSamplerLocation = TEXTURE_UNIT_SAMPLER_LOCATION//glGetUniformLocation(this->usedShaderProgram, "image_sampler_array");
	//getting the sampler location for texture array layer (z-axis):
	this->textureSamplerLayerLocation = TEXTURE_UNIT_ARRAY_SAMPLER_LOCATION;//glGetUniformLocation(this->used_shader_program, "image_sampler_array_layer");
	glBindTextureUnit(this->textureSamplerLocation, this->textureID);


	std::cout << " teture id is: " << this->textureSamplerLocation << std::endl;
	//Allocating storage:
	glTextureStorage3D(this->textureID, 2, GL_RGBA8, textureWidth / number_of_columns, textureHeight / number_of_rows, total_frames);

	//// set the texture wrapping parameters

	GLuint sampler{};
	glCreateSamplers(1, &sampler);

	// set the texture wrapping parametersawdas
	glBindSampler(this->textureSamplerLocation, sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrapping_param);	// set texture wrapping to GL_REPEAT (default wrapping method)
	//glBindSampler(this->sampler_binding_location, samplers[1]);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrapping_param);
	// set texture filtering parameters
	//glBindSampler(this->sampler_binding_location, samplers[2]);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minification_filter);
	//glBindSampler(this->sampler_binding_location, samplers[3]);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magnification_filter);



	glTextureParameteri(this->textureID, GL_TEXTURE_BASE_LEVEL, 0);
	glTextureParameteri(this->textureID, GL_TEXTURE_MAX_LEVEL, 4);










	//Frame counter do put each texture into 
	GLuint frame = start_frame;
	GLuint i{};
	while (frame <= last_frame)
	{
		std::cout << "pushing frame: " << frame << std::endl;
		// The `my_gl_format` represents your cpu-side channel layout.
		// Both GL_RGBA and GL_BGRA are common. See the "format" section
		// of this page: https://www.opengl.org/wiki/GLAPI/glTexImage3D
		glTextureSubImage3D(
			this->textureID,
			0,					// mipmap level
			0,		// Offset of each texture
			0,		// Offset of each texture
			i,				// Offset of each texture (each frame in out sprite animation)
			textureWidth / number_of_columns,		// width
			textureHeight / number_of_rows,		// height
			1,					// depth
			GL_RGBA,				// cpu pixel format
			GL_UNSIGNED_BYTE,	// cpu pixel coord type
			frames[frame].data() //image//			//Image data
		);
		i++;
		frame++;
	}
	//glGenerateTextureMipmap(this->texID);

	//Remove maybe:
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	stbi_image_free(image);
	this->savedTarget = GL_TEXTURE_2D_ARRAY;
	this->numberOfFrames = total_frames;
	std::cout << "Texture: " << this->textureID << " loaded. total frames: " << total_frames << ". startframe: " << start_frame << ". lastframe: " << last_frame << ". frame: " << frame << "\n";
	//std::cout << "Texture Array: " << texID << "loaded\n";
	return textureID;

}




//cut_one_frame(..) is used by cut_image_into_vectorlist(..) to get one image from an entire image:
std::vector<uint8_t> Texture::cutOneFrame(unsigned char* image, GLuint start, GLuint end, GLuint jump, GLuint width)
{
	//Vector used to get and structure a new image:
	std::vector<uint8_t> frame{};
	//Index to point where we are in tre image (starts at start):
	GLuint index = start;
	//as long as the entire picthure isn't read:
	auto j = 1;
	while (index < end)
	{

		//For each row of pixels:
		for (int i = 0; i < width; i++)
		{

			frame.push_back(image[index++]);
		}
		//Jump to next iteration of relevant pixels. 
		//-1 is because index jumps 1 too much at the very end (might change):
		index += (jump);
		j++;
	}

	return frame;
}

























//Function goes through char array and cuts out each frame accourding to the parameters. It will fail if the 
//Rows and columns don't divide image_width/height into whole numbers:
std::vector<std::vector<uint8_t>> Texture::cutImageIntoVectorlist(unsigned char* image, GLuint image_width, GLuint image_height,
	GLuint numb_rows, GLuint numb_columns)
{

	//Vector containing all the frames that we extract from the image:
	std::vector<std::vector<uint8_t>> all_frames{};
	//One pixe (RGBA):
	GLuint pixelsize = 4;
	//amount of pixels per frame:
	GLuint framesize = (image_height / numb_rows) * (image_width / numb_columns) * pixelsize;
	////Finding end frame:
	//GLuint end = framesize*(start_frame+number_of_frames);
	//How much we have to jump to get each frame:
	GLuint jump = (image_width - (image_width / numb_columns)) * pixelsize;




	//Index, where we currently are in the image:
	GLuint index{};
	//Jump to find end of that frame (height of one frame - 1) * width of entire image + width of one frame:
	GLuint end_jump = index + ((((image_height / numb_rows) - 1) * image_width) + (image_width / numb_columns)) * pixelsize;
	GLuint frame_width = (image_width / numb_columns) * pixelsize;


	GLuint index_next_row_jump = frame_width + ((image_width * ((image_height / numb_rows) - 1)) * pixelsize);


	GLuint total_frames = numb_columns * numb_rows;
	GLuint j{};
	//For loop gos through every frame and adds it to a vector of all the frames:			
	for (GLuint currentFrame = 0; currentFrame < total_frames; currentFrame++)
	{
		GLuint end = index + end_jump;

		std::vector<uint8_t> frame = cutOneFrame(image, index, end, jump, frame_width);
		//If frame wasn't cut out:
		if (frame.empty())
		{
			std::cout << "couldn't cut_one_frame(..)\n";
			//return empty list if failed:
			return {};
		}
		//add frame to list of frames:
		all_frames.insert(all_frames.begin() + j, frame);
		//		all_frames.push_back(frame);


				//Moving ot the next frame:
				//		std::cout << "entire frame, " << current_frame << ": " << frame << std::endl;
		if (j < (numb_columns - 1))
		{
			index += frame_width;
			j++;

		}
		else
		{
			index += index_next_row_jump;
			j = 0;
		}

	}
	return all_frames;
}


bool Texture::animateTextureArray(GLuint frameRate, GLfloat delta_Time)
{
	this->timeSinceLastAnimationFrame += delta_Time;
	//animateUpdate:
	GLfloat animationUpdateTime = 1.f / frameRate;
	if ((timeSinceLastAnimationFrame >= animationUpdateTime) && (this->numberOfFrames > 0))
	{

		this->currentFrame++;
		if (this->currentFrame >= this->numberOfFrames)
		{
			this->currentFrame = 0;
		}
		this->timeSinceLastAnimationFrame = 0.f;
		return true;
	}
	return false;
}

bool Texture::setTextureArrayFrame(GLuint frame = 0)
{
	if (this->numberOfFrames > 0 && frame < this->numberOfFrames)
	{
		this->currentFrame = frame;
	}
	return false;
}