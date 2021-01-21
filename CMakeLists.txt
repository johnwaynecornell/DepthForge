cmake_minimum_required(VERSION 3.00)

project(DepthForge)
set(CMAKE_CXX_STANDARD 11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Qt library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
# OpenGL
find_package(OpenGL)

include_directories(QtOpengl5_INCLUDE_DIRS)

# executable

add_executable(DepthForge version.h main.cpp
        Threading/Sync.h Threading/Sync.cpp PixelGfx/GfxThreadWorker.h PixelGfx/GfxThreadWorker.cpp
        PixelGfx/JWC_PixelGfx.h PixelGfx/JWC_PixelGfx.cpp PixelGfx/GfxBlt.cpp

        Image/Image.cpp Image/Image.h Image/Artif3d.cpp Image/DrawImage.cpp
        Image/TrigCache.cpp Image/TrigCache.h Image/Geometry.cpp Image/Geometry.h
        Image/PathAdapter.cpp Image/PathAdapter.h

        MainWnd.cpp MainWnd.h DepthForgeWin.cpp DepthForgeWin.h
        UI/UI.cpp UI/UI.h UI/Button.cpp UI/MainUI.cpp UI/MainUI.h UI/Forge.cpp UI/Forge.h
        UI/TabCtl.cpp UI/TabCtl.h
        Lense.cpp Lense.h FpsMonitor.cpp FpsMonitor.h
        UI/Slider.cpp UI/Slider.h UI/TestUI.cpp UI/TestUI.h
        genbuttons.h UI/Mode_Path.cpp UI/Mode_Path.h UI/Mode_DepthEdit.cpp UI/Mode_DepthEdit.h UI/Mode.cpp UI/Mode.h)

add_executable(_GenButtons genbuttons.cpp  Threading/Sync.h Threading/Sync.cpp
        PixelGfx/GfxThreadWorker.h PixelGfx/GfxThreadWorker.cpp
        PixelGfx/JWC_PixelGfx.h PixelGfx/JWC_PixelGfx.cpp PixelGfx/GfxBlt.cpp

        Image/Image.cpp Image/Image.h Image/Artif3d.cpp
        Image/DrawImage.cpp Image/TrigCache.cpp Image/TrigCache.h Image/Geometry.cpp Image/Geometry.h
        Image/PathAdapter.cpp Image/PathAdapter.h)

qt5_use_modules(DepthForge Widgets OpenGL)
qt5_use_modules(_GenButtons Widgets OpenGL)

if (UNIX OR LINUX)
target_link_libraries(DepthForge ${QT_LIBRARIES} ${OPENGL_LIBRARIES} pthread)
target_link_libraries(_GenButtons ${QT_LIBRARIES} ${OPENGL_LIBRARIES} pthread)
else()
target_link_libraries(DepthForge ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries(_GenButtons ${QT_LIBRARIES} ${OPENGL_LIBRARIES})

endif ()
