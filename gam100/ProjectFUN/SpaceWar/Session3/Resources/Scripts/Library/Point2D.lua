--Point2D Class (table)
Point2D = {X = 0,Y = 0, className = "Point2D"}
--Point2D Class Metatable
Point2D.mt = {}

--Creation by Constructor simulation
Point2D.mt.__call = function(caller,x,y)
x = x or 0 --set x to 0 if it is nil
y = y or 0 --set y to 0 if it is nil
p = {}
setmetatable(p,Point2D)
Point2D.__index = Point2D
p.X = x
p.Y = y
p.className = "Point2D"
return p
end
setmetatable(Point2D,Point2D.mt)

--Creation with new
function Point2D:new(x,y)
x = x or 0 --set x to 0 if it is nil
y = y or 0 --set y to 0 if it is nil
p = {}
setmetatable(p,self)
self.__index = self
p.X = x
p.Y = y
p.className = "Point2D"
return p
end

--Addition overload (adding two Point2Ds)
Point2D.__add = function(a,b)
local pr = Point2D()
pr.X = a.X + b.X
pr.Y = a.Y + b.Y
return pr
end

--Substraction overload
Point2D.__sub = function(a,b)
local pr = Vector2D()
pr.X = a.X - b.X
pr.Y = a.Y - b.Y
return pr
end

--Point2D * number overload
Point2D.__mul = function(a,b)
local pr = Point2D()
pr.X = a.X * b
pr.Y = a.Y * b
return pr
end

--Point2D / number number overload
Point2D.__div = function(a,b)
local pr = Point2D()
pr.X = a.X / b
pr.Y = a.Y / b
return pr
end

--comparing 2 Point2Ds
Point2D.__eq = function(a,b)
if(a.X == b.X and a.Y == b.Y) then return true end
return false
end

function Point2D:Clear()
	self.X = 0
	self.Y = 0
end

function Point2D:GetNormal()
local pr = Point2D()
pr.X = -self.Y
pr.Y = self.X
return pr
end

function Point2D:GetReflectedVector(vn)
	local rv = Point2D();
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

function Point2D:ClassifyToCircle(cir)
	center = cir:GetCenter()
	radius = cir:GetRadius()
	d = math.sqrt((self.X-center.X)*(self.X-center.X) + (self.Y-center.Y)*(self.Y-center.Y))
	if(d > radius) then
		return CLASSIFY.OUTSIDE
	elseif(d < radius) then
		return CLASSIFY.INSIDE
	end
	return CLASSIFY.INTERSECT
end

function Point2D:ClassifyToLine(lin)
	direction = lin:GetDirection()
	point = lin:GetPoint()
	cross = direction.X*(self.Y - point.Y) - direction.Y*(self.X - point.X)
	if(cross < 0.0) then
		return CLASSIFY.RIGHT
	elseif(cross > 0.0) then
		return CLASSIFY.LEFT
	end
	return CLASSIFY.INTERSECT
end

function Point2D:ClassifyToLineSegment(lns)
	pointA = lns:GetPointA()
	pointB = lns:GetPointB()
	res1 = pointB.Y - pointA.Y
	res2 = pointB.X - pointA.X
	res3 = self.X - pointA.X
	res4 = self.Y - pointA.Y
	t = 0
	if(res3*res1 == res4*res2)--the point is on the line of the segment
	then		
		if((res1<= -FUN_EPSILON) or (res1 >=FUN_EPSILON)) then
			t = res4/res1
		else 
			t = res3/res2
		end
		
		if(t < 0.0) then
			return CLASSIFY.BEHIND
		elseif(t > 1.0) then
			return CLASSIFY.BEYOND
		elseif((t > 0.0) and (t < 1.0)) then
			return CLASSIFY.INTERSECT
		elseif(t == 0.0) then
			return CLASSIFY.INTERSECT_A
		elseif(t == 1.0) then
			return CLASSIFY.INTERSECT_B
		end
	else --aside
		t = res2*res4 - res3*res1
		if(t > 0.0) then
			return CLASSIFY.LEFT
		elseif(t < 0.0) then
			return CLASSIFY.RIGHT	
		end	
	end
	--never reached
	return CLASSIFY.INTERSECT
end

function Point2D:GetLength()
	return math.sqrt(self.X*self.X + self.Y*self.Y)
