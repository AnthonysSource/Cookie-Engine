project "CookieEngine"
    kind "StaticLib"
    files {
        "Engine/**.c",
        "Engine/**.cpp",
        "Engine/**.h",
        "Engine/**.hpp",
        "ThirdParty/imgui/**.cpp",
        "ThirdParty/imgui/**.h",
        "ThirdParty/stb_image/*.cpp",
        "ThirdParty/glad/src/glad.c"
    }
    includedirs {
        "ThirdParty/glfw/include",
        "ThirdParty/glad/include",
        "ThirdParty/glm",
        "ThirdParty/imgui",
        "ThirdParty/stb_image",
        "ThirdParty/spdlog/include",
        "Engine"
    }
    links {
        "opengl32.lib",
        "GLFW"
    }

group "ThirdParty"
    include("ThirdParty/glfw")
group "" -- end of "ThirdParty"

-- Function to be used by external libraries that want to use this project
-- This is to workaround the fact that Premake doesn't have public includes
-- like CMake
function UseCookieEngine()
    includedirs { 
        "%{wks.location}/source/code/CookieEngine/ThirdParty/glfw/include",
        "%{wks.location}/source/code/CookieEngine/ThirdParty/glad/include",
        "%{wks.location}/source/code/CookieEngine/ThirdParty/glm",
        "%{wks.location}/source/code/CookieEngine/ThirdParty/imgui",
        "%{wks.location}/source/code/CookieEngine/ThirdParty/stb_image",
        "%{wks.location}/source/code/CookieEngine/ThirdParty/spdlog/include",
        "%{wks.location}/source/code/CookieEngine/Engine"
    }
    links { "CookieEngine" }
 end