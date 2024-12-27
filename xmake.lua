add_rules("mode.debug")
set_languages("c++23")
set_policy("build.ccache", false)

target("cclox")
	set_policy("build.c++.modules", true)
	set_kind("binary")
	add_files("src/*.mpp", { install = true })
	add_files("src/*.cpp")
	add_cxxflags("-ftime-trace")