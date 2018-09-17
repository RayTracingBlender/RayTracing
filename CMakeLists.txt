cmake_minimum_required(VERSION 3.0.2)
project(jpyengine)
#Variablen setzen:
set(Python_include "C:/Users/Chris/AppData/Local/Programs/Python/Python35/include")
set(Python_libs "C:/Users/Chris/AppData/Local/Programs/Python/Python35/libs")
set(Blender_addons_path "H:/dev/Renderengine2/Programmieren/Cmake_test/addons")
set(Addons_name "JPCEngine")


file(MAKE_DIRECTORY "&{Blender_addons_path}/JPCEngine/src")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "&{Blender_addons_path}/JPCEngine/src")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "&{Blender_addons_path}/JPCEngine/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Blender_addons_path}/JPCEngine/src")
add_subdirectory(src)