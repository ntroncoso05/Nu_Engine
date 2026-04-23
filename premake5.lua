workspace "Nu"
	architecture "x64"
	targetdir "build"
	
	configurations 
	{ 
		"Debug", 
        "Release",
        "Dist"
    }
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Nu/vendor/GLFW/include"
IncludeDir["Glad"] = "Nu/vendor/Glad/include"
IncludeDir["ImGui"] = "Nu/vendor/ImGui"
IncludeDir["glm"] = "Nu/vendor/glm"

include "Nu/vendor/GLFW"
include "Nu/vendor/Glad"
include "Nu/vendor/ImGui"

project "Nu"
    location "Nu"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "nupch.h"
    pchsource "Nu/src/nupch.cpp"

	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp"  
    }

    includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}"
    }
    
    links 
	{ 
		"GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }
    
	filter "system:windows"
        systemversion "latest"
        
		defines 
		{ 
            "NM_PLATFORM_WINDOWS",
            "NM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
		}
					
    filter "configurations:Debug"
        defines "NM_DEBUG"
        symbols "on"
                
    filter "configurations:Release"
        defines "NM_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "NM_DIST"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{ 
		"Nu"
    }
    
	files 
	{ 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.c", 
		"%{prj.name}/src/**.hpp", 
		"%{prj.name}/src/**.cpp"  
	}
    
	includedirs 
	{
        "%{prj.name}/src",
        "Nu/src",
        "Nu/vendor",
        "%{IncludeDir.glm}"
    }
	
	filter "system:windows"
        systemversion "latest"

		defines 
		{ 
            "NM_PLATFORM_WINDOWS"
		}
    
    filter "configurations:Debug"
        defines "NM_DEBUG"
        symbols "on"
                
    filter "configurations:Release"
        defines "NM_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "NM_DIST"
        optimize "on"