set(pythonfile_list 
	__init__.py;
	engine.py;
	test.py)

foreach(PYFILE ${pythonfile_list})
	#configure_file( "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../${PYFILE}" COPYONLY)
	file( COPY "${CMAKE_SOURCE_DIR}/src/python/${PYFILE}"
     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../"
	 )
	 if (EXISTS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../${PYFILE}")
		message("move files  ${PYFILE}")
		message("${CMAKE_SOURCE_DIR}/src/python/${PYFILE}")
		message("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../${PYFILE}")
	else()
		message(SEND_ERROR "${PYFILE} exestiert nicht in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../")
	endif()
endforeach()