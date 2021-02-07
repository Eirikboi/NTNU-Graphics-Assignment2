void updateSprite(glm::vec2& spriteCords);
GLuint activeShaderProgram;

/** Constants for vertex attribute locations */
constexpr auto va_position = 0;
constexpr auto va_color = 1;
constexpr auto va_texture = 2;
/** Constants for uniform locations */
// constexpr auto ul_texture_a = 1;
// constexpr auto ul_texture_b = 2;
int i = 0;
int j = 1;
glm::vec2 test = glm::vec2(0.f, 1.f);

/**
 * Defines a renderable object used in this example
 */
struct Renderable
{
    GLuint vao{};
    GLuint vbo{};
    GLuint ebo{};
    GLuint indexCount{};
};

/**
 * Defines the vertex layout used for this example
 * Also - Task 3 is related to this Vertex
 */
struct Vertex
{
    glm::vec2 position;
    glm::vec3 color;
    glm::vec2 texture;
};


/**
 * Creates all OpenGL resources required for drawing a sprite using the concept of a Renderable
 *
 * A renderable simply holds all buffers and vertex arrays required to addToScene a single object. It can contain a circle, square,
 * cube, rectangle or other fancy shapes in a single struct. This is nice as we have all the resources we need in one place,
 * except for textures and other uniform data.
 *
 * @return A renderable with all necessary OpenGL data
 */
Renderable create_sprite_data()
{
    /** This is what we will return */
    Renderable out{};

    /** Hard code sprite and index data (since it's a trivial mesh) - Also Task 3 is related to this sprite data */
    std::vector<Vertex> sprite_data = { {{-.5f, -.5f}, {1.f, 0.5f, 1.f}, {0.f,0.75f}}, //0 down left

                                       {{.5f, -.5f}, {1.f, 1.f, 1.f}, {0.25f,0.75f}}, //1 down right

                                       {{.5f, .5f}, {1.f, 1.f, 1.f}, {0.25f,1.f}}, //2 up right

                                       {{-.5f, .5f}, {1.f, 1.f, 1.f}, {0.f,1.f}} //3 up left
    };


    /** As you should be used to by now, we transfer the data into the buffer */
    glGenBuffers(1, &out.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, out.vbo);
    glBufferData(GL_ARRAY_BUFFER, vector_byte_size(sprite_data), sprite_data.data(), GL_STATIC_DRAW);

    /** Create a buffer of indices that we will use for our indexed drawing */
    std::vector<unsigned> indices = {/* Task 1A: Add proper indices to this initializer list (Hint: Should be 6 of them) */
        3, 1, 0,
        3, 2, 1
    };
    out.indexCount = indices.size();

    glGenBuffers(1, &out.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, out.ebo);


    /**
     * Task 1B: Fill this buffer with the data from the indices vector
     */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vector_byte_size(indices), indices.data(), GL_STATIC_DRAW);

    /** Now create the VAO for it */
    glGenVertexArrays(1, &out.vao);
    glBindVertexArray(out.vao);

    /** Set attributes as of shader */
    glVertexAttribPointer(va_position, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glVertexAttribPointer(va_color, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
    glVertexAttribPointer(va_texture, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texture)));

    /** Enable attributes */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    return out;
}

/**
 * Load the texture at the given relative filepath and put it into OpenGL for use in rendering
 *
 * @warning This function is NOT implemented by tutors
 *
 * @param filepath The relative filepath to the texture
 * @return An OpenGL handle to a 2D Texture
 */
GLuint loadOpenglTexture(const std::string& filepath)
{

    /**
     * Task 2A:
     *  - You must use the STB Image library to load a texture in here
     *  - You must initializeGameObject the texture into an OpenGL texture
     *    - This means creating a texture with glGenTextures or glCreateTextures (4.5)
     *    - And transferring the loaded texture data into this texture
     *    - And setting the texture format
     *    - Doing research and discovering solutions by googling or reading docs / other sources. (It is a skill too!)
     *  - Finally return the valid texture
     */
    GLuint textureID;
    glGenTextures(1, &textureID);
    //    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    //GLuint texID2;
    //glGenTextures(1, &texID2);
    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, texID2);
         // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int height{};
    int width{};
    int nrChannels{};

    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(filepath.c_str(), &height, &width, &nrChannels, 0);
    if (!image)
    {
        std::cout << "failed to load image\n";
        return 0;
    }
    //unsigned char* image2 = stbi_load("resources/textures/sprite.png", &height, &width, &nrChannels, 0);
    //if (!image2)
    //{
    //    std::cout << "failed to load image2\n";
    //    return 0;
    //}

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
    //glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);


    return textureID;
}

void addToScene(float dt, float time, const Renderable& renderable)
{
    /** Could set some uniforms here if needed (matrices, *cough*) */
    glm::mat4 transform = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    glm::mat4 camera = glm::lookAt(glm::vec3(0.5f * glm::cos(time), 0.5f * glm::sin(time), 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 view = glm::perspective(glm::radians(45.f), (float)16.f / (float)9.f, 0.1f, 100.f);
    //glUniform2f(5, 1.f, 1.f);
    glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(transform));
    glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(camera));
    glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(view));

    /*    glm::mat4 camera =
    glm::mat4 projection =
    */
    /** Bind all required data before drawing with indices (elements) */
    glBindVertexArray(renderable.vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderable.ebo);
    glDrawElements(GL_TRIANGLES, renderable.indexCount, GL_UNSIGNED_INT, nullptr);
    updateSprite(test);
    glUniform2f(5, test.x, test.y);
}


void updateSprite(glm::vec2& spriteCords) {

    spriteCords.x += 0.25f;
    if (i > 2)
    {
        i = 0;
        spriteCords.y -= 0.25f;
    }
    else
    {
        i++;
    }
    std::cout << "X" << spriteCords.x << " y" << spriteCords.y << " i" << i << '\n';
}



int main()
{
    /** Initialize GL, Shader and set up Debug Callback for sensible error messages */
    auto window = initialize_glfw_and_gl();
    auto shader = make_shader();
    create_debug_callback();

    /** Create sprite that we will use and load texture */
    auto sprite = create_sprite_data();
    // auto texture = load_opengl_texture("resources/textures/cat.png");
    auto texture2 = loadOpenglTexture("resources/textures/sprite.png");

    /** Used to capture the delta time */
    auto timeLastFrame = glfwGetTime();


    /** Enable program and set background to dark blue, we only have to enable program once since it's the only shader now */
    glUseProgram(shader);
    glClearColor(0.f, 0.15f, 0.3f, 1);
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window))
    {
        /** Compute delta time */
        const auto dt = glfwGetTime() - timeLastFrame;
        timeLastFrame = glfwGetTime();

        /** Start drawing and clearing */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        addToScene(dt, static_cast<float>(glfwGetTime()), sprite);
        glfwSwapBuffers(window);
        glfwPollEvents();
        Sleep(400);
    }

    /** Clean up (important to do this) */
    glUseProgram(0u);
    glDeleteProgram(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
