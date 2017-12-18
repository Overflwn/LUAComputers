--[[

			LUAComputers
		
	This game / program is a computer "simulator", which is able to run LUA code.
	It is heavily inspired by the Minecraft mod "ComputerCraft", therefore it uses low resolution which
	leads to a retro-like feeling.
	
	What this program tries to do better than ComputerCraft:
		-	Have a higher amount of "pixels" (not to confuse with the actual resolution; 1 "pixel" = 1 character with a background color)
			(320x180)
		-	Overall higher performance
		-	Global networking system (with use of the socket API from LÖVE)
		-	(A wrapper for the sound system)
		
	Additional notes:
		- It will try to name all the APIs the same as in ComputerCraft (which increases compatibility with programs made for it)
		
	~Piorjade @ 2017
	
	Last Edit: 13/12/2017 (DD/MM/YYYY)
	
	DEV CHANGES:
	-	Make the window 16:9 (standard: 320x180, that's the retro feel we want)
	-	Make it scale based on the resolution of the window
	-	Remove that "one char on a 'pixel' " policy; a "pixel" functions like an actual pixel.
	-	Make that "one char on a pixel" policy as the term API ONTOP of the normal graphics API (current name: gpu)

]]

--[[ Modules / APIs ]]

-- The socket API will be used to make the networking layer
local socket = require("socket")

--[[ Variables ]]

local mainStuff = {}
for each, thing in pairs(_G) do
	mainStuff[each] = thing
end
mainStuff.love = nil

-- Constants
_G.NETWORKING_HOST_ADDRESS, _G.NETWORKING_HOST_PORT, _G.NETWORKING_UPDATERATE, _G.NETWORKING_SOCKET, _G.NETWORKING_TIMER = 0, 0, 0, 0, 0
_G.TERM_SIZE_X, _G.TERM_SIZE_Y = 0, 0
local scaleX, scaleY = 0, 0
local pixel_width, pixel_height = 0, 0
local font = nil
local mouse = {pressed = false, btn = nil, x = 0, y = 0}
--As we want 120 ticks per second, we want to update every ~0.0083 seconds
local tickAt = 0.0083
local counter = 0
local secondCounter = 0
local bios = nil
local biosCoroutine = nil
local ev = {}
local timers = {}
local system = {}

_G.eventList = {}
--Essential
function _G.copyTable(t1)
	local t = {}
	for a, b in pairs(t1) do
		if type(b) ~= "table" then
			t[a] = b
		else
			t[a] = copyTable(b)
		end
	end
	return t
	
end

function system.setTimer(timeout)
	if timeout and type(timeout) == "number" and timeout >= 1 then
		table.insert(timers, {#timers+1, 0, timeout})
		return #timers
	end
end

--Load APIs located in /boot
local apis = love.filesystem.getDirectoryItems("boot")
table.sort(apis)
for each, file in ipairs(apis) do
	dofile("boot/"..file)
end

if not _G.termLoaded then return else _G.termLoaded = nil end

--[[ Functions ]]

local function logError(name, err)
	local file = love.filesystem.newFile(name..".txt")
	local ok, error = file:open("w")
	if not ok then print("ERROR WITH logError: "..tostring(error)) love.event.quit() end
	local ok = file:write("ERROR: "..tostring(err).."\n")
	file:close()
	return ok
end

function love.conf(t)
	t.console = true
end

function love.load()
	
	if not (love.window.setMode(1600, 900)) then love.event.quit() end
	-- Runs once on startup
	love.graphics.setBackgroundColor(0,0,0)
	-- Set up constants
	NETWORKING_HOST_ADDRESS = "localhost"
	NETWORKING_HOST_PORT = 7676
	NETWORKING_UPDATERATE = 0.1
	NETWORKING_TIMER = 0
	NETWORKING_SOCKET = socket.udp()
	NETWORKING_SOCKET:settimeout(0) --Disable the socket pausing the program when waiting for a message
	local success, err = NETWORKING_SOCKET:setsockname('*', 7676)
	if not success then
		print("Could not open socket: "..tostring(err))
		love.timer.sleep(5)
		love.event.quit()
	else
		print("Created socket.")
	end
	TERM_SIZE_X = 320 --800/4(200)
	TERM_SIZE_Y = 180 --600/4(150)
	scaleX, scaleY = love.graphics.getWidth() / 1280, love.graphics.getHeight() / 720
	gpu.setColor({0,0,0})
	gpu.clear()
	
	pixel_width = math.ceil(4 * scaleX)
	pixel_height = math.ceil(4 * scaleY)
	font = love.graphics.newFont(pixel_width)
	
	love.graphics.setFont(font)
	
	bios = loadfile("bios.lua")
	local env = {}
	setmetatable(env, {__index = mainStuff})
	env.event = copyTable(event)
	env.event.pull = function()
		return coroutine.yield()
	end
	env.gpu = gpu
	env.pickle = pickle
	env.unpickle = unpickle
	env.filesystem = filesystem
	env.networking = networking
	
	env.event.pull = function()
		return coroutine.yield()
	end
	env._ENV = env
	env._ENV._G = env._ENV
	env.logError = logError
	env.system = system
	setfenv(bios, env)
	biosCoroutine = coroutine.create(bios)
	
	
end

function love.update(dt)
	secondCounter = secondCounter+dt
	local toremove = {}
	if secondCounter >= 1 then
		for each, timer in ipairs(timers) do
			timer[2] = timer[2]+1
			if timer[2] >= timer[3] then
				event.push("timer", timer[1])
				table.insert(toremove, each)
				logError("timers", "timer "..tostring(timer[1]).." timed out.")
			end
		end
	end
	for each, timer in ipairs(toremove) do
		table.remove(timers, timer)
	end
	local data
	repeat
		data = networking.receive()
		if data then
			logError("log", "received something "..tostring(data))
		end
		if type(data) == "table" and #data == 3 then
			event.push("network_message", data[1], data[2], data[3])
		end
	until not data
	if counter >= tickAt then
		-- Runs every tick (uncapped; which is why dt (deltatime) is given; mainly background stuff only)
		if mouse.pressed then
			local newX, newY = math.ceil(love.mouse.getX()/pixel_width), math.ceil(love.mouse.getY()/pixel_height)
			if newX-mouse.x ~= 0 or newY-mouse.y ~= 0 then
				mouse.x, mouse.y = newX, newY
				event.push("mouse_drag", mouse.x, mouse.y, mouse.btn)
			end
		end
		
		
		ev = event.pull() or {}
		local _, err = coroutine.resume(biosCoroutine, ev)
		if not _ then
			local file = love.filesystem.newFile("errorLog.txt")
			local ok, error = file:open("a")
			if not ok then love.event.quit() end
			file:write(tostring(err).."\r\n")
			file:close()
			love.event.quit()
		end
		
		--[[local _, x, y, btn = unpack(event.pull() or {})
		if (_ == "mouse_click" or _ == "mouse_drag") and btn == 1 then
			gpu.drawPixel(x, y, {255, 0, 0})
		end]]
		
		counter = dt
		
	else
		counter = counter+dt
	end
end

function love.draw()
	-- Runs every frame (mainly drawing stuff here only)
	local buffer = getBuffer()
	for y, pixY in pairs(buffer) do
		for x, pixX in pairs(buffer[y]) do
			love.graphics.setColor(pixX.color)
			love.graphics.rectangle("fill", pixel_width*x-pixel_width, pixel_height*y-pixel_height, pixel_width, pixel_height)
		end
	end
end

function love.mousepressed(x, y, button, istouch)
	if (button == 1 or button == 2 or button == 3) and not mouse.pressed then
		local newX, newY = math.ceil(x/pixel_width), math.ceil(y/pixel_height)
		mouse.pressed = true
		mouse.x, mouse.y = newX, newY
		mouse.btn = button
		event.push("mouse_click", newX, newY, button)
	end
end

function love.mousereleased(x, y, button, istouch)
	if (button == 1 or button == 2 or button == 3) and button == mouse.btn then
		event.push("mouse_release", mouse.x, mouse.y, mouse.btn)
		mouse.pressed = false
		mouse.x, mouse.y = 0, 0
		mouse.btn = nil
	end
end

function love.keypressed(key)
	event.push("key_press", key)
end

function love.keyreleased(key)
	event.push("key_release", key)
end

function love.quit()
	
end

--[[ Code ]]