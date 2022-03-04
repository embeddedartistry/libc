add_library(architecture_specific INTERFACE)
target_include_directories(architecture_specific INTERFACE include/)
install(DIRECTORY include/ DESTINATION include)
