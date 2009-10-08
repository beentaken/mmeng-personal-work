PIOVER180 = 0.0174532925199
FUN_EPSILON = 0.0005

--Vector2D Class (table)
Vector2D = {X = 0,Y = 0,className = "Vector2D"}
--Vector2D Class Metatable
Vector2D.mt = {}

--Creation by Constructor simulation
Vector2D.mt.__call = function(caller,x,y)
x = x or 0 --set x to 0 if it is nil
y = y or 0 --set y to 0 if it is nil
p = {}
setmetatable(p,Vector2D)
Vector2D.__index = Vector2D
p.X = x
p.Y = y
p.className = "Vector2D"
return p
end
setmetatable(Vector2D,Vector2D.mt)

--Creation with new
function Vector2D:new(x,y)
x = x or 0 --set x to 0 if it is nil
y = y or 0 --set y to 0 if it is nil
p = {}
setmetatable(p,self)
self.__index = self
p.X = x
p.Y = y
p.className = "Vector2D"
return p
end

--Addition overload (adding two Vector2Ds)
Vector2D.__add = function(a,b)
local pr = Vector2D()
pr.X = a.X + b.X
pr.Y = a.Y + b.Y
return pr
end

--Substraction overload
Vector2D.__sub = function(a,b)
local pr = Vector2D()
pr.X = a.X - b.X
pr.Y = a.Y - b.Y
return pr
end

--Vector2D * number overload
Vector2D.__mul = function(a,b)
local pr = Vector2D()
pr.X = a.X * b
pr.Y = a.Y * b
return pr
end

--Vector2D / number number overload
Vector2D.__div = function(a,b)
local pr = Vector2D()
pr.X = a.X / b
pr.Y = a.Y / b
return pr
end

--comparing 2 Vector2Ds
Vector2D.__eq = function(a,b)
if(a.X == b.X and a.Y == b.Y) then return true end
return false
end


function Vector2D:Translate(x,y)
self.X = self.X + x
self.Y = self.Y + y
end

function Vector2D:Scale(x,y)
self.X = self.X * x
self.Y = self.Y * y
end

function Vector2D:Rotate(angle)
COS = math.cos(angle * PIOVER180);
SIN = math.sin(angle * PIOVER180);
X1 = (self.X*COS - self.Y*SIN);
Y1 = (self.Y*COS + self.X*SIN);
self.X = X1;
self.Y = Y1;
end

function Vector2D:GetNormal()
local pr = Vector2D()
pr.X = -self.Y
pr.Y = self.X
return pr
end

function Vector2D:GetReflectedVector(vn)
	local rv = Vector2D();
	d = math.sqrt(self.X * self.X + self.Y * self.Y);
	if((d<= -FUN_EPSILON) or (d >=FUN_EPSILON)) then
		rv.X = self.X/d;
		rv.Y = self.Y/d;	
	end

	dot = (rv.X*vn.X + rv.Y*vn.Y);
	rv.X = rv.X - 2*dot*vn.X;
	rv.Y = rv.Y - 2*dot*vn.Y;	
	return rv
end

function Vector2D:SetNormalize()
	d = math.sqrt(self.X*self.X + self.Y*self.Y);
	if((d<= -FUN_EPSILON) or (d >=FUN_EPSILON))
	then
		self.X = self.X/d;
		self.Y = self.Y/d;
	end
end

function Vector2D:GetDotProduct(v)
	return (self.X*v.X + self.Y*v.Y)
end

function Vector2D:GetLength()
	return math.sqrt(self.X*self.X + self.Y*self.Y)
end

function Vector2D:Clear()
	self.X = 0
	self.Y = 0
end

-- this is used by C++ to create a lua Vector2D
function CreateVector()
local pt = Vector2D()
return pt
end