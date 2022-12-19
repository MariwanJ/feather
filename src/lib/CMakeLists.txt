add_subdirectory(core)
add_subdirectory(qml)
add_subdirectory(vulture)
add_subdirectory(plugin)


add_definitions( -DFEATHER_PLATFORM_WINDOWS=1 -DFEATHER_BUILD_DLL=1)