cmake_minimum_required(VERSION 3.21)
project(LRUCache)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/91c3669f21cf569f13bd15569b5411e6ca9a8961.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(LRUCache test/tests.cpp include/LRUCache.hpp)
target_link_libraries(LRUCache gtest)
