----------------------------------------------------------------------------
--Matrix3x3
----------------------------------------------------------------------------
Matrix3x3= {Ma00 = 1.0,
		    Ma01 = 0.0,
		    Ma02 = 0.0,
		    Ma10 = 0.0,
		    Ma11 = 1.0,
		    Ma12 = 0.0,
		    Ma20 = 0.0,
		    Ma21 = 0.0,
		    Ma22 = 1.0,	
		    className = "Matrix3x3"}
Matrix3x3.mt = {}

--Creation by Constructor simulation
Matrix3x3.mt.__call = function(caller)
p = {}
setmetatable(p,Matrix3x3)
Matrix3x3.__index = Matrix3x3
p.Ma00 = 1.0
p.Ma01 = 0.0
p.Ma02 = 0.0
p.Ma10 = 0.0
p.Ma11 = 1.0
p.Ma12 = 0.0
p.Ma20 = 0.0
p.Ma21 = 0.0
p.Ma22 = 1.0
p.className = "Matrix3x3"
return p
end

setmetatable(Matrix3x3,Matrix3x3.mt)

--Creation with new
function Matrix3x3:new()
p = {}
setmetatable(p,self)
self.__index = self
p.Ma00 = 1.0
p.Ma01 = 0.0
p.Ma02 = 0.0
p.Ma10 = 0.0
p.Ma11 = 1.0
p.Ma12 = 0.0
p.Ma20 = 0.0
p.Ma21 = 0.0
p.Ma22 = 1.0
p.className = "Matrix3x3"
return p
end

Matrix3x3.__add = function(a,b)
local pr = Matrix3x3()
pr.Ma00 = a.Ma00 + b.Ma00
pr.Ma01 = a.Ma01 + b.Ma01
pr.Ma02 = a.Ma02 + b.Ma02
pr.Ma10 = a.Ma10 + b.Ma10
pr.Ma11 = a.Ma11 + b.Ma11
pr.Ma12 = a.Ma12 + b.Ma12
pr.Ma20 = a.Ma20 + b.Ma20
pr.Ma21 = a.Ma21 + b.Ma21
return pr
end

Matrix3x3.__sub = function(a,b)
local pr = Matrix3x3()
pr.Ma00 = a.Ma00 - b.Ma00
pr.Ma01 = a.Ma01 - b.Ma01
pr.Ma02 = a.Ma02 - b.Ma02
pr.Ma10 = a.Ma10 - b.Ma10
pr.Ma11 = a.Ma11 - b.Ma11
pr.Ma12 = a.Ma12 - b.Ma12
pr.Ma20 = a.Ma20 - b.Ma20
pr.Ma21 = a.Ma21 - b.Ma21
return pr
end


Matrix3x3.__mul = function(a,m)
local mt = Matrix3x3()
mt.Ma00 = a.Ma00*m.Ma00 + a.Ma01*m.Ma10 + a.Ma02*m.Ma20
mt.Ma01 = a.Ma00*m.Ma01 + a.Ma01*m.Ma11 + a.Ma02*m.Ma21
mt.Ma02 = a.Ma00*m.Ma02 + a.Ma01*m.Ma12 + a.Ma02*m.Ma22
mt.Ma10 = a.Ma10*m.Ma00 + a.Ma11*m.Ma10 + a.Ma12*m.Ma20
mt.Ma11 = a.Ma10*m.Ma01 + a.Ma11*m.Ma11 + a.Ma12*m.Ma21
mt.Ma12 = a.Ma10*m.Ma02 + a.Ma11*m.Ma12 + a.Ma12*m.Ma22
mt.Ma20 = a.Ma20*m.Ma00 + a.Ma21*m.Ma10 + a.Ma22*m.Ma20
mt.Ma21 = a.Ma20*m.Ma01 + a.Ma21*m.Ma11 + a.Ma22*m.Ma21
mt.Ma22 = a.Ma20*m.Ma02 + a.Ma21*m.Ma12 + a.Ma22*m.Ma22
return mt
end

Matrix3x3.__eq = function(a,b)
return (a.Ma00 == b.Ma00) and
	   (a.Ma01 == b.Ma01) and
	   (a.Ma02 == b.Ma02) and
	   (a.Ma10 == b.Ma10) and
	   (a.Ma11 == b.Ma11) and
	   (a.Ma12 == b.Ma12) and
	   (a.Ma20 == b.Ma20) and
	   (a.Ma21 == b.Ma21)
end


function Matrix3x3:Clear()
self.Ma00 = 0.0
self.Ma01 = 0.0
self.Ma02 = 0.0
self.Ma10 = 0.0
self.Ma11 = 0.0
self.Ma12 = 0.0
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = 0.0
end

function Matrix3x3:SetScale(sx,sy)
self.Ma00 = sx
self.Ma01 = 0.0
self.Ma02 = 0.0
self.Ma10 = 0.0
self.Ma11 = sy
self.Ma12 = 0.0
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = 1.0
end

