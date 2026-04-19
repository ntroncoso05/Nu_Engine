workspace "Nu"
	architecture "x64"
	targetdir "build"
	
	configurations 
	{ 
		"Debug", 
        "Release",
        "Dist"
    }
    
local outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Nu"
    location "Nu"
    kind "SharedLib"
    language "C++"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/**.h", 
		"%{prj.name}/**.c", 
		"%{prj.name}/**.hpp", 
		"%{prj.name}/**.cpp" 
    }

    includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor",
	}
    
	filter "system:windows"
		cppdialect "C++17"
        staticruntime "On"
        
		defines 
		{ 
            "NM_PLATFORM_WINDOWS",
            "NU_BUILD_DLL",
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
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	dependson 
	{ 
		"Nu"
    }
    
	files 
	{ 
		"%{prj.name}/**.h", 
		"%{prj.name}/**.c", 
		"%{prj.name}/**.hpp", 
		"%{prj.name}/**.cpp" 
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
    
        postbuildcommands
        {
            ("{COPY} ../bin/" .. outputdir .. "/Nu/Nu.dll %{cfg.targetdir}")
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