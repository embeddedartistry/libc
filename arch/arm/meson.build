# ARM architecture meson build

arm_arch_dep = declare_dependency(
	include_directories: include_directories('include'),
	sources: files(
		'src/__aeabi_atexit.c',
		'src/crt0.S',
	)
)

if build_arch == 'arm'
	build_machine_dep = arm_arch_dep
endif

if host_arch == 'arm'
	host_machine_dep = arm_arch_dep
endif
