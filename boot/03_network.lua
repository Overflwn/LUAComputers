--[[
	Networking API for LUAComputers
	
~Piorjade
]]

_G.networking = {}

function _G.networking.send(ip, message, port)
	local msg = pickle({ip, message, port})
	return _G.NETWORKING_SOCKET:sendto(msg, ip, port)
end

function _G.networking.receive()
	return unpickle(_G.NETWORKING_SOCKET:receive() or "{}")
end