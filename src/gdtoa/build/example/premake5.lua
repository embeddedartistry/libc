-- Copyright © 2017 Embedded Artistry LLC.
-- License: MIT. See LICENSE file for details.

-- For reference, please refer to the premake wiki:
-- https://github.com/premake/premake-core/wiki

local arch_ = require "modules/arch"
local build_ = require "modules/buildinfo"
local link_ = require "modules/link"

local ROOT = "../"
local RESULTSROOT = "../buildresults/%{cfg.platform}_%{cfg.buildcfg}/"

--------------------------------
--  WORKSPACE CONFIGURATION   --
--------------------------------
workspace "EmbeddedArtistry"
  configurations { "debug", "release" }
  platforms      { "x86_64", "x86_32" }

  -- _ACTION is the argument you passed into premake5 when you ran it.
  local project_action = "UNDEFINED"
  if _ACTION ~= nill then project_action = _ACTION end

  -- Where the project/make files are output
  location(ROOT .. "build/gen")

-----------------------------------
-- Global Compiler/Linker Config --
-----------------------------------
  filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On"
  filter "configurations:Release"  defines { "NDEBUG" } optimize "On"

  filter { "platforms:x86_32" }
    architecture "x86"

  filter { "platforms:x86_64" }
    architecture "x86_64"

  -- Global settings for building makefiles
  filter { "action:gmake" }
    flags { "C++11" }

  -- Global settings for building make files on mac specifically
  filter { "system:macosx", "action:gmake"}
    toolset "clang"

  filter {} -- clear filter when you know you no longer need it!

--------------------------------------------------------------------------------
---------------------------------- Projects ------------------------------------
--------------------------------------------------------------------------------

-----------------------------
-- Architecture Lib Config --
-----------------------------

  project "libarch"
    kind "StaticLib"
    language "C++"
    targetdir (RESULTSROOT .. "arch/%{cfg.architecture}")
    targetname "arch"

    local SourceDir = ROOT .. "arch/%{cfg.architecture}/";
    files
    {
      SourceDir .. "**.h",
      SourceDir .. "**.c",
      SourceDir .. "**.hpp",
      SourceDir .. "**.cpp"
    }

    buildoptions {"-fno-builtin", "-nodefaultlibs"}
    linkoptions {"-nodefaultlibs", "-nostartfiles"}

    filter {} -- clear filter!

    includedirs
    {
      arch_.include(),
      SourceDir,
      SourceDir .. "include/",
      ROOT .. "lib/",
      ROOT .. "lib/libc/include",
    }

----------------------------
-- Embeddable libc Config --
----------------------------

  project "libc"
    kind "StaticLib"
    language "C"
    targetdir (RESULTSROOT .. "lib")
    targetname "c"

    local SourceDir = ROOT .. "lib/libc/";
    files
    {
      SourceDir .. "**.h",
      SourceDir .. "**.c"
    }

    buildoptions {"-fno-builtin", "-nodefaultlibs"}
    linkoptions {"-nodefaultlibs", "-nostartfiles"}

    filter {} -- clear filter!

    includedirs
    {
      arch_.include(),
      SourceDir,
      SourceDir .. "include/",
      ROOT .. "lib/",
      ROOT .. "lib/libc/include",
    }

    links
    {
      "libmalloc_freelist"
    }

------------------------------
-- libmalloc Library Config --
------------------------------

  project "libmalloc_threadx"
    kind "StaticLib"
    language "C"
    targetdir (RESULTSROOT .. "lib/malloc_tx")
    targetname "malloc"

    local SourceDir = ROOT .. "lib/malloc/";
    files
    {
      SourceDir .. "**.h",
      SourceDir .. "aligned_malloc.c",
      SourceDir .. "malloc_threadx.c"
    }

    buildoptions {"-fno-builtin", "-nodefaultlibs"}
    linkoptions {"-nodefaultlibs", "-nostartfiles"}

    filter {} -- clear filter!

    includedirs
    {
      SourceDir,
      arch_.include(),
      ROOT .. "lib/",
      ROOT .. "lib/libc",
      ROOT .. "os/"
    }

  project "libmalloc_freelist"
    kind "StaticLib"
    language "C"
    targetdir (RESULTSROOT .. "lib/malloc")
    targetname "malloc"

    local SourceDir = ROOT .. "lib/malloc/";
    files
    {
      SourceDir .. "**.h",
      SourceDir .. "aligned_malloc.c",
      SourceDir .. "malloc_freelist.c"
    }

    buildoptions {"-fno-builtin", "-nodefaultlibs"}
    linkoptions {"-nodefaultlibs", "-nostartfiles"}

    filter {} -- clear filter!

    includedirs
    {
      SourceDir,
      arch_.include(),
      ROOT .. "lib/",
      ROOT .. "lib/libc/include",
    }

----------------------------
-- Version Library Config --
----------------------------

  project "LibVersion"
    kind "StaticLib"
    language "C++"
    output_dir = RESULTSROOT .. "lib"
    targetdir (output_dir)
    targetname "version"

    prebuildcommands { "@rm " .. ROOT .. output_dir .. "/" .. "libversion.a" }

    local SourceDir = ROOT .. "lib/version/";
    files
    {
      SourceDir .. "**.h",
      SourceDir .. "**.c",
    }

    filter {} -- clear filter!

    -- Definitions for the version library
    buildoptions {
      build_.defines(),
    }

    includedirs
    {
      SourceDir,
    }

