##################################################
# Common Non-language Specific Compiler Settings #
##################################################

# NOTE:
#	For language-specific values, use subdir('build/compiler/<lang>') in your top-level build file

desired_common_warning_flags = [
	# Disabled Warnings
	'-Wno-unknown-pragmas', # Some compilers complain about our use of #pragma mark
	'-Wno-c++98-compat',
	'-Wno-c++98-compat-pedantic',
	'-Wno-padded',
	'-Wno-exit-time-destructors', # causes warnings if you use static values
	'-Wno-global-constructors', # causes warnings if you use static values
	'-Wno-covered-switch-default',
	# Desired Warnings
	'-Wfloat-equal',
	'-Wconversion',
	'-Wlogical-op',
	'-Wundef',
	'-Wredundant-decls',
	'-Wshadow',
	'-Wstrict-overflow=2',
	'-Wwrite-strings',
	'-Wpointer-arith',
	'-Wcast-qual',
	'-Wformat=2',
	'-Wformat-truncation',
	'-Wmissing-include-dirs',
	'-Wcast-align',
	'-Wswitch-enum',
	'-Wsign-conversion',
	'-Wdisabled-optimization',
	# '-Winline', # Now disabled because it is mostly warning us about default constructors and destructors
	'-Winvalid-pch',
	'-Wmissing-declarations',
	'-Wdouble-promotion',
	'-Wshadow',
	'-Wtrampolines',
	'-Wvector-operation-performance',
	'-Wshift-overflow=2',
	'-Wnull-dereference',
	'-Wduplicated-cond',
	'-Wshift-overflow=2',
	'-Wnull-dereference',
	'-Wduplicated-cond',
	'-Wcast-align=strict',
]

# These variables should be set for all combinations of compilers and native: true/false
desired_common_compile_flags = [
	# Diagnostics
	'-fdiagnostics-show-option',
	'-fcolor-diagnostics',
	# Compiler Optimization Flags
	'-ffunction-sections', # Place each function in its own section (ELF Only)
	'-fdata-sections', # Place each data in its own section (ELF Only)
	'-fdevirtualize', # Attempt to convert calls to virtual functions to direct calls
]

if meson.is_subproject() == false
	desired_common_compile_flags += desired_common_warning_flags
endif


desired_common_link_flags = [
	# Optimization Flags
	'-Wl,-dead_strip', # Strip dead symbols for OS X
	'-Wl,--gc-sections',
]
