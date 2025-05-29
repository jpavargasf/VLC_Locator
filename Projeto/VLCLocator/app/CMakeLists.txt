cmake_minimum_required(VERSION 3.4.1)

add_library( # Define the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/native-lib.cpp)

find_library( # Sets the path to the log library.
        log-lib
        log )

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library.
        ${log-lib} )
