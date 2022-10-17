############################
# Release Packaging Module #
############################
#
# This module provides targets for creating host and native packages using
# customizable built-in machinery. The underlying script uses `tar`, which is
# a requirement for this module.
#
# In order for these targets to be available, you must define either or both of
# the following variables, which are lists of files or strings:
#	- host_pkg_files
#	- native_pkg_files
#
# You can specify any number of directories and files to include in the archive.
# 	Files can be separate elements: ['docs', 'include', 'buildresults/lib/libc.a']
#   They can also be ground together using commas in a single element:
#		['docs,include,buildresults/lib/libc.a']
# 	If you wish to change directories before adding files to the archive, add the directory
#   name (relative to the source root), followed by a colon, followed by a comma-separated list of files
#   to add from that directory:
#		['include,arch/x86_64/include', 'buildresults:docs', 'buildresults/lib:libc.a']
#
# By default, the base name for the package will use the project's name, with `_native` appended
# to native-only packages. You can override this default by defining variables named `host_pkg_name`
# and `native_pkg_name`.
#
# By default, the packages will be named according to the cpu_family(), cpu(), system(), and
# meson.project_version() values defined by the build system. You can override these values by
# specifying your own package info arrays named `host_pkg_info_array` and `native_pkg_info-array`.
#
# These arrays may include any of the following arugments:
#	 [
#		'-a', 'architecture string',
#		'-c', 'cpu string',
#		'-s', 'system string',
#		'-v', 'version string',
# 	]
#
# The naming format is PROJECTNAME_VERSION_ARCH_CPU_SYS.tgz. You can hijack any of these values
# for your purposes. You may also leave off values you don't wish to include.
#
# All variables to control the behavior of this module must be defined before including it.

#################
# Configuration #
#################

host_pkg_info_array_default = [
	'-a', host_machine.cpu_family(),
	'-c', host_machine.cpu(),
	'-s', host_machine.system(),
	'-v', meson.project_version(),
]

native_pkg_info_array_default = [
	'-a', build_machine.cpu_family(),
	'-c', build_machine.cpu(),
	'-s', build_machine.system(),
	'-v', meson.project_version(),
]

host_pkg_name_default = meson.project_name()
native_pkg_name_default = meson.project_name() + '_native'

host_pkg_name = get_variable('host_pkg_name', host_pkg_name_default)
native_pkg_name = get_variable('native_pkg_name', native_pkg_name_default)
host_pkg_info_array = get_variable('host_pkg_info_array', host_pkg_info_array_default)
native_pkg_info_array = get_variable('native_pkg_info_array', native_pkg_info_array_default)

#####################
# Packaging Targets #
#####################

# If you want to implement a custom packaging target, you can reference
# This files object to gain access to the script
packaging_script = files('package.sh')

# You cannot run the packaging script if tar isn't installed on your system
if find_program('tar', required: false).found()
	if get_variable('host_pkg_files', []).length() == 0
		info('No host_pkg_files variable defined: disabling package target.')
	else
		run_target('package',
			command: [
				packaging_script,
				# Options
				host_pkg_info_array,
				# Project Name
				host_pkg_name,
				# Files to Package
				host_pkg_files
			]
		)
	endif

	if get_variable('native_pkg_files', []).length() == 0
		info('No host_pkg_files variable defined: disabling package target.')
	else
		run_target('package-native',
			command: [
				packaging_script,
				# Options
				native_pkg_info_array,
				# Project Name
				native_pkg_name,
				# Files to Package
				native_pkg_files
			]
		)
	endif
endif
