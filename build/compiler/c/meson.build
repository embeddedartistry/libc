##################################################
# Common C Language Compiler Settings and Values #
##################################################

native_c_compiler = meson.get_compiler('c', native: true)
host_c_compiler = meson.get_compiler('c', native: false)

native_c_compiler_id = native_c_compiler.get_id()
host_c_compiler_id = host_c_compiler.get_id()

# Use these variables to control whether you're setting flags for native: true/false
desired_c_compile_flags = []
desired_native_c_compile_flags = []
