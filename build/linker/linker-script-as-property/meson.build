###############################################################
# Generate Linker Arguments and Dependencies for Linker Files #
# Using Cross-compilation file properties					  #
###############################################################

linker_script_flags = []
linker_script_deps = []

foreach entry : meson.get_cross_property('linker_paths', [''])
	if entry != ''
		linker_script_flags += '-L' + meson.source_root() / entry
	endif
endforeach

foreach entry : meson.get_cross_property('linker_scripts', [''])
	if entry != ''
		linker_script_flags += '-T' + entry
	endif
endforeach

foreach entry : meson.get_cross_property('link_depends', [''])
	if entry != ''
		linker_script_deps += meson.source_root() / entry
	endif
endforeach
