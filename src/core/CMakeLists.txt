set(INC 
${Python_include}
${CMAKE_SOURCE_DIR}/pybind11/include)
if (EXISTS "${Python_include}/../Lib/site-packages/numpy/core/include/numpy")
	set(INC 
	${INC}
	"${Python_include}/../Lib/site-packages/numpy/core/include/numpy")
else()
	message(FATAL_ERROR "Numpy konnte nicht gefunden werden \n Path: ${Python_include}/../Lib/site-packages/numpy/core/include/numpy")
endif()
message(status " Python_include: ${Python_include}")

include_directories(${INC})
link_directories(${Python_libs})
set(Library_files 
	#include.h 
	#main.cpp)
	test.cpp)

add_library(_JPCEngine SHARED ${Library_files})
set_target_properties(_JPCEngine PROPERTIES SUFFIX ".pyd")