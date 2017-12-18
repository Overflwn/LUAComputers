--[[
	GPU API for LUAComputers
	
~Piorjade
]]

_G.eventList = {}

_G.event = {}

function _G.event.push(name, ...)
	table.insert(_G.eventList, { name, unpack({...}) })
end

function _G.event.pull()
	return table.remove(_G.eventList)
end