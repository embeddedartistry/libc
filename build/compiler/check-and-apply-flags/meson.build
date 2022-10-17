##############################################################
# Modular Fucntion to Check and Apply Compiler Flags in Bulk #
##############################################################

# To use this function, define a variable called compile_settings_list and/or link_settings_list.
# These variables are used to iterate over each compiler/flag/native setting to reduce duplication.
# Populate these variable before including this module.
#
# Common flags that apply to all configuratons are specified in varibles called:
#	- desired_common_compile_flags
#	- desired_common_link_flags
#
# Each element should be a dict, with the following fields:
#	'lang': programming language (string)
#	'compiler': compiler object to supply for has_argument() calls
#	'flags': a list of flags that you want to test and apply to the project
#	'isnative': true if native, false otherwise
#
## Here is an example list that applies flags to C and C++ for native true/false
#
#compile_settings_list = [
#	{'lang': 'c', 'compiler': host_c_compiler, 'flags': desired_c_compile_flags, 'isnative': false},
#	{'lang': 'c', 'compiler': native_c_compiler, 'flags': desired_native_c_compile_flags, 'isnative': true},
#	{'lang': 'cpp', 'compiler': host_cpp_compiler, 'flags': desired_cpp_compile_flags, 'isnative': false},
#	{'lang': 'cpp', 'compiler': native_cpp_compiler, 'flags': desired_native_cpp_compile_flags, 'isnative': true},
#]
#
# Sometimes linker checks provide false failures due to missing symbols at link time.
# To provide additional flags for linker checks, populate an optional property in your cross file:
#	get_supported_link_arg_flags
#
# The same structure is used for both compile_settings_list and link_settings_list


if get_variable('compile_settings_list', []).length() == 0
	warning('Expected variable compile_settings_list not defined. Not processing compiler arguments.')
else
	# Process each compiler configuration
	foreach entry : compile_settings_list
		add_project_arguments(entry.get('compiler').get_supported_arguments(
				entry.get('flags') + desired_common_compile_flags),
			language: entry.get('lang'), native: entry.get('isnative'))
	endforeach
endif

if get_variable('link_settings_list', []).length() == 0
	warning('Expected variable link_settings_list not defined. Not processing linker arguments.')
else
	# Process each linker configuration
	foreach entry : link_settings_list
		supporting_link_flags = meson.get_external_property('get_supported_link_arg_flags', [],
			native: entry.get('isnative'))

		foreach flag : entry.get('flags') + desired_common_link_flags
			if entry.get('compiler').has_multi_link_arguments(flag, supporting_link_flags)
				add_project_link_arguments(flag,
					language: entry.get('lang'), native: entry.get('isnative'))
			endif
		endforeach
	endforeach
endif
