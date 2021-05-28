workspace "ECM"
	startproject "WowmaniaECM"
	configurations { "Debug", "Release" }
	platforms { "Win64" }

	--[[
	filter { "platforms:Win32" }
		system "Windows"
		architecture "x86"
		libdirs { "3rdParty/SDL2-2.0.14/lib/x86" }
		libdirs { "$(DXSDK_DIR)/Lib/x86" }
	]]
	
	filter { "platforms:Win64" }
		system "Windows"
		architecture "x86_64"
		libdirs { "3rdParty/SDL2-2.0.14/lib/x64" }
		libdirs { "$(DXSDK_DIR)/Lib/x64" }
	
project "ECM"
	targetdir "bin"
	debugdir "bin"
	
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	flags { "FatalWarnings", "MultiProcessorCompile" }

	files { "src/*.cpp", "src/*.h" }
	
	files { "3rdParty/SDL2-2.0.14/include/*.cpp", "3rdParty/SDL2-2.0.14/include/*.h" }
	includedirs { "3rdParty/SDL2-2.0.14/include" }
	links { "SDL2", "SDL2main" }
			
	defines { "IMGUI_DISABLE_OBSOLETE_FUNCTIONS" }
	files { "3rdParty/imgui/*.cpp", "3rdParty/imgui/*.h" }
	includedirs { "3rdParty/imgui" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		omitframepointer "On"
		optimize "Full"
		
	links { "d3d11.lib", "d3dcompiler.lib", "dxgi.lib", "dxguid.lib" }

	filter { "files:3rdParty/**" }
		warnings "Off"

os.execute("mkdir bin")
os.copyfile("3rdParty/SDL2-2.0.14/lib/x64/SDL2.dll", "bin/SDL2.dll")
	