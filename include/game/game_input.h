#ifndef GAME_INPUT_H
#define GAME_INPUT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
/*
GLFWInput:

*/
class GameInput
{
public:
    GameInput(GLFWwindow* window);
    ~GameInput();
    
private:


    GLFWwindow* window;
    //process_mouse() returns the recieved input from mouse:
};
#endif // !GAMEINPUT_H







//SLETT NÅR VI HAR BEDRE LØSNING:

//public:
//static GameInput& getInstance()
//{
//    // Guaranteed to be destroyed:
//    static GameInput    instance; 
//    // Instantiated on first use:
//    return instance;
//}
////If declared worng:
////GameInput(GameInput const&) = delete;
////void operator=(GameInput const&) = delete;

//// Note: Scott Meyers mentions in his Effective Modern
////       C++ book, that deleted functions should generally
////       be public as it results in better error messages
////       due to the compilers behavior to check accessibility
////       before deleted status
//void process_mouse_callback(GLFWwindow* window, double x_pos, double y_pos)
//{
//    getInstance().process_mouse_callback_impl(window, x_pos, y_pos);
//};
//void scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
//{
//    getInstance().scroll_callback_impl(window, x_pos, y_pos);
//};


//private:
////private constructor to prevent creating copies:
//GameInput() {}                    // Constructor? (the {} brackets) are needed here.
//GameInput(GameInput const&);              
//void operator=(GameInput const&);
