--[[
		filesystem API for LUAComputers
		
	~Piorjade

]]

_G.filesystem = {}

function filesystem.open(path, mode)
	if type(path) ~= "string" or type(mode) ~= "string" then return false, "path, mode expected" end
	if mode == "r" or mode == "w" or mode == "a" then
		return love.filesystem.newFile(path, mode)
	else
		return false, "invalid mode"
	end
end

filesystem.exists = love.filesystem.exists

filesystem.mkdir = love.filesystem.createDirectory

filesystem.list = love.filesystem.getDirectoryItems

filesystem.isDir = love.filesystem.isDirectory
filesystem.isFile = love.filesystem.isFile
filesystem.load = love.filesystem.load

filesystem.remove = love.filesystem.remove
