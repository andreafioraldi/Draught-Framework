add_custom_command(OUTPUT "${EXECUTABLE_OUTPUT_PATH}/Map.dubbel" DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Map.stout" COMMAND "${EXECUTABLE_OUTPUT_PATH}/stoutc" "${CMAKE_CURRENT_SOURCE_DIR}/Map.stout" -o "${EXECUTABLE_OUTPUT_PATH}/Map.dubbel")

add_custom_target(Map_dubbel ALL DEPENDS "${EXECUTABLE_OUTPUT_PATH}/Map.dubbel")

add_dependencies(Map_dubbel stoutc)

install(FILES ${EXECUTABLE_OUTPUT_PATH}/Map.dubbel DESTINATION lib)
