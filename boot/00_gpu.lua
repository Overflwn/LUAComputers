--[[
	GPU API for LUAComputers
	
~Piorjade
]]

--Constants
_G.gpu = {}
local currentBuffer = {}
local col = {0,0,0}

function gpu.clear(_col)
	love.graphics.setBackgroundColor(_col or col)
	currentBuffer = {}
end

function gpu.setColor(_col)
	if type(_col) == "table" and #_col == 3 then
		col[1] = _col[1]
		col[2] = _col[2]
		col[3] = _col[3]
	end
end

function gpu.getColor() return col end

function gpu.getTermSize()
	return TERM_SIZE_X, TERM_SIZE_Y
end

function gpu.drawRect(x, y, width, height, _col)
	if not type(x) == "number" and type(y) == "number" and type(width) == "number" and type(height) == "number" then return false, "num, num, num, num expected" end
	local maxX, maxY = gpu.getTermSize()
	if x < 0 or x > maxX or y < 0 or y > maxY or x+width-1 > maxX or y+height-1 > maxY then return false, "coordinates out of bounds" end
	for yc = y, y+height-1 do
		if not currentBuffer[yc] then currentBuffer[yc] = {} end
		for xc = x, x+width-1 do
			currentBuffer[yc][xc] = {
				color = {_col[1] or col[1], _col[2] or col[2], _col[3] or col[3]}
			}
		end
	end
end


function gpu.drawPixel(x, y, _col)
	local maxX, maxY = gpu.getTermSize()
	if x < 0 or x > maxX or y < 0 or y > maxY then return false, "coordinates out of bounds" end
	if type(currentBuffer[y]) ~= "table" then currentBuffer[y] = {} end
	currentBuffer[y][x] = {
		color = {_col[1] or col[1], _col[2] or col[2], _col[3] or col[3]}
	}
	
end

function _G.getBuffer()
	return currentBuffer
end

_G.termLoaded = true