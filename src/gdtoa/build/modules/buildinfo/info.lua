-- Copyright © 2017 Embedded Artistry LLC.
-- License: MIT. See LICENSE file for details.


local m = {}

function m.machine()
	return "$(shell echo `whoami`@`hostname`)"
end

function m.date()
	return "\"$(shell date)\""
end

return m
