cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0110 NEW)
project(DTS_TESTS)

if(MSVC)
    add_compile_options(/DDTS_DEBUG_CHECKS /W4)
elseif(WIN32)
    add_compile_options(-DDTS_DEBUG_CHECKS -Wall -Wextra -pedantic -Wno-pedantic-ms-format)
else()
    add_compile_options(-DDTS_DEBUG_CHECKS -Wall -Wextra -pedantic)
endif()

set(TEST_EXECS test_alignof1 test_alignof2 test_array1 test_array2 test_listnode_sizeof test_struct_sizeof)

add_executable(array examples/array/array.c)
add_executable(dynarray examples/dynarray/dynarray.c)
add_executable(list examples/list/list.c)

enable_testing()

file(GLOB tests "tests/*.c")
foreach(testpath ${tests})
    get_filename_component(testname_we ${testpath} NAME_WE)
    add_executable(${testname_we} ${testpath})
endforeach()

add_test("Alignof int" test_alignof1)
add_test("Alignof struct" test_alignof2)
add_test("Array Heap" test_array1)
add_test("Array Alias" test_array2)
add_test("Manual sizeof listnode" test_listnode_sizeof)
add_test("Manual sizeof struct" test_struct_sizeof)

set_property(TARGET ${TEST_EXECS} array dynarray list PROPERTY C_STANDARD 99)