set(pythonfile_list 
	__init__.py;
	engine.py)

foreach(PYFILE ${pythonfile_list})
	#configure_file( "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../${PYFILE}" COPYONLY)
	file( COPY "${CMAKE_SOURCE_DIR}/src/python/${PYFILE}"
     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../"
	 )
	message("move files  ${PYFILE}")
	message("${CMAKE_SOURCE_DIR}/src/python/${PYFILE}")
	message("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../${PYFILE}")
endforeach()