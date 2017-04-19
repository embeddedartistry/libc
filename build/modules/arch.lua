-- Copyright © 2017 Embedded Artistry LLC.
-- License: MIT. See LICENSE file for details.


local m = {}

local ROOT = "../"

-- Use this function if you need to override the default
-- build ROOT location
function m.set_build_top(top)
  ROOT = top
end

-- Gets you to the arch top: e.g. arch/x86/
function m.root()
  return ROOT .. "arch/%{cfg.architecture}/"
end

-- Gets you to the arch include dir: e.g. arch/x86/include/
function m.include()
  return ROOT .. "arch/%{cfg.architecture}/include/"
end

-- Gets you to the arch lib dir: e.g. arch/x86/lib/
function m.lib()
  return ROOT .. "arch/%{cfg.architecture}/lib/"
end

return m
