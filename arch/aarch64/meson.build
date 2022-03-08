# aarch64 architecture meson build

aarch64_arch_common_dep = declare_dependency(
	include_directories: include_directories('include'),
	sources: files(
		'src/__aeabi_atexit.c',
	)
)

# This crt0.s file is not built to support MacOS M1 builds,
# and we leverage the existing MacOS/startup code for this.
aarch64_non_macos_dep = declare_dependency(
	sources: files(
		'src/crt0.S'
	),
	dependencies: aarch64_arch_common_dep
)

if build_arch == 'aarch64'
	if build_machine.system() == 'darwin'
		build_machine_dep = aarch64_arch_common_dep
	else
		build_machine_dep = aarch64_non_macos_dep
	endif
endif

if host_arch == 'aarch64'
	if host_machine.system() == 'darwin'
		host_machine_dep = aarch64_arch_common_dep
	else
		host_machine_dep = aarch64_non_macos_dep
	endif
endif
