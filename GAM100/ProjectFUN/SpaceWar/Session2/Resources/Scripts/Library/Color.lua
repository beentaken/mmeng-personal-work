--Color Class (table)
Color = {R = 0 ,G = 0,B = 0,A = 0 , className = "Color"}
--Color Class Metatable
Color.mt = {}

--Creation by Constructor simulation
Color.mt.__call = function(caller,r,g,b,a)
R = r or 0 
G = g or 0 
B = b or 0
A = a or 0
p = {}
setmetatable(p,Color)
Color.__index = Color
p.R = r
p.G = g
p.B = b
p.A = a
p.className = "Color"
return p
end
setmetatable(Color,Color.mt)

--Creation with new
function Color:new(r,g,b,a)
R = r or 0 
G = g or 0 
B = b or 0
A = a or 0
p = {}
setmetatable(p,self)
self.__index = self
p.R = r
p.G = g
p.B = b
p.A = a
p.className = "Color"
return p
end

--Addition overload (adding two Colors)
Color.__add = function(a,b)
local pr = Color()
pr.R = a.R + b.R
pr.G = a.G + b.G
pr.B = a.B + b.B
pr.A = a.A + b.A
return pr
end

--Substraction overload
Color.__sub = function(a,b)
local pr = Color()
pr.R = a.R - b.R
pr.G = a.G - b.G
pr.B = a.B - b.B
pr.A = a.A - b.A
return pr
end

--Color * color overload
Color.__mul = function(a,b)
local pr = Color()
pr.R = a.R * b.R
pr.G = a.G * b.G
pr.B = a.B * b.B
pr.A = a.A * b.A
return pr
end

--Color / color number overload
Color.__div = function(a,b)
local pr = Color()
pr.R = a.R / b.R
pr.G = a.G / b.G
pr.B = a.B / b.B
pr.A = a.A / b.A
return pr
end

--comparing 2 Colors
Color.__eq = function(a,b)
if(a.R == b.R and a.G == b.G and a.B == b.B and a.A == b.A) then return true end
return false
end


function Color:Clamp()
if(self.R > 1.0) then self.R = 1.0 end 
if(self.G > 1.0) then self.G = 1.0 end
if(self.B > 1.0) then self.B = 1.0 end
if(self.A > 1.0) then self.A = 1.0 end

if(self.R < 0.0) then self.R = 0.0 end
if(self.G < 0.0) then self.G = 0.0 end
if(self.B < 0.0) then self.B = 0.0 end
if(self.A < 0.0) then self.A = 0.0 end
end

-- this is used by C++ to create a lua Color
function CreateColor()
local pt = Color()
return pt
end