cmake_minimum_required(VERSION 3.14)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(LINUX_DISTR_NAME "unknown" CACHE INTERNAL "Distro name")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" OFF)
option(WITH_GTEST "Whether to build Google Test" ON)

configure_file(version.h.in version.h)

add_executable(ip_filter main.cpp
    ipv4address.h ipv4address.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if(WITH_GTEST)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.17.0
    )

    FetchContent_MakeAvailable(googletest)
endif()

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_boost test_boost.cpp ipv4address.cpp)

    set_target_properties(test_boost PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_boost
        ${Boost_LIBRARIES}
    )

    enable_testing()
    add_test(NAME test_boost COMMAND test_boost)
endif()

if(WITH_GTEST)
    add_executable(test_gtest test_gtest.cpp ipv4address.cpp)

    set_target_properties(test_gtest PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_gtest
        gtest_main
    )

    enable_testing()
    add_test(NAME test_gtest COMMAND test_gtest)
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_PACKAGE_FILE_NAME "ip_filter-0.0.${PATCH_VERSION}-${LINUX_DISTR_NAME}")

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
