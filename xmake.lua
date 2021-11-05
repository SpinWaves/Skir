add_requires("libsdl_image", "libsdl", "libsdl_ttf", "libsndfile", "openal-soft")

add_rules("mode.debug", "mode.release")
set_languages("c11")

set_objectdir("build-int/$(os)_$(arch)")
set_targetdir("build/$(os)_$(arch)")

target("Keep_Running")
	set_kind("binary")
	add_files("src/**.c")
	add_includedirs("src")

	if is_mode("debug") then
		add_defines("DEBUG")
	elseif is_mode("release") then
		add_defines("RELEASE")
	end

	add_defines("LOG_DIR=\"$(projectdir)/logs\"")
	add_defines("MAIN_DIR=\"$(projectdir)/\"")

	add_defines("SDL_MAIN_HANDLED")
	add_packages("libsdl_image", "libsdl", "libsdl_ttf", "libsndfile", "openal-soft")
target_end() -- optional but I think the code is cleaner with this
