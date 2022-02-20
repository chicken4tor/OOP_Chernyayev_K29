cmake_minimum_required(VERSION 3.0.0)
project(lab1a VERSION 0.1.0)

include(CTest)
enable_testing()

include(CTest)
enable_testing()

find_package(Doxygen REQUIRED dot)

# find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_library(uttt uttt.cpp)

add_executable(lab1a main.cpp uttt)

# target_link_libraries(tut1 PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

if(DOXYGEN_FOUND)

    # set(DOXYGEN_GENERATE_HTML NO)
    # set(DOXYGEN_GENERATE_MAN YES)
    set(DOXYGEN_EXCLUDE_PATTERNS "build")

    doxygen_add_docs(
        doxygen
        ${PROJECT_SOURCE_DIR}
        COMMENT "Generate man pages"
    )
else(DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)

add_executable(
  lab1a_test
  uttt_test.cpp
  uttt
)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(lab1a_test PRIVATE GTest::gtest_main)

add_test(AllTestsInLab1a lab1a_test)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
