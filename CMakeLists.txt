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

add_executable(DepthForge main.cpp  Threading/Sync.h Threading/Sync.cpp
                                    PixelGfx/GfxThreadWorker.h PixelGfx/GfxThreadWorker.cpp PixelGfx/JWC_PixelGfx.h PixelGfx/JWC_PixelGfx.cpp
        PixelGfx/GfxBlt.cpp DepthForgeWin.cpp DepthForgeWin.h UI/UI.cpp UI/UI.h Image/Image.cpp Image/Image.h MainWnd.cpp MainWnd.h Image/Artif3d.cpp Image/DrawImage.cpp UI/Button.cpp UI/MainUI.cpp UI/MainUI.h UI/Forge.cpp UI/Forge.h Lense.cpp Lense.h UI/Slider.cpp UI/Slider.h UI/TestUI.cpp UI/TestUI.h FpsMonitor.cpp FpsMonitor.h Image/TrigCache.cpp Image/TrigCache.h Image/Geometry.cpp Image/Geometry.h Image/PathAdapter.cpp Image/PathAdapter.h UI/TabCtl.cpp UI/TabCtl.h version.h)

qt5_use_modules(DepthForge Widgets OpenGL)

if (UNIX OR LINUX)
target_link_libraries(DepthForge ${QT_LIBRARIES} ${OPENGL_LIBRARIES} pthread)
else()
target_link_libraries(DepthForge ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
endif ()
