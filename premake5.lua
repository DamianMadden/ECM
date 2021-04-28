workspace "ECM"
	configurations { "Debug", "Release" }
	startproject "WowmaniaECM"
	
project "WowmaniaECM"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	flags { "FatalWarnings", "MultiProcessorCompile" }

	files { "src/*.cpp", "src/*.h" }
	
	files { "3rdParty/SDL2-2.0.14/include/*.cpp", "3rdParty/SDL2-2.0.14/include/*.h" }
	includedirs { "3rdParty/SDL2-2.0.14/include" }
	libdirs { "3rdParty/SDL2-2.0.14/lib/x86" }
	links { "SDL2", "SDL2main" }

	defines { "IMGUI_DISABLE_OBSOLETE_FUNCTIONS" }
	files { "3rdParty/imgui/*.cpp", "3rdParty/imgui/*.h" }
	includedirs { "3rdParty/imgui" }
	
	files { "3rdParty/Blackbone/src/Blackbone**.cpp", "3rdParty/Blackbone/src/Blackbone**.h" }
	includedirs { "3rdParty/Blackbone/src/Blackbone/**" }
	libdirs { "3rdParty/Blackbone/build/x64/**" }


	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		omitframepointer "On"
		optimize "Full"
	
	libdirs { "$(DXSDK_DIR)/Lib/x64;" }
	links { "d3d11.lib", "d3dcompiler.lib", "dxgi.lib", "dxguid.lib" }

	filter { "files:3rdParty/**" }
		warnings "Off"

	targetdir "builds"
	debugdir "builds"

project "WowmaniaECMTests"
	kind "ConsoleApp"
	language "C++"
	files {"test/*.cpp" }
	
	files { "3rdParty/googletest/**.h", "3rdParty/googletest/**.hpp", "3rdParty/googletest/src/gtest-all.cc" }
	includedirs { "3rdParty/googletest/include", "3rdParty/googletest" }