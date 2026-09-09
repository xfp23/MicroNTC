
file(GLOB_RECURSE NTC_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(NTC STATIC
    ${NTC_SOURCES}
)


target_include_directories(NTC PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(NTC PRIVATE
    "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)