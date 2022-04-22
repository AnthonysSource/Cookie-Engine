workspace "Cookie"
    configurations { "Debug", "Release", "Shipping" }
    platforms { "Win64" }
    language "C++"
	cppdialect "C++17"
    startproject "CookieGame"

    filter { "platforms:Win64" }
        system "Windows"
        architecture "x86_64"

    -- Output Directories
    outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    targetdir ("%{wks.location}/bin/%{prj.name}/" .. outputDir)
    objdir ("%{wks.location}/bin-obj/%{prj.name}/" .. outputDir)

-- Configurations
---------------------------------------------------------------------
filter "configurations:Debug"
    defines {
        "COOKIE_PLATFORM_WINDOWS",
        "GLFW_INCLUDE_NONE",
        "COOKIE_DEBUG",
        "CKE_ASSERTS",
        "COOKIE_LOGGING"
    }
    symbols "On"
    optimize "Off"

filter "configurations:Release"
    defines {
        "COOKIE_PLATFORM_WINDOWS",
        "GLFW_INCLUDE_NONE",
        "COOKIE_DEBUG",
        "CKE_ASSERTS",
        "COOKIE_LOGGING"
    }
    symbols "On"
    optimize "On"

filter "configurations:Shipping"
    defines {
        "COOKIE_PLATFORM_WINDOWS",
        "GLFW_INCLUDE_NONE",
    }
    symbols "Off"
    optimize "On"

-- Project Includes
---------------------------------------------------------------------
include("source/code/CookieEngine")
include("source/code/CookieGame")