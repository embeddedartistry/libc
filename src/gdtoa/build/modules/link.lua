-- Copyright © 2017 Embedded Artistry LLC.
-- License: MIT. See LICENSE file for details.


local m = {}

local ROOT = "../"
local OUTPUT_DIR = "buildresults"
local FILENAME = output
local WL = true

-- Use this function if you need to override the default
-- build ROOT location
function m.name(filename)
  FILENAME = filename
end

function m.use_wl(en)
	WL = en
end

function m.outputTo(targetdir)
	OUTPUT_DIR = ROOT .. targetdir .. "/"
end

-- Gets linker flags
function m.flags()
	if WL == true then
		string = "-Wl,-map," .. OUTPUT_DIR .. FILENAME .. ".map"
	else
		string = "-map " .. OUTPUT_DIR .. FILENAME
	end

 	return string
end

return m
