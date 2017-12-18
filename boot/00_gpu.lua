--[[
	GPU API for LUAComputers
	
~Piorjade
]]

--Constants
_G.TERM_SIZE_X, _G.TERM_SIZE_Y = 800 / 4, 600 / 4
_G.gpu = {}
local currentBuffer = {}
local col = {0,0,0}

function gpu.clear(_col)
	love.graphics.setBackgroundColor(_col or col)
	currentBuffer = {}
end

function gpu.setCursorPos(x, y)
	if not (type(x) == "number" and type(y) == "number") then return false, "num, num expected" end
	cX, cY = x, y
end

function gpu.setColor(_col)
	if type(_col) == "table" and #_col == 3 then
		col[1] = _col[1]
		col[2] = _col[2]
		col[3] = _col[3]
	end
end


function gpu.drawPixel(x, y, _col)
	
	if type(currentBuffer[y]) ~= "table" then currentBuffer[y] = {} end
	currentBuffer[y][x] = {
		color = {_col[1] or col[1], _col[2] or col[2], _col[3] or col[3]}
	}
	
end

function _G.getBuffer()
	return currentBuffer
end

_G.termLoaded = true