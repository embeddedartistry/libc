##############################################
# Format Strings to Use for Linker Map Files #
##############################################

# This format string template can be used to declare a map file
# with an executable when using GCC, Clang, or MSVC
# Use it like:
#	link_args: map_file.format(meson.current_build_dir() + '/libc_test')

if native_c_compiler.has_link_argument('-Wl,-map,test.map')
	native_map_file = '-Wl,-map,@0@.map'
elif native_c_compiler.has_link_argument('-Wl,-Map,test.map')
	native_map_file = '-Wl,-Map,@0@.map'
elif native_c_compiler_id == 'msvc'
	native_map_file = '/MAP:@0@.map'
else
	warning('Native toolchain does not support Map file generation')
	native_map_file = []
endif

if host_c_compiler.has_link_argument('-Wl,-Map,test.map')
	host_map_file = '-Wl,-Map,@0@.map'
elif host_c_compiler.has_link_argument('-Wl,-map,test.map')
	host_map_file = '-Wl,-map,@0@.map'
elif host_c_compiler.has_multi_link_arguments('--specs=nosys.specs', '-Wl,-Map,test.map')
	# ARM will fail the check without --specs=nosys.specs
	host_map_file = '-Wl,-Map,@0@.map'
elif host_c_compiler_id == 'msvc'
	host_map_file = '/MAP:@0@.map'
else
	warning('Host toolchain does not support Map file generation')
	host_map_file = []
endif

# The map_file variable is a simplified alias to host_map_file
map_file = host_map_file
