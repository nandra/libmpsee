cmake_minimum_required(VERSION 3.0)
project (libmpsse_examples)

# bitbang example
add_executable(mpsse_bitbang bitbang.c)
target_link_libraries(mpsse_bitbang libmpsse ${FTDI_LIBRARY})
target_include_directories(mpsse_bitbang PUBLIC ${CMAKE_SOURCE_DIR})

# ds1305 example
add_executable(mpsse_ds1305 ds1305.c)
target_link_libraries(mpsse_ds1305 libmpsse ${FTDI_LIBRARY})
target_include_directories(mpsse_ds1305 PUBLIC ${CMAKE_SOURCE_DIR})

# gpio example
add_executable(mpsse_gpio gpio.c)
target_link_libraries(mpsse_gpio libmpsse ${FTDI_LIBRARY})
target_include_directories(mpsse_gpio PUBLIC ${CMAKE_SOURCE_DIR})

# i2ceeprom example
add_executable(mpsse_i2ceeprom i2ceeprom.c)
target_link_libraries(mpsse_i2ceeprom libmpsse ${FTDI_LIBRARY})
target_include_directories(mpsse_i2ceeprom PUBLIC ${CMAKE_SOURCE_DIR})

# spiflash example
add_executable(mpsse_spiflash spiflash.c)
target_link_libraries(mpsse_spiflash libmpsse ${FTDI_LIBRARY})
target_include_directories(mpsse_spiflash PUBLIC ${CMAKE_SOURCE_DIR})

# spiflash_fast example
add_executable(mpsse_spiflash_fast spiflashfast.c)
target_link_libraries(mpsse_spiflash_fast libmpsse ${FTDI_LIBRARY})
target_include_directories(mpsse_spiflash_fast PUBLIC ${CMAKE_SOURCE_DIR})