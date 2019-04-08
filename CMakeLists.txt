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
    add_executable(${PROJECT_NAME} test.cpp Loader/ShaderLoader.h Loader/ShaderLoader.cpp Loader/TextureLoader.h Loader/TextureLoader.cpp Transform.h Camera/Camera.cpp Camera/Camera.h Timer.cpp Timer.h stb_image.h Model/Mesh.h Model/Mesh.cpp Model/Model.cpp Model/Model.h TestLight.h Object.h Light/Light.h Light/Light.cpp Light/PointLight.cpp Light/PointLight.h Light/SpotLight.cpp Light/SpotLight.h Light/DirLight.cpp Light/DirLight.h LightManager.cpp LightManager.h Light/Light_include.h Scene/BaseScene.h Scene/SkyBox.cpp Scene/SkyBox.h Scene/Flat.cpp Scene/Flat.h Scene/BaseScene.cpp)
else()
    add_executable(${PROJECT_NAME} main.cpp Loader/ShaderLoader.h Loader/ShaderLoader.cpp Loader/TextureLoader.h Loader/TextureLoader.cpp Transform.h Camera/Camera.cpp Camera/Camera.h Timer.cpp Timer.h stb_image.h Model/Mesh.cpp Model/Mesh.h Model/Model.cpp Model/Model.h TestLight.h Object.h Light/Light.h Light/Light.cpp Light/PointLight.cpp Light/PointLight.h Light/SpotLight.cpp Light/SpotLight.h Light/DirLight.cpp Light/DirLight.h LightManager.cpp LightManager.h Light/Light_include.h Scene/BaseScene.h Scene/SkyBox.cpp Scene/SkyBox.h Scene/Flat.cpp Scene/Flat.h Scene/BaseScene.cpp)
endif()

target_link_libraries(${PROJECT_NAME} assimp SOIL glew32 glfw3 glu32 opengl32)

