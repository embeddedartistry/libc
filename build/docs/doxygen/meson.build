##################
# Doxygen Module #
##################
# This module provides a Doxygen generation target using a templated configuration
# file contained in this module folder. The project contains Meson configuration
# variables which are populated during the build configuration stage. Default Values
# are provided based on the project skeleton and the configured Meson project info.
#
# Users can override all configuration variables in the "Module Configuration" section below
# by defining overrides prior to invoking this module with subdir().
#
# You can also provide your own Doxyfile in your project repo by overriding the doxyfile_config
# variable. This will disable the configuration step, using your Doxyfile for the conversion step.
# If you choose to go this route, we recommend making your Doxyfile configurable so that you
# can supply meson.build_root() appropriately for the Doxygen output directory.


########################
# Module Configuration #
########################

# Name of the project in the Doxygen output
doxygen_project_name = get_variable('doxygen_project_name', meson.project_name())

# Version number for Doxygen output
doxygen_version = get_variable('doxygen_version', meson.project_version())

# Populates the project brief with a description string
doxygen_description = get_variable('doxygen_description', '')

# Where the generated output should be placed
doxygen_output_dir = get_variable('doxygen_output_dir', meson.build_root() / 'docs')

# Input directories to process
doxygen_input = get_variable('doxygen_input',
	[
		meson.source_root() / 'src',
		meson.source_root() / 'docs',
		meson.source_root() / 'README.md'
	]
)

# This variable can be used to supply additional entries to the Doxygen input
# without overriding default values
doxygen_input_additional = get_variable('doxygen_input_additional', [])

# Process into the proper format: multiple entries are separated by spaces
doxygen_input_parsed = ''
foreach item : doxygen_input + doxygen_input_additional
	doxygen_input_parsed += item + ' '
endforeach

# Patterns and files to exclude from processing
# Doxygen expects multiple entries to be separated by spaces!
doxygen_excludes = get_variable('doxygen_excludes',
	'catch.hpp',
)

# Use a markdown file as the Doxygen main page
doxygen_mainpage_md = get_variable('doxygen_mainpage_md', meson.source_root() / 'README.md')

#################################
# Populate Configuration Values #
#################################

doxyfile_config_data = {
	'PROJECT_NAME': doxygen_project_name,
	'PROJECT_VERSION': doxygen_version,
	'PROJECT_DESCRIPTION': doxygen_description,
	'OUTPUT_DIR': doxygen_output_dir,
	'INPUT_DIRS': doxygen_input_parsed,
	'EXCLUDE_PATTERNS': doxygen_excludes,
	'MD_AS_MAINPAGE': doxygen_mainpage_md
}

doxyfile_config = configuration_data()

foreach var, value : doxyfile_config_data
	doxyfile_config.set(var, value)
endforeach

doxyfile_input = get_variable('doxyfile_input', files('Doxyfile.in'))

doxyfile = get_variable('doxyfile',
	configure_file(input : doxyfile_input,
        output : 'Doxyfile',
        configuration : doxyfile_config_data
    )
)

########################
# Doxygen Build Target #
########################

doxygen = find_program('doxygen', required: false, disabler: true)
run_target('docs', command: [doxygen, doxyfile])
