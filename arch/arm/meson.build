# ARM architecture meson build

libruntime_arm = static_library('runtime_arm',
    sources: files(
		'src/crt0.S',
		'src/__aeabi_atexit.c',
	),
	include_directories: [include_directories('include')]
)

arm_arch_dep = declare_dependency(
	include_directories: include_directories('include'),
	link_with: libruntime_arm,
)

if target_architecture == 'arm'
	target_arch_deps += [arm_arch_dep]
	target_arch_include += include_directories('include')
endif

if native_architecture == 'arm'
	native_arch_deps += [arm_arch_dep]
	native_arch_include += include_directories('include')
endif
