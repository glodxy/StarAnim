cmake_minimum_required(VERSION 3.12)
option(_DEBUG ON)
if(DEFINED _DEBUG)
    project(Test)
else()
    project(StarAnim)
endif()
set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH e:/project/${PROJECT_NAME})

if(DEFINED _DEBUG)
    add_executable(${PROJECT_NAME} test.cpp ShaderLoader.h ShaderLoader.cpp TextureLoader.h TextureLoader.cpp Transform.h Camera.cpp Camera.h Timer.cpp Timer.h stb_image.h Mesh.h Mesh.cpp Model.cpp Model.h TestLight.h Object.h Light/Light.h Light/Light.cpp Light/PointLight.cpp Light/PointLight.h Light/SpotLight.cpp Light/SpotLight.h Light/DirLight.cpp Light/DirLight.h LightManager.cpp LightManager.h Light/Light_include.h)
else()
    add_executable(${PROJECT_NAME} main.cpp ShaderLoader.h ShaderLoader.cpp TextureLoader.h TextureLoader.cpp Transform.h Camera.cpp Camera.h Timer.cpp Timer.h stb_image.h Mesh.cpp Mesh.h Model.cpp Model.h TestLight.h Object.h Light/Light.h Light/Light.cpp Light/PointLight.cpp Light/PointLight.h Light/SpotLight.cpp Light/SpotLight.h Light/DirLight.cpp Light/DirLight.h LightManager.cpp LightManager.h Light/Light_include.h)
endif()

target_link_libraries(${PROJECT_NAME} assimp SOIL glew32 glfw3 glu32 opengl32)

