cmake_minimum_required(VERSION 3.0.2)
project(jpyengine)
#Variablen setzen:
#wichtig ist die Python Version 3.5 zu haben wegen Blender
#Außerdem sollte man die Debug libraries mit installieren
set(Python_include "C:/Users/Chris/AppData/Local/Programs/Python/Python35/include")
set(Python_libs "C:/Users/Chris/AppData/Local/Programs/Python/Python35/libs")
#Path zum Blender/scripts/addons (dort speichtert Blender seine Addons)
set(Blender_addons_path "F:/blender versionwn/blender-2.79-rc1-windows64/2.79/scripts/addons")
set(Addons_name "JPCEngine")


file(MAKE_DIRECTORY "&{Blender_addons_path}/JPCEngine/src")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "&{Blender_addons_path}/JPCEngine/src")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "&{Blender_addons_path}/JPCEngine/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Blender_addons_path}/JPCEngine/src")
add_subdirectory(src)
