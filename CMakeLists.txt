cmake_minimum_required(VERSION 3.22)
project(04_homework)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

configure_file(src/version.h.in src/version.h)

project(sfinae VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

if (MSVC)
    target_compile_options(sfinae PRIVATE
            /W4
    )
else ()
    target_compile_options(sfinae PRIVATE
            -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS sfinae RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT rudik.login@gmail.com)
include(CPack)