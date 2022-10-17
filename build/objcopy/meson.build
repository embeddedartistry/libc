##################
# objcopy Module #
##################
#
# This module references an `objcopy` program which should be defined in a
# Meson cross file or native file.
#
# If the property is found, we will call `find_program` on the value of the property.
# If both conditions are fulfilled, we will provide command arrays that can be used
# with `custom_target` calls for converting from ELF/mach-o to hex/bin.
#
# To enable conversion to `.hex` or `.bin`, you need to create a `custom_target`
# with the input ELF/mach-o application, and the output as the converted file name.
# The command string should reference one of these command variables:
#	- host_hex_conversion
#	- host_bin_conversion
#	- native_hex_conversion
# 	- native_bin_conversion
#
# Example target:
# sample_app_hex = custom_target('sample_app.hex',
#	input: sample_app,
#	output: 'sample_app.hex',
#	command: host_hex_conversion,
#	build_by_default: true
# )
#
# You can also use the `native_objcopy` and `host_objcopy` variables in your builds
# for other purposes.
#
# objcopy-dependent targets will be disabled if the property is not defined or the program isn't found.

###
# Read properties from cross/native files
host_objcopy_program = meson.get_external_property('objcopy', '', native: false)
native_objcopy_program = meson.get_external_property('objcopy', '', native: true)

###
# Check if found, and disable if not
if host_objcopy_program == ''
	host_objcopy = disabler()
else
	host_objcopy = find_program(host_objcopy_program,
		required: false, disabler: true)
endif

if native_objcopy_program == ''
	native_objcopy = disabler()
else
	native_objcopy = find_program(native_objcopy_program,
		required: false, disabler: true)
endif

if host_objcopy.found() == false
	message('Host objcopy program not available, .hex and .bin conversion targets will be disabled.')
endif

if native_objcopy.found() == false
	message('Native objcopy program not available, .hex and .bin conversion targets will be disabled.')
endif

###
# Command variables for conversion targets
host_hex_conversion = [host_objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@']
host_bin_conversion = [host_objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@']
native_hex_conversion = [host_objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@']
native_bin_conversion = [host_objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@']
