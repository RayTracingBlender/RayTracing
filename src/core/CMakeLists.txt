include_directories(${Python_include})
link_directories(${Python_libs})
set(Library_files 
	include.h 
	main.cpp)

add_library(_JPCEngine SHARED ${Library_files})
set_target_properties(_JPCEngine PROPERTIES SUFFIX ".pyd")