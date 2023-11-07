# aarch64 architecture meson build

aarch64_arch_common_dep = declare_dependency(
	include_directories: include_directories('include'),
	sources: files(
		'src/__aeabi_atexit.c',
	)
)

# This crt0.s file is not currently building for aarch64.
# At this time, we are leveraging existing startup code.
aarch64_crt0_dep = declare_dependency(
	sources: files(
		'src/crt0.S'
	),
	dependencies: aarch64_arch_common_dep
)

if build_arch == 'aarch64'
	build_machine_dep = aarch64_arch_common_dep
endif

if host_arch == 'aarch64'
	host_machine_dep = aarch64_arch_common_dep
endif

# The previous version was:
#if build_machine.system() == 'darwin'
#	build_machine_dep = aarch64_arch_common_dep
#else
#	build_machine_dep = aarch64_non_macos_dep
#endif