-------------------------------
-- Embeddable Library Config --
-------------------------------

  project "Libraries"
    kind "StaticLib"
    language "C++"
    targetdir (RESULTSROOT .. "lib")
    targetname "embedded"

    local SourceDir = ROOT .. "lib/";
    files
    {
      SourceDir .. "**.h", SourceDir .. "**.hpp",
      SourceDir .. "**.c", SourceDir .. "**.cpp"
    }

    -- Exclude libc files
    filter { "files:**/lib/libc/**" }
      flags {"ExcludeFromBuild"}

    -- Exclude libmalloc files
    filter { "files:**/lib/malloc/**" }
      flags {"ExcludeFromBuild"}

    --Exclude libcpp files
    filter { "files:**/lib/libcpp/**" }
      flags {"ExcludeFromBuild"}

    --Exclude libversion files
    filter { "files:**/lib/version/**" }
      flags {"ExcludeFromBuild"}

    filter {} -- clear filter!

    includedirs
    {
      SourceDir,
      --Need libc++ to enable htis
      --ROOT .. "lib/libc/include",
      arch_.include(),
      "/usr/local/opt/llvm/include/c++/v1/",
      "/usr/local/opt/llvm/include",
    }

    links
    {
      "LibVersion",
    }

-----------------------------
-- C-only Libraries Config --
-----------------------------

  project "Libraries_C"
    kind "StaticLib"
    language "C"
    targetdir (RESULTSROOT .. "lib")
    targetname "embedded_c"

    local SourceDir = ROOT .. "lib/";
    files
    {
      SourceDir .. "**.h",
      SourceDir .. "**.c",
    }

    -- Exclude libc files
    filter { "files:**/lib/libc/**" }
      flags {"ExcludeFromBuild"}

    -- Exclude libmalloc files
    filter { "files:**/lib/malloc/**" }
      flags {"ExcludeFromBuild"}

    --Exclude libcpp files
    filter { "files:**/lib/libcpp/**" }
      flags {"ExcludeFromBuild"}

    --Exclude libversion files
    filter { "files:**/lib/version/**" }
      flags {"ExcludeFromBuild"}

    filter {} -- clear filter!

    includedirs
    {
      SourceDir,
      arch_.include(),
      ROOT .. "lib/libc/include",
      "/usr/local/opt/llvm/include",
    }

    links
    {
      "LibVersion"
    }

-------------------------------
-- C Unit Test Configuration --
-------------------------------

  project "C_UnitTests"
    kind "ConsoleApp"
    language "C"
    targetdir (RESULTSROOT .. "bin/tests/c/")
    targetname "test_c_libs.bin"

    --Temporary
    removeplatforms { "X86_32" }

    local SourceDir = ROOT .. "test/lib/";

    files
    {
      SourceDir .. "**.h",
      SourceDir .. "**.c",
    }

    filter {} -- clear filter!

    includedirs
    {
      SourceDir, -- include root source directory to allow for absolute include paths
      arch_.include(),
      ROOT .. "lib/",
      ROOT .. "lib/external/",
      ROOT .. "lib/libc/include",
      ROOT .. "test/cmocka/",
    }

    -- Library Dependencies
    libdirs
    {
      arch_.lib() .. "cmocka/"
    }

    links
    {
      "Libraries_C",
      "cmocka"
    }

------------------------------
-- Simulator Project Config --
------------------------------

  project "Simulator"
    kind "ConsoleApp"
    language "C++"
    output_dir = RESULTSROOT .. "bin/simulator"
    targetdir (RESULTSROOT .. "bin/simulator")
    targetname "simulator.bin"

    -- Set up our linker flags
    link_.outputTo(output_dir)
    link_.name("simulator")

    local SourceDir = ROOT .. "main/simulator/";

    files
    {
      --TODO: recombine simulator
      --SourceDir .. "**.h",
      SourceDir .. "**.hpp",
      --SourceDir .. "**.c",
      SourceDir .. "**.cpp",
    }

    filter {} -- clear filter!

    linkoptions {link_.flags()}

    includedirs
    {
      SourceDir, -- include root source directory to allow for absolute include paths
      arch_.include(),
      ROOT .. "lib/",
      --Need libc++ to enable htis
      --ROOT .. "lib/libc/include",
      arch_.include(),
      "/usr/local/opt/llvm/include/c++/v1/",
      "/usr/local/opt/llvm/include",
    }

    links
    {
      "Libraries",
      "libmalloc_freelist"
    }

  project "Simulator_C"
    kind "ConsoleApp"
    language "C"
    output_dir = RESULTSROOT .. "bin/simulator_c"
    targetdir (output_dir)
    targetname "simulator.bin"

    -- Set up our linker flags
    link_.outputTo(output_dir)
    link_.name("simulator")

    local SourceDir = ROOT .. "main/simulator/";

    files
    {
      --TODO: recombine simulator
      SourceDir .. "**.h",
      SourceDir .. "**.c",
    }

    filter {} -- clear filter!

    buildoptions {"-nodefaultlibs"}
    linkoptions {"-nodefaultlibs", link_.flags()}

    includedirs
    {
      SourceDir, -- include root source directory to allow for absolute include paths
      ROOT .. "lib/",
      ROOT .. "lib/libc/include",
      arch_.include(),
    }

    links
    {
      "Libraries_C",
      "libc",
      "libmalloc_freelist",
      "System"
    }

