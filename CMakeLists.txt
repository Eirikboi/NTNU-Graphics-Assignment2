cmake_minimum_required (VERSION 3.14 FATAL_ERROR)
project(Assignment_2 VERSION 2.0.0)

# Add dependencies
add_subdirectory(external)

# Create .exe file (essentially)
add_executable(${PROJECT_NAME})

# Add additional source files here
target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    
    ${CMAKE_CURRENT_LIST_DIR}/include/game/game_application.h#-
    ${CMAKE_CURRENT_LIST_DIR}/include/game/struct_transform.h #-
    ${CMAKE_CURRENT_LIST_DIR}/include/game/game_input.h
    ${CMAKE_CURRENT_LIST_DIR}/include/game/gl_error_handling.h
    ${CMAKE_CURRENT_LIST_DIR}/include/game/global_game_input.h
    ${CMAKE_CURRENT_LIST_DIR}/include/game/glutil.h
    ${CMAKE_CURRENT_LIST_DIR}/include/game/game_user_interface.h
    ${CMAKE_CURRENT_LIST_DIR}/include/game/game_movement.h
    ${CMAKE_CURRENT_LIST_DIR}/include/game/game_platform.h 

    #${CMAKE_CURRENT_LIST_DIR}/include/GameApplicationGui.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/renderer.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/renderer_model.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/renderer_vertex_data.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/resource_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/renderer_shader.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/renderer_sprite.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/renderer_texture.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/renderer_light.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/renderer_light_shadows.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/global_renderer_shader_locations.h
    ${CMAKE_CURRENT_LIST_DIR}/include/game/game_mesh.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/global_renderer_shader_locations.h
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer/global_renderer_information.h

    ${CMAKE_CURRENT_LIST_DIR}/src/game/glutil.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_application.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_application_input.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_application_user_interface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_input.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_mesh.cpp 
    #-
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_input.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_movement.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_platform.cpp
    
    
    # ${CMAKE_CURRENT_LIST_DIR}/src/game/game_transform.cpp #-
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_objects_input_callbacks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/game/game_user_interface.cpp

    #${CMAKE_CURRENT_LIST_DIR}/src/GameApplicationGui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer/renderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer/renderer_model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer/renderer_shader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer/renderer_texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer/renderer_light.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer/renderer_light_shadows.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer/camera.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer/resource_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer/renderer_sprite.cpp
    
    # Game objects are stored here
    ${CMAKE_CURRENT_LIST_DIR}/src/gameObjects/game_objects.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gameObjects/game_object.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gameObjects/game_objects.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/gameObjects/game_object.cpp


    ${CMAKE_CURRENT_LIST_DIR}/src/physics/game_square_bounds.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/physics/game_rigidbody.h 
    ${CMAKE_CURRENT_LIST_DIR}/src/physics/game_square_bounds.h
    ${CMAKE_CURRENT_LIST_DIR}/src/physics/game_intersectdata.h

    
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imconfig.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_impl_glfw.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_internal.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_widgets.cpp
# "src/renderer/renderer_light.cpp" "src/renderer/renderer_light_shadows.cpp")
)
# Set include directories
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/include/game
    ${CMAKE_CURRENT_LIST_DIR}/include/renderer

    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/src/game
    ${CMAKE_CURRENT_LIST_DIR}/src/renderer
    ${CMAKE_CURRENT_LIST_DIR}/src/gameObjects
    ${CMAKE_CURRENT_LIST_DIR}/src/physics#-
)

# Link with external libraries
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    glad::glad
    gfx::gfx
    glm
    glfw
    stbimage::stbimage
    tinyobj::tinyobj
)

# Enable C++ 17
target_compile_features(
    ${PROJECT_NAME}
    PRIVATE
    cxx_std_17
)

# Copy resources to binary directory
add_custom_target(
    copy_shaders ALL
    ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E echo "Copied resource directory to binary directory ${CMAKE_CURRENT_BINARY_DIR}"
)

