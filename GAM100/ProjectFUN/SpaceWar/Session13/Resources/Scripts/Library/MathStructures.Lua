
----------------------------------------------------------------------------
--Circle2D
----------------------------------------------------------------------------
Circle2D= {center = Point2D(),
		  radius = 0,
		  className = "Circle2D"}
Circle2D.mt = {}

--Creation by Constructor simulation
Circle2D.mt.__call = function(caller,c,r)
c = c or Point2D() 
r = r or 0
p = {}
setmetatable(p,Circle2D)
Circle2D.__index = Circle2D
p.center = c
p.radius = r
p.className = "Circle2D"
return p
end

setmetatable(Circle2D,Circle2D.mt)

--Creation with new
function Circle2D:new(c,r)
c = c or Point2D() 
r = r or 0
p = {}
setmetatable(p,self)
self.__index = self
p.center = c
p.radius = r
p.className = "Circle2D"
return p
end

-- this is used by C++ to create a lua Circle2D
function CreateCircle2D()
local pt = Circle2D()
return pt
end

----------------------------------------------------------------------------
--Line2D
----------------------------------------------------------------------------

Line2D= {point = Point2D(),
		  direction = Vector2D(),
		  className = "Line2D"}
Line2D.mt = {}

--Creation by Constructor simulation
Line2D.mt.__call = function(caller,pt,v)
pt = pt or Point2D() 
v = v or Vector2D()
p = {}
setmetatable(p,Line2D)
Line2D.__index = Line2D
p.point = pt
p.direction = v
p.className = "Line2D"
return p
end

setmetatable(Line2D,Line2D.mt)

--Creation with new
function Line2D:new(pt,v)
pt = pt or Point2D() 
v = v or Vector2D()
p = {}
setmetatable(p,self)
self.__index = self
p.point = pt
p.direction = v
p.className = "Line2D"
return p
end

-- this is used by C++ to create a lua Line2D
function CreateLine2D()
local pt = Line2D()
return pt
end

----------------------------------------------------------------------------
--LineSegment2D
----------------------------------------------------------------------------
LineSegment2D= {pointA = Point2D(),
		  pointB = Point2D(),
		  className = "LineSegment2D"}
LineSegment2D.mt = {}

--Creation by Constructor simulation
LineSegment2D.mt.__call = function(caller,a,b)
a = a or Point2D() 
b = b or Point2D()
p = {}
setmetatable(p,LineSegment2D)
LineSegment2D.__index = LineSegment2D
p.pointA = a
p.pointB = b
p.className = "LineSegment2D"
return p
end

setmetatable(LineSegment2D,LineSegment2D.mt)

--Creation with new
function LineSegment2D:new(a,b)
a = a or Point2D() 
b = b or Point2D()
p = {}
setmetatable(p,self)
self.__index = self
p.point = a
p.direction = b
p.pointA = a
p.pointB = b
p.className = "LineSegment2D"
return p
end

-- this is used by C++ to create a lua LineSegment2D
function CreateLineSegment2D()
local pt = LineSegment2D()
return pt
end


----------------------------------------------------------------------------
--Ray2D
----------------------------------------------------------------------------
Ray2D= {point = Point2D(),
		  direction = Vector2D(),
		  className = "Ray2D"}
Ray2D.mt = {}

--Creation by Constructor simulation
Ray2D.mt.__call = function(caller,pt,v)
pt = pt or Point2D() 
v = v or Vector2D()
p = {}
setmetatable(p,Ray2D)
Ray2D.__index = Ray2D
p.point = pt
p.direction = v
p.className = "Ray2D"
return p
end

setmetatable(Ray2D,Ray2D.mt)

--Creation with new
function Ray2D:new(pt,v)
pt = pt or Point2D() 
v = v or Vector2D()
p = {}
setmetatable(p,self)
self.__index = self
p.point = pt
p.direction = v
p.className = "Ray2D"
return p
end

-- this is used by C++ to create a lua Ray2D
function CreateRay2D()
local pt = Ray2D()
return pt
end