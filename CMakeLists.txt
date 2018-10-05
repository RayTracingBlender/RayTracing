cmake_minimum_required(VERSION 3.0.2)
project(jpyengine)
#finde Python
find_package( PythonLibs 3.5 REQUIRED )


#Variablen setzen:
#wichtig ist die Python Version 3.5 zu haben wegen Blender
#Außerdem sollte man die Debug libraries mit installieren
if (${PYTHONLIBS_FOUND})
	set(Python_include "${PYTHON_INCLUDE_DIRS}")
	set(Python_libs "${Python_include}/../libs")
else ()
	#falls Python nicht gefunden
	message(FATAL_ERROR "Python 3.5 konnte nicht gefunden werden" )
endif()

#get username
cmake_host_system_information(RESULT temp_username QUERY HOSTNAME)
string(LENGTH "${temp_username}" temp_username_length)
MATH(EXPR temp_username_length "${temp_username_length}-3")
string(SUBSTRING "${temp_username}" 0 ${temp_username_length} username)
message("temp_username ${username}")


#Path zum Blender/scripts/addons (dort speichtert Blender seine Addons)
set(Blender_addons_path "C:/Users/${username}/AppData/Roaming/Blender Foundation/Blender/2.79/scripts/addons")
if (NOT EXISTS ${Blender_addons_path})
	message(FATAL_ERROR "Der Blender Path: &{Blender_addons_path} exestiert nicht")
endif()

set(Addons_name "JPCEngine")


file(MAKE_DIRECTORY "${Blender_addons_path}/JPCEngine/src")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${Blender_addons_path}/JPCEngine/src")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "&{Blender_addons_path}/JPCEngine/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Blender_addons_path}/JPCEngine/src")
add_subdirectory(src)
