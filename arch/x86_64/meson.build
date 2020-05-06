# x86_64 architecture meson build

x86_64_arch_dep = declare_dependency(
	include_directories: include_directories('include'),
)

if build_arch == 'x86_64'
	build_machine_dep = x86_64_arch_dep
endif

if host_arch == 'x86_64'
	host_machine_dep = x86_64_arch_dep
endif
