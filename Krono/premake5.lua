project "Krono"
	kind "None"
	language "C++"
	cppdialect "C++20"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (outputdir .. "/%{prj.name}/intermediates")

	includedirs {
		"include"
	}

	files {
		"include/**.hpp"
	}