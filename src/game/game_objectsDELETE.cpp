#include <game_objects.h>
#include <global_game_variables.h>
int shader;
int renderable;
int texture;
int axeo;
int axet;
int testShadowShader;
GameObjects::GameObjects()
{
}

GameObjects::~GameObjects()
{
}
//Initialize() Initializes everything that needs to be initialized:
void GameObjects::initializeEverything()
{
    int x;
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,&x);
    gameRenderer.addShader(&shader,"resources/shaders/sprite_vertex.vert", "resources/shaders/sprite_fragment.frag");
    gameRenderer.addShader(&testShadowShader, "resources/shaders/test_depth_vertex.vert", "resources/shaders/test_depth_fragment.frag", false);
    if (shader == -1)
    {
        exit(-1);
    }
   
  //  auto shader2 = renderer.add_shader("resources/shaders/sprite_vertex.vert", "resources/shaders/sprite_fragment.frag");
    gameRenderer.addRenderable(&renderable,"resources/objects/untitled.obj");
    gameRenderer.addRenderable(&axeo,"resources/objects/axe.obj");
    gameRenderer.addTexture(&axet, "resources/textures/axe_color.png", shader, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
    gameRenderer.addTexture(&texture, "resources/textures/diamond.png",shader, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);

    int test;
    gameRenderer.addTextureArray(&test, "resources/textures/diamond.png", shader, 0, 3, 2, 2, GL_REPEAT, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST);
    gameRenderer.setTextureArrayFrame(test, 0);
    
    std::cout << shader << ' ' << renderable << ' ' << texture << std::endl;
    //this->spriteRenderer.initialize_sprite();
    //this->loadTextures();
}

//draw_game_objects() goes through everything to be drawn and draws it:
void GameObjects::drawGameObjects()
{
}

void GameObjects::update(GLFWwindow* gameWindow, GLdouble deltaTime, GLdouble time)
{
    
    this->gameCamera.processInput(gameWindow,deltaTime);
    this->gameRenderer.setCamera(this->gameCamera.getCameraPositionVector(), this->gameCamera.getCameraTargetVector(), this->gameCamera.getCameraUpVector());
    glm::vec3   sposition = glm::vec3(1.f, /*4 * glm::sin(time)*/0.f, 1.f),
                ssize = glm::vec3(0.02f, 0.02f, 0.02f),
                srotation_axis = glm::vec3(1.f, 1.f, 1.f),
                scolor = glm::vec3(1.f, 1.f, 1.f);

    glm::vec3   dposition = glm::vec3(1.f, 0.f, 4 * glm::sin(time)),
                dsize = glm::vec3(0.02f, 0.02f, 0.02f),
                drotation_axis = glm::vec3(1.f, 1.f, 1.f),
                dcolor = glm::vec3(1.f, 1.f, 1.f);

    glm::vec3   qposition = glm::vec3(1.f, 0.f, 4 * glm::sin(time)),
                qsize = glm::vec3(0.02f, 0.02f, 0.02f),
                qrotation_axis = glm::vec3(1.f, 1.f, 1.f),
                qcolor = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3   Cposition = glm::vec3(0.f, 0.f, 0.f),
                Csize = glm::vec3(10.f, 0.02f, 10.f),
                Crotation_axis = glm::vec3(0.f, 1.f, 0.f),
                Ccolor = glm::vec3(1.f, 1.f, 1.f);

    GLfloat srotate = 50 * time;
    GLfloat drotate = 0.f;
    GLfloat qrotate = 0.f;
        gameRenderer.addToScene(axeo, axet, shader, &sposition, &ssize, &srotate, &srotation_axis, nullptr);
        gameRenderer.addToScene(axeo, axet, shader, &dposition, &dsize, &drotate, &drotation_axis, nullptr);
        gameRenderer.addToScene(renderable, texture, shader, &Cposition, &Csize, &drotate, &Crotation_axis, nullptr);

        gameRenderer.drawScene(testShadowShader);
  //  gameRenderer.settingMatrices(axeo, shader, glm::vec3(1.f, /*4 * glm::sin(time)*/0.f, 1.f), glm::vec3(0.02f, 0.02f, 0.02f), 50 * time, glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f));
  //  gameRenderer.addToScene(axeo, axet, shader);
  //  gameRenderer.settingMatrices(axeo, shader, glm::vec3(1.f, 0.f, 4*glm::sin(time)), glm::vec3(0.02f, 0.02f, 0.02f), 0.f/*20 * time*/, glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
  //  gameRenderer.addToScene(axeo, axet, shader);

  //  //gameRenderer.settingMatrices(renderable, shader, glm::vec3(glm::sin(2 * time), 1.f, 0.f), glm::vec3(0.5f, 0.5f, 0.5f), 50*time, glm::vec3(0.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f));
  //  gameRenderer.settingMatrices(renderable, shader, glm::vec3(-3.f, -1.f, 0.f/*4 * glm::sin(time)*/), glm::vec3(10.0f, 0.1f, 10.f)/*glm::vec3(1)*/, 0.f, glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f));
  ////  gameRenderer.settingMatrices(renderable, shader, glm::vec3(-3.f, -1.f, 0.f/*4 * glm::sin(time)*/), glm::vec3(10.f, 10.f, 0.1f)/*glm::vec3(1)*/, /*5 * glfwGetTime()*/0.f, glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
  //  gameRenderer.addToScene(renderable, texture, shader);
  //  gameRenderer.settingMatrices(renderable, shader, glm::vec3(0.f,-1.5f,0.f), /*glm::vec3(10.0f, 0.1f, 10.f)*/glm::vec3(1), 0.f, glm::vec3(1), glm::vec3(1));
  //  gameRenderer.addToScene(renderable, texture, shader);

}
void GameObjects::loadTextures()
{
    
}