end

function Point2D:Distance(pnt)
	return math.sqrt((self.X-pnt.X)*(self.X-pnt.X) + (self.Y-pnt.Y)*(self.Y-pnt.Y))
end

function Point2D:ClassifyToRay(ray)
	direction = ray:GetDirection()
	origin = ray:GetOrigin()
	res1 = (self.X - origin.X)*direction.Y
	res2 = (self.Y - origin.Y)*direction.X

	if(res1 == res2)--point is on the line of the ray
	then
		t = 0
		if((direction.X<= -FUN_EPSILON) or (direction.X >=FUN_EPSILON))
		then
			t = (self.X - origin.X)/direction.X
			if(t < 0.0) then
				return CLASSIFY.BEHIND
			elseif(t > 0.0) then
				return CLASSIFY.INTERSECT
			else
				return CLASSIFY.INTERSECT_ORIGIN
			end
		else
			t = (Y - origin.Y)/direction.Y
			if(t < 0.0) then
				return CLASSIFY.BEHIND
			elseif(t > 0.0) then
				return CLASSIFY.INTERSECT
			else
				return CLASSIFY.INTERSECT_ORIGIN
			end
		end
	else
		--this formulas is gettin from cross product
		cross = direction.X*(self.Y - origin.Y) - 
				direction.Y*(self.X - origin.X)

		if(cross < 0.0) then
			return CLASSIFY.RIGHT
		elseif(cross > 0.0) then
			return CLASSIFY.LEFT
		else
			return CLASSIFY.INTERSECT
		end
	end
end



function Point2D:GetDotProduct(v)
	return self.X*v.X + self.Y*v.Y
end

function Point2D:PointInsideCircle(cir, error_value)
	radius = cir:GetRadius()
	center = cir:GetCenter()
	d = math.sqrt((self.X-center.X)*(self.X-center.X) + (self.Y-center.Y)*(self.Y-center.Y))
	return d <= (radius + error_value)
end

function Point2D:PointOnCircle(cir)
	radius = cir:GetRadius()
	center = cir:GetCenter()
	d = math.sqrt((self.X-center.X)*(self.X-center.X) + (self.Y-center.Y)*(self.Y-center.Y))
	return d == radius
end

function Point2D:PointOnLine(lin)
	point = lin:GetPoint()
	direction = lin:GetDirection()
	cross = direction.X*(self.Y - point.Y) - direction.Y*(self.X - point.X)
	return ((cross >= -FUN_EPSILON) and (cross <=FUN_EPSILON))
end

function Equal(f1, f2 , approximation)
		if((f1 >= (f2 - approximation)) and (f1 <= (f2 + approximation))) then
			return true
		end
		return false
end
	
function Point2D:PointOnLineSegment(lns)
		pointA = lns:GetPointA()
		pointB = lns:GetPointB()
		res1 = pointB.Y - pointA.Y
		res2 = pointB.X - pointA.X
		res3 = self.X - pointA.X
		res4 = self.Y - pointA.Y
		t = 0
		if(Equal(res3*res1,res4*res2,1.2))
		then	
			if((res1 <= -FUN_EPSILON) or (res1 >= FUN_EPSILON)) then
				t = res4/res1
			else
				t = res3/res2
			end
			
			if((t >= 0.0) and (t <= 1.0)) then
				return true
			end
		end
		return false
end

function Point2D:PointOnRay(ray)
	direction = ray:GetDirection()
	origin = ray:GetOrigin()
	if(((self.X - origin.X)*direction.Y) == ((self.Y - origin.Y)*direction.X))	
	then
		t = 0
		if((direction.X<= -FUN_EPSILON) or (direction.X >=FUN_EPSILON))
		then
			t = (self.X - origin.X)/direction.X
			if(t > 0.0) then
				return true	
			end		
		else
			t = (self.Y - origin.Y)/direction.Y
			if(t > 0.0) then
				return true	
			end		
		end
	end
	
	return false
end
	

function Point2D:PointOutsideCircle(cir)
    radius = cir:GetRadius()
    center = cir:GetCenter()
	d = math.sqrt((self.X-center.X)*(self.X-center.X) + (self.Y-center.Y)*(self.Y-center.Y))
	return d > radius
end

