
find_package(OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories("include/")

file(GLOB_RECURSE opencv_test_src include/*.h src/*.cpp)

add_executable(opencv_test ${opencv_test_src})
target_link_libraries(opencv_test PUBLIC core ${OpenCV_LIBS})
                              
set_target_properties (opencv_test PROPERTIES FOLDER Main)