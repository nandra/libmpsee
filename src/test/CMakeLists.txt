include_directories(${CMAKE_SOURCE_DIR})

#add_mocked_test(program SOURCES ${CMAKE_SOURCE_DIR}/src/module.c MOCKS printf)
add_mocked_test(support SOURCES ${CMAKE_SOURCE_DIR}/support.c LINK_LIBRARIES ${FTDI_LIBRARY})