function Point2D:PointOutsideLine(lin)
	direction = lin:GetDirection()
	point = lin:GetPoint()
	cross = direction.X*(self.Y - point.Y) - direction.Y*(self.X - point.X)
	return ((cross <= -FUN_EPSILON) or (cross >=FUN_EPSILON))
end

function Point2D:ProjectionOnCircle(cir)
	local pro = Point2D()
	radius = cir:GetRadius()
    center = cir:GetCenter()
	deno = self.X*self.X - 2*self.X*center.X + center.X*center.X + self.Y*self.Y - 2*self.Y*center.Y + center.Y*center.Y
	t = radius / math.sqrt(deno)
	pro.X = (self.X - center.X)*t + center.X
	pro.Y = (self.Y - center.Y)*t + center.Y
	return pro,math.sqrt((self.X-pro.X)*(self.X-pro.X) + (self.Y-pro.Y)*(self.Y-pro.Y))
end

function Point2D:ProjectionOnLine(lin,pro)
	direction = lin:GetDirection()
	point = lin:GetPoint()
	temp1 = direction.X*direction.X + direction.Y*direction.Y
	temp2 = direction.X*(self.X - point.X) + direction.Y*(self.Y - point.Y)
	local pro = Point2D()
	pro.X = (direction.X/temp1)*temp2 + point.X
	pro.Y = (direction.Y/temp1)*temp2 + point.Y
	return pro,math.sqrt((self.X-pro.X)*(self.X-pro.X) + (self.Y-pro.Y)*(self.Y-pro.Y))
end


function Point2D:ProjectionOnLineSegment(lns)
	pointA = lns:GetPointA()
	pointB = lns:GetPointB()
	local pro = Point2D()
	lnsdirX = pointB.X - pointA.X
	lnsdirY = pointB.Y - pointA.Y

	temp1 = lnsdirX*lnsdirX + lnsdirY*lnsdirY
	temp2 = lnsdirX*(self.X - pointA.X) + lnsdirY*(self.Y - pointA.Y)

	pro.X = (lnsdirX/temp1)*temp2 + pointA.X
	pro.Y = (lnsdirY/temp1)*temp2 + pointA.Y

	res1 = pointB.Y - pointA.Y
	t = 0
		
	if((res1<= -FUN_EPSILON) or (res1 >=FUN_EPSILON)) then
		t = (pro.Y - pointA.Y)/res1
	else 
		t = (pro.X - pointA.X)/(pointB.X - pointA.X)
	end
	
	onlinesegment = false
	
	if((t >= 0.0) and (t <= 1.0)) then
		onlinesegment = true
	end
	
	return pro,math.sqrt((self.X - pro.X)*(self.X - pro.X) + (self.Y - pro.Y)*(self.Y - pro.Y)),onlinesegment
end

function Point2D:ProjectionOnRay(ray)
	direction = ray:GetDirection()
	origin = ray:GetOrigin()
	temp1 = direction.X*direction.X + direction.Y*direction.Y
	temp2 = direction.X*(self.X - origin.X) + direction.Y*(self.Y - origin.Y)
	local pro = Point2D()
	pro.X = (direction.X/temp1)*temp2 + origin.X
	pro.Y = (direction.Y/temp1)*temp2 + origin.Y

	t = 0
	onray = false
	if((direction.X<= -FUN_EPSILON) or (direction.X >=FUN_EPSILON))
	then
		t = (pro.X - origin.X)/direction.X
		if(t > 0.0) then
			onray = true
		else
			onray = false
		end
	else	
		t = (pro.Y - origin.Y)/direction.Y
		if(t > 0.0) then
			onray = true
		else
			onray = false
		end
	end

	return pro, math.sqrt((self.X - pro.X)*(self.X - pro.X) + (self.Y - pro.Y)*(self.Y - pro.Y)), onray
end


function Point2D:Rotate(angle)
COS = math.cos(angle * PIOVER180);
SIN = math.sin(angle * PIOVER180);
X1 = (self.X*COS - self.Y*SIN);
Y1 = (self.Y*COS + self.X*SIN);
self.X = X1;
self.Y = Y1;
end

function Point2D:Scale(x,y)
self.X = self.X * x
self.Y = self.Y * y
end

-- this is used by C++ to create a lua Point2D
function CreatePoint()
local pt = Point2D()
return pt
end