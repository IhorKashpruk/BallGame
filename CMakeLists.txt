cmake_minimum_required(VERSION 3.7)
project(testC__)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -pedantic -Wno-unused -Wextra")

file(GLOB Box2D_Code
        "src/libs/Box2D/Collision/*"
        "src/libs/Box2D/Collision/Shapes/*"
        "src/libs/Box2D/Common/*"
        "src/libs/Box2D/Dynamics/*"
        "src/libs/Box2D/Dynamics/Contacts/*"
        "src/libs/Box2D/Dynamics/Joints/*"
        "src/libs/Box2D/Rope/*")


set(SOURCE_FILES main.cpp
        src/libs/Box2D/Box2D.h
        ${Box2D_Code}
        src/libs/json.hpp
        src/utility/primitive_types.h
        src/ui/interfaces/IDrawable.h
        src/ui/AUIO.h
        src/ui/interfaces/IResponsible.h
        src/ui/logic/Subject.h
        src/ui/logic/IObserver.h
        src/ui/UIO.h
        src/ui/interfaces/IDimensional.h
        src/Draftsman.h
        src/ui/physics/PUIO.h
        src/ui/AChecker.h
        src/ui/Context.h
        src/utility/P_P_M.h
        src/utility/math_things.h
        src/utility/other_things.h
        src/ui/logic/ALogic.h
        src/ui/ModernContext.h
        src/ui/logic/MenuLogic.h
        src/Factory.h
        src/ContextManager.h
        src/ui/Button.h
        src/ui/physics/PO.h
        src/ui/physics/WorldWrapper.h
        src/ui/physics/box2d_properties.h
        src/Game.h src/Interceptor.h
        src/window_properties.h
        src/theme_properties.h
        src/ui/logic/GameLogic.h
        src/ui/Text.h
        src/ui/ColorScheme.h
        src/ui/physics/WorldUIO.h
        src/ui/logic/Camera.h
        src/ui/logic/WorldLogic.h
        src/ui/physics/Ball.h
        src/ui/logic/AfterGameLogic.h
        src/JsonReader.h src/LevelManager.h src/ui/physics/Windmill.h src/ui/interfaces/Identity.h src/ui/interfaces/Colorful.h src/ui/Label.h src/ui/interfaces/IText.h src/ui/physics/Influential.h)

include_directories(src)
include_directories(src/libs)
add_executable(testC__ ${SOURCE_FILES})
target_link_libraries(testC__ SDL2 SDL2_image SDL2_gfx SDL2_ttf pthread)