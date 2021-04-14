link_libraries(
        coll
)

aux_source_directory(. TEST_SRC)

add_executable(tests ${TEST_SRC})