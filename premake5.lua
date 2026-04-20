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

include "Nu/vendor/GLFW"

project "Nu"
    location "Nu"
    kind "SharedLib"
    language "C++"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

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
        "%{IncludeDir.GLFW}"
    }
    
    links 
	{ 
		"GLFW",
        "opengl32.lib",
        "dwmapi.lib"
    }
    
	filter "system:windows"
		cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
		defines 
		{ 
            "NM_PLATFORM_WINDOWS",
            "NM_BUILD_DLL",
		}

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
					
    filter "configurations:Debug"
        defines "NM_DEBUG"
        symbols "On"
                
    filter "configurations:Release"
        defines "NM_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NM_DIST"
        optimize "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    systemversion "latest"
    
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
    }
	
	filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        
		links 
		{ 
			"Nu"
		}
        
		defines 
		{ 
            "NM_PLATFORM_WINDOWS",
		}
    
    filter "configurations:Debug"
        defines "NM_DEBUG"
        symbols "On"
                
    filter "configurations:Release"
        defines "NM_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "NM_DIST"
        optimize "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"