-- Copyright © 2017 Embedded Artistry LLC.
-- License: MIT. See LICENSE file for details.

local m = {}

ROOT = "../../"

function m.set_root_dir(root)
	ROOT = root
end

-- Commit hash
function m.commit()
  return "$(shell cd " .. ROOT .. "; git log -1 --format=\"%h\")"
end

-- Count of commits past
function m.commits_past()
  return "$(strip $(word 2, $(subst -, ,$(shell cd " .. ROOT .. "; git describe --long --dirty --tags))))"
end

-- Dirty or not
function m.dirty()
  return "$(strip $(word 4, $(subst dirty,+, $(subst -, ,$(shell cd " .. ROOT .. "; git describe --long --dirty --tags)))))"
end

function m.tag()
	return "$(strip $(word 1, $(subst -, ,$(shell cd " .. ROOT .. "; git describe --long --dirty --tags))))"
end

return m
