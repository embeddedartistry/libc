# aarch64 architecture meson build

aarch64_arch_dep = declare_dependency(
	include_directories: include_directories('include'),
	sources: files(
		'src/__aeabi_atexit.c',
		'src/crt0.S',
	)
)

if build_arch == 'aarch64'
	build_machine_dep = aarch64_arch_dep
endif

if host_arch == 'aarch64'
	host_machine_dep = aarch64_arch_dep
endif