function Matrix3x3:SetTranslate(tx,ty)
self.Ma00 = 1.0
self.Ma01 = 0.0
self.Ma02 = tx
self.Ma10 = 0.0
self.Ma11 = 1.0
self.Ma12 = ty
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = 1.0	
end

function Matrix3x3:SetRotateOnZ(angle)
angle = angle*PIOVER180
self.Ma00 = math.cos(angle)
self.Ma01 = -math.sin(angle)
self.Ma02 = 0.0
self.Ma10 = math.sin(angle)
self.Ma11 = math.cos(angle)
self.Ma12 = 0.0
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = 1.0
end

function Matrix3x3:SetInverse2x2()
	det = self:GetDeterminant2x2()
	if((det <= -FUN_EPSILON) or (det >=FUN_EPSILON))
	then
		inv = Matrix3x3()
		onedet = (1/det)
		inv.Ma00 = onedet * self.Ma11
		inv.Ma01 = onedet * -self.Ma01
		inv.Ma02 = onedet * 0.0
		inv.Ma10 = onedet * -self.Ma10
		inv.Ma11 = onedet * self.Ma00
		inv.Ma12 = 0.0
		inv.Ma20 = 0.0
		inv.Ma21 = 0.0
		inv.Ma22 = onedet
		self:CopyValues(inv)
	end
end

function Matrix3x3:SetInverse3x3()
	det = self:GetDeterminant3x3()
	if((det <= -FUN_EPSILON) or (det >=FUN_EPSILON))
	then
		inv = Matrix3x3()
		onedet = (1/det)
		inv.Ma00 = onedet * (self.Ma11*self.Ma22 - self.Ma12*self.Ma21)
		inv.Ma01 = onedet * (self.Ma02*self.Ma21 - self.Ma01*self.Ma22)
		inv.Ma02 = onedet * (self.Ma01*self.Ma12 - self.Ma02*self.Ma11)
		inv.Ma10 = onedet * (self.Ma12*self.Ma20 - self.Ma10*self.Ma22)
		inv.Ma11 = onedet * (self.Ma00*self.Ma22 - self.Ma02*self.Ma20)
		inv.Ma12 = onedet * (self.Ma02*self.Ma10 - self.Ma00*self.Ma12)
		inv.Ma20 = onedet * (self.Ma10*self.Ma21 - self.Ma11*self.Ma20)
		inv.Ma21 = onedet * (self.Ma01*self.Ma20 - self.Ma00*self.Ma21)
		inv.Ma22 = onedet * (self.Ma00*self.Ma11 - self.Ma01*self.Ma10)
		self:CopyValues(inv)
	end
end

function Matrix3x3:SetIdentity()
self.Ma00 = 1.0
self.Ma01 = 0.0
self.Ma02 = 0.0
self.Ma10 = 0.0
self.Ma11 = 1.0
self.Ma12 = 0.0
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = 1.0
end

function Matrix3x3:SetTranspose()
temp = Matrix3x3()
temp.Ma00 = self.Ma00
temp.Ma01 = self.Ma10
temp.Ma02 = self.Ma20
temp.Ma10 = self.Ma01
temp.Ma11 = self.Ma11
temp.Ma12 = self.Ma21
temp.Ma20 = self.Ma02
temp.Ma21 = self.Ma12
temp.Ma22 = self.Ma22
self:CopyValues(temp)
end

function Matrix3x3:GetDeterminant2x2()
return self.Ma00*self.Ma11 - self.Ma10*self.Ma01
end

function Matrix3x3:GetDeterminant3x3()
return  self.Ma00*(self.Ma11*self.Ma22 - self.Ma12*self.Ma21) - 
		self.Ma01*(self.Ma10*self.Ma22 - self.Ma12*self.Ma20) + 
		self.Ma02*(self.Ma10*self.Ma21 - self.Ma11*self.Ma20)
end

function Matrix3x3:CopyValues(m)
self.Ma00 = m.Ma00 
self.Ma01 = m.Ma01 
self.Ma02 = m.Ma02 
self.Ma10 = m.Ma10 
self.Ma11 = m.Ma11 
self.Ma12 = m.Ma12 
self.Ma20 = m.Ma20 
self.Ma21 = m.Ma21 
self.Ma22 = m.Ma22 
end

function Matrix3x3:SetOpposite()
	det = self:GetDeterminant2x2()
	if((det <= -FUN_EPSILON) or (det >=FUN_EPSILON))
	then
		oneDet = 1/det
		temp = Matrix3x3()
		temp.Ma00 = oneDet * self.Ma11
		temp.Ma01 = oneDet * -self.Ma01
		temp.Ma02 = 0.0
		temp.Ma10 = oneDet * -self.Ma10
		temp.Ma11 = oneDet * self.Ma00
		temp.Ma12 = 0.0
		temp.Ma20 = 0.0
		temp.Ma21 = 0.0
		temp.Ma22 = oneDet
		self:CopyValues(temp)
	end
end

-- this is used by C++ to create a lua Matrix3x3
function CreateMatrix3x3()
local pt = Matrix3x3()
return pt
end