####################################################
# Common C++ Language Compiler Settings and Values #
####################################################

native_cpp_compiler = meson.get_compiler('cpp', native: true)
host_cpp_compiler = meson.get_compiler('cpp', native: false)

native_cpp_compiler_id = native_cpp_compiler.get_id()
host_cpp_compiler_id = host_cpp_compiler.get_id()

desired_cpp_common_warning_flags = [
	'-Wold-style-cast',
	'-Wnon-virtual-dtor',
	'-Wctor-dtor-privacy',
	'-Woverloaded-virtual',
	'-Wnoexcept',
	'-Wstrict-null-sentinel',
	'-Wuseless-cast',
	'-Wzero-as-null-pointer-constant',
	'-Wextra-semi',
]

# Use these variables to control whether you're setting flags for native: true/false
desired_cpp_compile_flags = []
if meson.is_subproject() == false
desired_cpp_compile_flags += desired_cpp_common_warning_flags
endif
desired_native_cpp_compile_flags = desired_cpp_compile_flags
