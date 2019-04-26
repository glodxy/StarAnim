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
    add_executable(${PROJECT_NAME} test.cpp Loader/ShaderLoader.h Loader/ShaderLoader.cpp Loader/TextureLoader.h Loader/TextureLoader.cpp Transform.h Camera/Camera.cpp Camera/Camera.h Timer.cpp Timer.h stb_image.h Object/Model/Mesh.h Object/Model/Mesh.cpp Object/Model/Model.cpp Object/Model/Model.h TestLight.h Object.h Light/Light.h Light/Light.cpp Light/PointLight.cpp Light/PointLight.h Light/SpotLight.cpp Light/SpotLight.h Light/DirLight.cpp Light/DirLight.h LightManager.cpp LightManager.h Light/Light_include.h Object/Scene/BaseScene.h Object/Scene/SkyBox.cpp Object/Scene/SkyBox.h Object/Scene/Flat.cpp Object/Scene/Flat.h Object/Scene/BaseScene.cpp RenderManager.cpp RenderManager.h Object/Object_include.h Object/Model/Model_include.h Object/Scene/Scene_include.h ShaderManager.cpp ShaderManager.h Object/BaseObject.h)
else()
    add_executable(${PROJECT_NAME} main.cpp Loader/ShaderLoader.h Loader/ShaderLoader.cpp Loader/TextureLoader.h Loader/TextureLoader.cpp Transform.h Camera/Camera.cpp Camera/Camera.h Timer.cpp Timer.h stb_image.h Object/Model/Mesh.cpp Object/Model/Mesh.h Object/Model/Model.cpp Object/Model/Model.h TestLight.h Object.h Light/Light.h Light/Light.cpp Light/PointLight.cpp Light/PointLight.h Light/SpotLight.cpp Light/SpotLight.h Light/DirLight.cpp Light/DirLight.h LightManager.cpp LightManager.h Light/Light_include.h Object/Scene/BaseScene.h Object/Scene/SkyBox.cpp Object/Scene/SkyBox.h Object/Scene/Flat.cpp Object/Scene/Flat.h Object/Scene/BaseScene.cpp RenderManager.cpp RenderManager.h Object/Object_include.h Object/Model/Model_include.h Object/Scene/Scene_include.h ShaderManager.cpp ShaderManager.h Object/BaseObject.h)
endif()

target_link_libraries(${PROJECT_NAME} assimp SOIL glew32 glfw3 glu32 opengl32)

