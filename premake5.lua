-- Copyright © 2017 Embedded Artistry LLC.
-- License: MIT. See LICENSE file for details.

-- For reference, please refer to the premake wiki:
-- https://github.com/premake/premake-core/wiki

local arch_ = require "build/modules/arch"

local ROOT = "./"
local RESULTSROOT = ROOT .. "buildresults/%{cfg.platform}_%{cfg.buildcfg}/"

--------------------------------
--  WORKSPACE CONFIGURATION   --
--------------------------------
workspace "EmbeddedArtistry LibC"
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

  project "libc"
    kind "StaticLib"
    language "C"
    targetdir (RESULTSROOT .. "libc")
    targetname "c"

    local SourceDir = ROOT .. "src/";
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
      SourceDir .. "../include/",
      ROOT .. "lib/",
      "/usr/local/opt/llvm/include",
      "/usr/local/opt/llvm/include/c++/v1/"
    }

    libdirs
    {

    }

    links
    {

    }

project "libc_UnitTests"
    kind "ConsoleApp"
    language "C"
    targetdir (RESULTSROOT .. "test/")
    targetname "libc.bin"

    --Temporary
    removeplatforms { "X86_32" }

    local SourceDir = ROOT .. "test/";

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
      ROOT .. "include/",
      ROOT .. "test/cmocka/",
      "/usr/local/opt/llvm/include",
      "/usr/local/opt/llvm/include/c++/v1/"
    }

    -- Library Dependencies
    libdirs
    {
      arch_.lib() .. "cmocka/"
    }

    links
    {
      "libc",
      "cmocka"
    }
