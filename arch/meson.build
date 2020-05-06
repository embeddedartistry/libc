# Architecture-specific Build Support

build_arch = build_machine.cpu_family()
host_arch = host_machine.cpu_family()

build_machine_arch_sys_include = include_directories(build_arch + '/include',
	is_system: true)
host_machine_arch_sys_include = include_directories(host_arch + '/include',
	is_system: true)

#########################################
# Add Architecture-specific Build Files #
#########################################

subdir(build_arch)

if(build_arch != host_arch)
	subdir(host_arch)
endif
