add_library(architecture_specific INTERFACE)
target_include_directories(architecture_specific INTERFACE include/)
target_sources(architecture_specific INTERFACE src/__aeabi_atexit.c src/crt0.S)
install(DIRECTORY include/ DESTINATION include)
