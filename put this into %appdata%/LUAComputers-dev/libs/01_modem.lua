--[[

		modem API for LuaOS

	~Piorjade
]]

_G.modem = {}

function _G.modem.receive(timeout)
	if timeout and type(timeout) == "number" and timeout > 0 then
		
		local timer = system.setTimer(timeout)
		logError("networkLog", "Waiting for message with timeout. "..tostring(timer))
		local ev, a, b, c
		repeat
			ev, a, b, c = unpack(event.pull())
			logError("events", tostring(ev))
		until ev == "network_message" or (ev == "timer" and a == timer)
		logError("networkLog", "Got "..tostring(ev))
		if ev == "network_message" then
			return a, b, c
		end
		return
	else
		logError("networkLog", "Waiting for message without timeout")
		local ev, a, b, c
		repeat
			ev, a, b, c = unpack(event.pull())
			logError("events", tostring(ev))
		until ev == "network_message"
		logError("networkLog", "Received: "..tostring(b))
		return a, b, c
	end
end

function _G.modem.send(ip, msg)
	return networking.send(ip, msg, 76767)
end