set(pythonfile_list 
	Triangle.py)
file(MAKE_DIRECTORY "${Blender_addons_path}/JPCEngine/Shapes")

foreach(PYFILE ${pythonfile_list})
	#configure_file( "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../${PYFILE}" COPYONLY)
	file( COPY "${CMAKE_SOURCE_DIR}/src/python/Shapes/${PYFILE}"
     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Shapes"
	 )
	 if (EXISTS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Shapes/${PYFILE}")
		message("move files  ${PYFILE}")
		message("${CMAKE_SOURCE_DIR}/src/python/Shapes/${PYFILE}")
		message("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Shapes/${PYFILE}")
	else()
		message(SEND_ERROR "${PYFILE} exestiert nicht in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Shapes")
	endif()
endforeach()