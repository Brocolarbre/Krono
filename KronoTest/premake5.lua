project "KronoTest"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (outputdir .. "/%{prj.name}/intermediates")

	includedirs {
		"%{wks.location}/Krono/include"
	}

	files {
		"src/**.hpp",
		"src/**.cpp"
	}