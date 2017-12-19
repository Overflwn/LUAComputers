--[[
		BIOS.lua for LuaOS
		
	~Piorjade
]]

function _G.loadfile(file)
	--Fix loadfile, got broken smh
	if filesystem.isFile(file) then
		local func = filesystem.load(file)
		setfenv(func, _G)
		return func
	else
		return false, "not a file"
	end
end

function _G.dofile(file)
	--dofile got broken too smh
	local func, err = loadfile(file)
	if func then
		return func()
	else
		return func, err
	end
end


--Load libraries
local libList = filesystem.list("libs")
table.sort(libList)
for each, lib in ipairs(libList) do
	local func = loadfile("libs/"..lib)
	local _, err = pcall(func)
	if not _ then _ = logError("errors", "Failed to load '"..tostring(lib).."': "..tostring(err)) end
end


term.writeText(1, 1, "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
term.writeText(1, 3, "abcdefghijklmnopqrstuvwxyz")
term.writeText(1, 5, "0123456789")
term.writeText(1, 7, ",.;-+=/")

while true do
	local _, x, y, btn = unpack(event.pull())
	if (_ == "mouse_click" or _ == "mouse_release" or _ == "mouse_drag") and btn == 1 then
		gpu.drawPixel(x, y, {255, 0, 0})
	end
	--[[if _ == "mouse_click" and btn == 1 then
		local success, err = modem.send("192.168.0.38", "Hewwo world")
		if not success then term.writeText(1,11,tostring(err)) else
			term.writeText(1,9,"Sent")
		end
	elseif _ == "mouse_click" and btn == 2 then
		term.writeText(1,9,"Receiving: ")
		local ip, msg, port = modem.receive()
		if msg then term.writeText(12,9,msg) else
			term.writeText(12,9,"No message.")
		end
	end]]
end