

--[[
		term API for LuaOS
		
	~Piorjade
]]

--One char: 6x6

_G.term = {}

local file = filesystem.open("fonts/test.lf", "r")
local data = file:read()
--logError("font", pickle(c))
local chars = unpickle(tostring(data))
file:close()

function term.writeRawCharAtTotal(x, y, char)
	
	
	if chars[char] then
		for each, coordinate in ipairs(chars[char]) do
			gpu.drawPixel(x+coordinate[1], y+coordinate[2], {255, 255, 255})
		end
	end
end

function term.writeRawCharAt(x, y, char)
	--chars have a 6x6 grid and the top left corner has the coordinate (0|0)
	--So the screen has a possibility of around 53x30 letters on the screen with this function
	--[[
		so the letter "A" basically looks like this:
		
		001100		  11
		010010		 1  1
		110011      11  11
		111111	--> 111111	
		110011	    11  11
		110011	    11  11
	]]
	
	if chars[char] then
		for each, coordinate in ipairs(chars[char]) do
			gpu.drawPixel(x*6-6+coordinate[1]+1, y*6-6+coordinate[2]+1, {255, 255, 255})
		end
	end
end

function term.writeText(x, y, text)
	local tmp_text = text
	local counter = 1
	repeat
		term.writeRawCharAtTotal( 8 * counter - 8 + x*8 - 8 + 1, y*6-6+1, string.sub(tmp_text, 1, 1))
		tmp_text = string.sub(tmp_text, 2)
		counter = counter+1
	until tmp_text == nil or #tmp_text == 0
end