# aarch64 architecture meson build

arm64_arch_dep = declare_dependency(
	include_directories: include_directories('include')
)

if target_architecture == 'aarch64'
	target_arch_deps += [arm64_arch_dep]
	target_arch_include += include_directories('include')
endif

if native_architecture == 'aarch64'
	native_arch_deps += [arm64_arch_dep]
	native_arch_include += include_directories('include')
endif
