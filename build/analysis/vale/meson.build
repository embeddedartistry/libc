################################
# Vale Document Linting Module #
################################
# This module adds a vale document linting target to your build system.
#
# All variables used below can be overridden by the user. Simply define the variables
# with your own values before invoking this module.

vale_default_files = [
	meson.source_root() + '/docs/',
	meson.source_root() + '/README.md'
]

# Override this variable to control what files and folders vale will analyze
vale_files = get_variable('vale_files', vale_default_files)

# Add additional files without redefining the defaults
vale_additional_files = get_variable('vale_files', [])

# Control the file types that vale will analyze. Separated by comma.
vale_file_types = get_variable('vale_file_types', 'md,rst,txt')

# Supply a style file, which will use this file instead of the default .vale.ini
vale_config_file = get_variable('vale_config_file',
	files('vale-styleguide/config/documentation.vale.ini'))

vale_default_args = [
	# Files to include in analysis
	'--glob', '*.{' + vale_file_types + '}'
]

if vale_config_file.length() > 0
	vale_default_args += ['--config', vale_config_file]
endif

# Control the arguments passed to vale.
vale_args = get_variable('vale_args', vale_default_args)
# Add additional arguments without overriding the defaults
vale_additional_args = get_variable('vale_additional_args', [])

vale = find_program('vale', required: false, disabler: true)

run_target('vale',
	command: [
		vale,
		vale_args,
		vale_additional_args,
		vale_files,
		vale_additional_files
	]
)
