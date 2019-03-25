# x86_64 architecture meson build

x86_64_arch_dep = declare_dependency(
	include_directories: include_directories('include')
)

if target_architecture == 'x86_64'
	target_arch_deps += [x86_64_arch_dep]
	target_arch_include += include_directories('include')
endif

if native_architecture == 'x86_64'
	native_arch_deps += [x86_64_arch_dep]
	native_arch_include += include_directories('include')
endif
