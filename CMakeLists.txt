cmake_minimum_required(VERSION 3.8)
project(GraphicsPlayground_Mac)

set(CMAKE_CXX_STANDARD 11)
include_directories(
        GraphicsPlayground-Mac
        GraphicsPlayground-Mac/CityModelExample
        GraphicsPlayground-Mac/Interpolation
        GraphicsPlayground-Mac/RotateCube
        GraphicsPlayground-Mac/RotateTextureCube
        GraphicsPlayground-Mac/BlendExample
        GraphicsPlayground-Mac/WaterRendering
        GraphicsPlayground-Mac/ParticleSystem
        GraphicsPlayground-Mac/common
        SimpleOpenGLImageLibrary/src
        Tiny
        wolf
        .)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries( ${GLFW_LIBRARIES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
link_libraries( ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )


set(SOURCE_FILES
        GraphicsPlayground-Mac/BlendExample/BlendExample.cpp
        GraphicsPlayground-Mac/BlendExample/BlendExample.h
        GraphicsPlayground-Mac/CityModelExample/AABBCollider.cpp
        GraphicsPlayground-Mac/CityModelExample/AABBCollider.h
        GraphicsPlayground-Mac/CityModelExample/Camera.cpp
        GraphicsPlayground-Mac/CityModelExample/Camera.h
        GraphicsPlayground-Mac/CityModelExample/CityModelExample.cpp
        GraphicsPlayground-Mac/CityModelExample/CityModelExample.h
        GraphicsPlayground-Mac/CityModelExample/CityModeller.cpp
        GraphicsPlayground-Mac/CityModelExample/CityModeller.h
        GraphicsPlayground-Mac/CityModelExample/Collider.cpp
        GraphicsPlayground-Mac/CityModelExample/Collider.h
        GraphicsPlayground-Mac/CityModelExample/collidetest.cpp
        GraphicsPlayground-Mac/CityModelExample/CollisionDetector.cpp
        GraphicsPlayground-Mac/CityModelExample/CollisionDetector.h
        GraphicsPlayground-Mac/CityModelExample/CollisionHelper.h
        GraphicsPlayground-Mac/CityModelExample/CollisionPackage.h
        GraphicsPlayground-Mac/CityModelExample/Cube.h
        GraphicsPlayground-Mac/CityModelExample/CubemapTexture.cpp
        GraphicsPlayground-Mac/CityModelExample/CubemapTexture.h
        GraphicsPlayground-Mac/CityModelExample/DirectionalLight.h
        GraphicsPlayground-Mac/CityModelExample/DirectionalLightcpp.cpp
        GraphicsPlayground-Mac/CityModelExample/FormatTranslator.cpp
        GraphicsPlayground-Mac/CityModelExample/FormatTranslator.h
        GraphicsPlayground-Mac/CityModelExample/Frustum.cpp
        GraphicsPlayground-Mac/CityModelExample/Frustum.h
        GraphicsPlayground-Mac/CityModelExample/Helper.h
        GraphicsPlayground-Mac/CityModelExample/Light.h
        GraphicsPlayground-Mac/CityModelExample/Node.cpp
        GraphicsPlayground-Mac/CityModelExample/Node.h
        GraphicsPlayground-Mac/CityModelExample/Plane.h
        GraphicsPlayground-Mac/CityModelExample/Ray.cpp
        GraphicsPlayground-Mac/CityModelExample/Ray.h
        GraphicsPlayground-Mac/CityModelExample/SkyBox.cpp
        GraphicsPlayground-Mac/CityModelExample/SkyBox.h
        GraphicsPlayground-Mac/CityModelExample/Sphere.cpp
        GraphicsPlayground-Mac/CityModelExample/Sphere.h
        GraphicsPlayground-Mac/CityModelExample/SphereCollider.cpp
        GraphicsPlayground-Mac/CityModelExample/SphereCollider.h
        GraphicsPlayground-Mac/CityModelExample/struct.h
        GraphicsPlayground-Mac/CityModelExample/SurfaceMaterial.h
        GraphicsPlayground-Mac/CityModelExample/Triangle.h
        GraphicsPlayground-Mac/common/RenderTarget.cpp
        GraphicsPlayground-Mac/common/RenderTarget.h
        GraphicsPlayground-Mac/Interpolation/InterpolationExample.cpp
        GraphicsPlayground-Mac/Interpolation/InterpolationExample.h
        "GraphicsPlayground-Mac/ParticleSystem/AddVelAffector.cpp"
        "GraphicsPlayground-Mac/ParticleSystem/AddVelAffector.h"
        "GraphicsPlayground-Mac/ParticleSystem/Affector.h"
        "GraphicsPlayground-Mac/ParticleSystem/ColorAffector.cpp"
        "GraphicsPlayground-Mac/ParticleSystem/ColorAffector.h"
        "GraphicsPlayground-Mac/ParticleSystem/ColorBlendingAffector.cpp"
        "GraphicsPlayground-Mac/ParticleSystem/ColorBlendingAffector.h"
        "GraphicsPlayground-Mac/ParticleSystem/Effect.cpp"
        "GraphicsPlayground-Mac/ParticleSystem/Effect.h"
        "GraphicsPlayground-Mac/ParticleSystem/Emitter.cpp"
        "GraphicsPlayground-Mac/ParticleSystem/Emitter.h"
        "GraphicsPlayground-Mac/ParticleSystem/FadeAffector.cpp"
        "GraphicsPlayground-Mac/ParticleSystem/FadeAffector.h"
        "GraphicsPlayground-Mac/ParticleSystem/HelperFunction.cpp"
        "GraphicsPlayground-Mac/ParticleSystem/HelperFunction.h"
        "GraphicsPlayground-Mac/ParticleSystem/ParticleStruct.h"
        "GraphicsPlayground-Mac/ParticleSystem/ParticleSystemExample.cpp"
        "GraphicsPlayground-Mac/ParticleSystem/ParticleSystemExample.h"
        "GraphicsPlayground-Mac/ParticleSystem/ScaleAffector.cpp"
        "GraphicsPlayground-Mac/ParticleSystem/ScaleAffector.h"
        GraphicsPlayground-Mac/RotateCube/RotateCubeExample.cpp
        GraphicsPlayground-Mac/RotateCube/RotateCubeExample.h
        GraphicsPlayground-Mac/RotateTextureCube/RotateTextureCubeExample.cpp
        GraphicsPlayground-Mac/RotateTextureCube/RotateTextureCubeExample.h
        GraphicsPlayground-Mac/WaterRendering/WaterRenderingExample.cpp
        GraphicsPlayground-Mac/WaterRendering/WaterRenderingExample.hpp
        GraphicsPlayground-Mac/ExampleBase.cpp
        GraphicsPlayground-Mac/ExampleBase.hpp
        GraphicsPlayground-Mac/KeyboardInputHandler.hpp
        GraphicsPlayground-Mac/main.cpp
        GraphicsPlayground-Mac/MouseInputHandler.hpp
        GraphicsPlayground-Mac/Quad.cpp
        GraphicsPlayground-Mac/Quad.hpp
        GraphicsPlayground-Mac/Renderable.hpp
        GraphicsPlayground-Mac/stdafx.cpp
        GraphicsPlayground-Mac/stdafx.h
        GraphicsPlayground-Mac/WaterQuad.cpp
        GraphicsPlayground-Mac/WaterQuad.hpp
        "SimpleOpenGLImageLibrary/src/image_DXT.c"
        "SimpleOpenGLImageLibrary/src/image_DXT.h"
        "SimpleOpenGLImageLibrary/src/image_helper.c"
        "SimpleOpenGLImageLibrary/src/image_helper.h"
        "SimpleOpenGLImageLibrary/src/SOIL.c"
        "SimpleOpenGLImageLibrary/src/SOIL.h"
        "SimpleOpenGLImageLibrary/src/stb_image_aug.c"
        "SimpleOpenGLImageLibrary/src/stb_image_aug.h"
        "SimpleOpenGLImageLibrary/src/stbi_DDS_aug.h"
        "SimpleOpenGLImageLibrary/src/stbi_DDS_aug_c.h"
        Tiny/tinystr.cpp
        Tiny/tinystr.h
        Tiny/tinyxml.cpp
        Tiny/tinyxml.h
        Tiny/tinyxmlerror.cpp
        Tiny/tinyxmlparser.cpp
        wolf/W_Buffer.cpp
        wolf/W_Buffer.h
        wolf/W_BufferManager.cpp
        wolf/W_BufferManager.h
        wolf/W_Common.cpp
        wolf/W_Common.h
        wolf/W_IndexBuffer.cpp
        wolf/W_IndexBuffer.h
        wolf/W_Material.cpp
        wolf/W_Material.h
        wolf/W_MaterialManager.cpp
        wolf/W_MaterialManager.h
        wolf/W_Program.cpp
        wolf/W_Program.h
        wolf/W_ProgramManager.cpp
        wolf/W_ProgramManager.h
        wolf/W_Texture.cpp
        wolf/W_Texture.h
        wolf/W_TextureManager.cpp
        wolf/W_TextureManager.h
        wolf/W_Types.h
        wolf/W_VertexBuffer.cpp
        wolf/W_VertexBuffer.h
        wolf/W_VertexDeclaration.cpp
        wolf/W_VertexDeclaration.h
        Game.cpp
        Game.hpp)

add_executable(GraphicsPlayground_Mac ${SOURCE_FILES})


