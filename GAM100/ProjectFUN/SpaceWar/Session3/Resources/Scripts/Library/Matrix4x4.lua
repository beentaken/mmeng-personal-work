----------------------------------------------------------------------------
--Matrix4x4
----------------------------------------------------------------------------
Matrix4x4= {Ma00 = 1.0,
			Ma01 = 0.0,
			Ma02 = 0.0,
			Ma03 = 0.0,
			Ma10 = 0.0,
			Ma11 = 1.0,
			Ma12 = 0.0,
			Ma13 = 0.0,
			Ma20 = 0.0,
			Ma21 = 0.0,
			Ma22 = 1.0,
			Ma23 = 0.0,
			Ma30 = 0.0,
			Ma31 = 0.0,
			Ma32 = 0.0,
			Ma33 = 1.0,
		    className = "Matrix4x4"}
Matrix4x4.mt = {}

--Creation by Constructor simulation
Matrix4x4.mt.__call = function(caller)
p = {}
setmetatable(p,Matrix4x4)
Matrix4x4.__index = Matrix4x4
p.Ma00 = 1.0
p.Ma01 = 0.0
p.Ma02 = 0.0
p.Ma03 = 0.0
p.Ma10 = 0.0
p.Ma11 = 1.0
p.Ma12 = 0.0
p.Ma13 = 0.0
p.Ma20 = 0.0
p.Ma21 = 0.0
p.Ma22 = 1.0
p.Ma23 = 0.0
p.Ma30 = 0.0
p.Ma31 = 0.0
p.Ma32 = 0.0
p.Ma33 = 1.0
p.className = "Matrix4x4"
return p
end

setmetatable(Matrix4x4,Matrix4x4.mt)

--Creation with new
function Matrix4x4:new()
p = {}
setmetatable(p,self)
self.__index = self
p.Ma00 = 1.0
p.Ma01 = 0.0
p.Ma02 = 0.0
p.Ma03 = 0.0
p.Ma10 = 0.0
p.Ma11 = 1.0
p.Ma12 = 0.0
p.Ma13 = 0.0
p.Ma20 = 0.0
p.Ma21 = 0.0
p.Ma22 = 1.0
p.Ma23 = 0.0
p.Ma30 = 0.0
p.Ma31 = 0.0
p.Ma32 = 0.0
p.Ma33 = 1.0
p.className = "Matrix4x4"
return p
end

Matrix4x4.__add = function(a,m)
local mt = Matrix4x4()
mt.Ma00 = a.Ma00 + m.Ma00
mt.Ma01 = a.Ma01 + m.Ma01
mt.Ma02 = a.Ma02 + m.Ma02
mt.Ma03 = a.Ma03 + m.Ma03
mt.Ma10 = a.Ma10 + m.Ma10
mt.Ma11 = a.Ma11 + m.Ma11
mt.Ma12 = a.Ma12 + m.Ma12
mt.Ma13 = a.Ma13 + m.Ma13
mt.Ma20 = a.Ma20 + m.Ma20
mt.Ma21 = a.Ma21 + m.Ma21
mt.Ma22 = a.Ma22 + m.Ma22
mt.Ma23 = a.Ma23 + m.Ma23
mt.Ma30 = a.Ma30 + m.Ma30
mt.Ma31 = a.Ma31 + m.Ma31
mt.Ma32 = a.Ma32 + m.Ma32
mt.Ma33 = a.Ma33 + m.Ma33
return mt
end

Matrix4x4.__sub = function(a,m)
local mt = Matrix4x4()
mt.Ma00 = a.Ma00 - m.Ma00
mt.Ma01 = a.Ma01 - m.Ma01
mt.Ma02 = a.Ma02 - m.Ma02
mt.Ma03 = a.Ma03 - m.Ma03
mt.Ma10 = a.Ma10 - m.Ma10
mt.Ma11 = a.Ma11 - m.Ma11
mt.Ma12 = a.Ma12 - m.Ma12
mt.Ma13 = a.Ma13 - m.Ma13
mt.Ma20 = a.Ma20 - m.Ma20
mt.Ma21 = a.Ma21 - m.Ma21
mt.Ma22 = a.Ma22 - m.Ma22
mt.Ma23 = a.Ma23 - m.Ma23
mt.Ma30 = a.Ma30 - m.Ma30
mt.Ma31 = a.Ma31 - m.Ma31
mt.Ma32 = a.Ma32 - m.Ma32
mt.Ma33 = a.Ma33 - m.Ma33
return mt
end


Matrix4x4.__mul = function(a,m)
local mt = Matrix4x4()
mt.Ma00 = a.Ma00*m.Ma00 + a.Ma01*m.Ma10 + a.Ma02*m.Ma20 + a.Ma03*m.Ma30
mt.Ma01 = a.Ma00*m.Ma01 + a.Ma01*m.Ma11 + a.Ma02*m.Ma21 + a.Ma03*m.Ma31
mt.Ma02 = a.Ma00*m.Ma02 + a.Ma01*m.Ma12 + a.Ma02*m.Ma22 + a.Ma03*m.Ma32
mt.Ma03 = a.Ma00*m.Ma03 + a.Ma01*m.Ma13 + a.Ma02*m.Ma23 + a.Ma03*m.Ma33
mt.Ma10 = a.Ma10*m.Ma00 + a.Ma11*m.Ma10 + a.Ma12*m.Ma20 + a.Ma13*m.Ma30
mt.Ma11 = a.Ma10*m.Ma01 + a.Ma11*m.Ma11 + a.Ma12*m.Ma21 + a.Ma13*m.Ma31
mt.Ma12 = a.Ma10*m.Ma02 + a.Ma11*m.Ma12 + a.Ma12*m.Ma22 + a.Ma13*m.Ma32
mt.Ma13 = a.Ma10*m.Ma03 + a.Ma11*m.Ma13 + a.Ma12*m.Ma23 + a.Ma13*m.Ma33
mt.Ma20 = a.Ma20*m.Ma00 + a.Ma21*m.Ma10 + a.Ma22*m.Ma20 + a.Ma23*m.Ma30
mt.Ma21 = a.Ma20*m.Ma01 + a.Ma21*m.Ma11 + a.Ma22*m.Ma21 + a.Ma23*m.Ma31
mt.Ma22 = a.Ma20*m.Ma02 + a.Ma21*m.Ma12 + a.Ma22*m.Ma22 + a.Ma23*m.Ma32
mt.Ma23 = a.Ma20*m.Ma03 + a.Ma21*m.Ma13 + a.Ma22*m.Ma23 + a.Ma23*m.Ma33
mt.Ma30 = a.Ma30*m.Ma00 + a.Ma31*m.Ma10 + a.Ma32*m.Ma20 + a.Ma33*m.Ma30
mt.Ma31 = a.Ma30*m.Ma01 + a.Ma31*m.Ma11 + a.Ma32*m.Ma21 + a.Ma33*m.Ma31
mt.Ma32 = a.Ma30*m.Ma02 + a.Ma31*m.Ma12 + a.Ma32*m.Ma22 + a.Ma33*m.Ma32
mt.Ma33 = a.Ma30*m.Ma03 + a.Ma31*m.Ma13 + a.Ma32*m.Ma23 + a.Ma33*m.Ma33
return mt
end

Matrix4x4.__eq = function(a,b)
return  (a.Ma00 == b.Ma00) and
		(a.Ma01 == b.Ma01) and
		(a.Ma02 == b.Ma02) and
		(a.Ma03 == b.Ma03) and
		(a.Ma10 == b.Ma10) and
		(a.Ma11 == b.Ma11) and
		(a.Ma12 == b.Ma12) and
		(a.Ma13 == b.Ma13) and
		(a.Ma20 == b.Ma20) and
		(a.Ma21 == b.Ma21) and
		(a.Ma22 == b.Ma22) and
		(a.Ma23 == b.Ma23) and
		(a.Ma30 == b.Ma30) and
		(a.Ma31 == b.Ma31) and
		(a.Ma32 == b.Ma32) and
		(a.Ma33 == b.Ma33)
end

--todo: no Point3D yet!
function Matrix4x4:Tensor(p)
end

function Matrix4x4:GetTrace()
return self.Ma00 + self.Ma11 + self.Ma22 + self.Ma33
end

function Matrix4x4:SetRotateOnX(angle)
angle = angle*PIOVER180
self.Ma00 = 1.0
self.Ma01 = 0.0
self.Ma02 = 0.0
self.Ma03 = 0.0
self.Ma10 = 0.0
self.Ma11 = math.cos(angle)
self.Ma12 = -math.sin(angle)
self.Ma13 = 0.0
self.Ma20 = 0.0
self.Ma21 = math.sin(angle)
self.Ma22 = math.cos(angle)
self.Ma23 = 0.0
self.Ma30 = 0.0
self.Ma31 = 0.0
self.Ma32 = 0.0
self.Ma33 = 1.0
end


function Matrix4x4:SetRotateOnY(angle)
angle = angle*PIOVER180
self.Ma00 = math.cos(angle)
self.Ma01 = 0.0
self.Ma02 = math.sin(angle)
self.Ma03 = 0.0
self.Ma10 = 0.0
self.Ma11 = 1.0
self.Ma12 = 0.0
self.Ma13 = 0.0
self.Ma20 = -math.sin(angle)
self.Ma21 = 0.0
self.Ma22 = math.cos(angle)
self.Ma23 = 0.0
self.Ma30 = 0.0
self.Ma31 = 0.0
self.Ma32 = 0.0
self.Ma33 = 1.0	
end

--todo no Vector3D yet!
function Matrix4x4:SetRotateArbitraryAxis(ax,angle)
end

function Matrix4x4:SetInverseScale(sx,sy,sz)
	if((sx <= -FUN_EPSILON) or (sx >=FUN_EPSILON))
	then
		self.Ma00 = 1.0/sx
	else self.Ma00 = 1.0
	end

	self.Ma01 = 0.0
	self.Ma02 = 0.0
	self.Ma03 = 0.0
	self.Ma10 = 0.0
	if((sy <= -FUN_EPSILON) or (sy >=FUN_EPSILON))
	then
		self.Ma11 = 1.0/sy
	else
		self.Ma11 = 1.0
	end

	self.Ma12 = 0.0
	self.Ma13 = 0.0
	self.Ma20 = 0.0
	self.Ma21 = 0.0

	if((sz <= -FUN_EPSILON) or (sz >=FUN_EPSILON))
	then
		self.Ma22 = 1.0/sz
	else self.Ma22 = 1.0
	end

	self.Ma23 = 0.0
	self.Ma30 = 0.0
	self.Ma31 = 0.0
	self.Ma32 = 0.0
	self.Ma33 = 1.0	
end

function Matrix4x4:SetInverseTranslate(tx,ty,tz)
		self.Ma00 = 1.0
		self.Ma01 = 0.0
		self.Ma02 = 0.0
		self.Ma03 = -tx
		self.Ma10 = 0.0
		self.Ma11 = 1.0
		self.Ma12 = 0.0
		self.Ma13 = -ty
		self.Ma20 = 0.0
		self.Ma21 = 0.0
		self.Ma22 = 1.0
		self.Ma23 = -tz
		self.Ma30 = 0.0
		self.Ma31 = 0.0
		self.Ma32 = 0.0
		self.Ma33 = 1.0
end

function Matrix4x4:SetInverseRotateOnX(angle)
	angle = angle*PIOVER180
	self.Ma00 = 1.0
	self.Ma01 = 0.0
	self.Ma02 = 0.0
	self.Ma03 = 0.0
	self.Ma10 = 0.0
	self.Ma11 = math.cos(angle)
	self.Ma12 = math.sin(angle)
	self.Ma13 = 0.0
	self.Ma20 = 0.0
	self.Ma21 = -math.sin(angle)
	self.Ma22 = math.cos(angle)
	self.Ma23 = 0.0
	self.Ma30 = 0.0
	self.Ma31 = 0.0
	self.Ma32 = 0.0
	self.Ma33 = 1.0
end

function Matrix4x4:SetInverseRotateOnY(angle)
	angle = angle*PIOVER180
	self.Ma00 = math.cos(angle)
	self.Ma01 = 0.0
	self.Ma02 = -math.sin(angle)
	self.Ma03 = 0.0
	self.Ma10 = 0.0
	self.Ma11 = 1.0
	self.Ma12 = 0.0
	self.Ma13 = 0.0
	self.Ma20 = math.sin(angle)
	self.Ma21 = 0.0
	self.Ma22 = math.cos(angle)
	self.Ma23 = 0.0
	self.Ma30 = 0.0
	self.Ma31 = 0.0
	self.Ma32 = 0.0
	self.Ma33 = 1.0
end

function Matrix4x4:SetInverseRotateOnZ(angle)
	angle = angle*PIOVER180
	self.Ma00 = math.cos(angle)
	self.Ma01 = math.sin(angle)
	self.Ma02 = 0.0
	self.Ma03 = 0.0
	self.Ma10 = -math.sin(angle)
	self.Ma11 = math.cos(angle)
	self.Ma12 = 0.0
	self.Ma13 = 0.0
	self.Ma20 = 0.0
	self.Ma21 = 0.0
	self.Ma22 = 1.0
	self.Ma23 = 0.0
	self.Ma30 = 0.0
	self.Ma31 = 0.0
	self.Ma32 = 0.0
	self.Ma33 = 1.0
end

function Matrix4x4:SetInverse4x4()
	transtemp = Matrix4x4()
	temp = Matrix4x4()
	temp.Ma00 = self.Ma11
	temp.Ma01 = self.Ma12
	temp.Ma02 = self.Ma13
	temp.Ma10 = self.Ma21
	temp.Ma11 = self.Ma22
	temp.Ma12 = self.Ma23
	temp.Ma20 = self.Ma31
	temp.Ma21 = self.Ma32
	temp.Ma22 = self.Ma33
	transtemp.Ma00 = temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma10
	temp.Ma01 = self.Ma12
	temp.Ma02 = self.Ma13
	temp.Ma10 = self.Ma20
	temp.Ma11 = self.Ma22
	temp.Ma12 = self.Ma23
	temp.Ma20 = self.Ma30
	temp.Ma21 = self.Ma32
	temp.Ma22 = self.Ma33
	transtemp.Ma01 = -temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma10
	temp.Ma01 = self.Ma11
	temp.Ma02 = self.Ma13
	temp.Ma10 = self.Ma20
	temp.Ma11 = self.Ma21
	temp.Ma12 = self.Ma23
	temp.Ma20 = self.Ma30
	temp.Ma21 = self.Ma31
	temp.Ma22 = self.Ma33
	transtemp.Ma02 = temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma10
	temp.Ma01 = self.Ma11
	temp.Ma02 = self.Ma12
	temp.Ma10 = self.Ma20
	temp.Ma11 = self.Ma21
	temp.Ma12 = self.Ma22
	temp.Ma20 = self.Ma30
	temp.Ma21 = self.Ma31
	temp.Ma22 = self.Ma32
	transtemp.Ma03 = -temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma01
	temp.Ma01 = self.Ma02
	temp.Ma02 = self.Ma03
	temp.Ma10 = self.Ma21
	temp.Ma11 = self.Ma22
	temp.Ma12 = self.Ma23
	temp.Ma20 = self.Ma31
	temp.Ma21 = self.Ma32
	temp.Ma22 = self.Ma33
	transtemp.Ma10 = -temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma00
	temp.Ma01 = self.Ma02
	temp.Ma02 = self.Ma03
	temp.Ma10 = self.Ma20
	temp.Ma11 = self.Ma22
	temp.Ma12 = self.Ma23
	temp.Ma20 = self.Ma30
	temp.Ma21 = self.Ma32
	temp.Ma22 = self.Ma33
	transtemp.Ma11 = temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma00
	temp.Ma01 = self.Ma01
	temp.Ma02 = self.Ma03
	temp.Ma10 = self.Ma20
	temp.Ma11 = self.Ma21
	temp.Ma12 = self.Ma23
	temp.Ma20 = self.Ma30
	temp.Ma21 = self.Ma31
	temp.Ma22 = self.Ma33
	transtemp.Ma12 = -temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma00
	temp.Ma01 = self.Ma01
	temp.Ma02 = self.Ma02
	temp.Ma10 = self.Ma20
	temp.Ma11 = self.Ma21
	temp.Ma12 = self.Ma22
	temp.Ma20 = self.Ma30
	temp.Ma21 = self.Ma31
	temp.Ma22 = self.Ma32
	transtemp.Ma13 = temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma01
	temp.Ma01 = self.Ma02
	temp.Ma02 = self.Ma03
	temp.Ma10 = self.Ma11
	temp.Ma11 = self.Ma12
	temp.Ma12 = self.Ma13
	temp.Ma20 = self.Ma31
	temp.Ma21 = self.Ma32
	temp.Ma22 = self.Ma33
	transtemp.Ma20 = temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma00
	temp.Ma01 = self.Ma02
	temp.Ma02 = self.Ma03
	temp.Ma10 = self.Ma10
	temp.Ma11 = self.Ma12
	temp.Ma12 = self.Ma13
	temp.Ma20 = self.Ma30
	temp.Ma21 = self.Ma32
	temp.Ma22 = self.Ma33
	transtemp.Ma21 = -temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma00
	temp.Ma01 = self.Ma01
	temp.Ma02 = self.Ma03
	temp.Ma10 = self.Ma10
	temp.Ma11 = self.Ma11
	temp.Ma12 = self.Ma13
	temp.Ma20 = self.Ma30
	temp.Ma21 = self.Ma31
	temp.Ma22 = self.Ma33
	transtemp.Ma22 = temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma00
	temp.Ma01 = self.Ma01
	temp.Ma02 = self.Ma02
	temp.Ma10 = self.Ma10
	temp.Ma11 = self.Ma11
	temp.Ma12 = self.Ma12
	temp.Ma20 = self.Ma30
	temp.Ma21 = self.Ma31
	temp.Ma22 = self.Ma32
	transtemp.Ma23 = -temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma01
	temp.Ma01 = self.Ma02
	temp.Ma02 = self.Ma03
	temp.Ma10 = self.Ma11
	temp.Ma11 = self.Ma12
	temp.Ma12 = self.Ma13
	temp.Ma20 = self.Ma21
	temp.Ma21 = self.Ma22
	temp.Ma22 = self.Ma23
	transtemp.Ma30 = -temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma00
	temp.Ma01 = self.Ma02
	temp.Ma02 = self.Ma03
	temp.Ma10 = self.Ma10
	temp.Ma11 = self.Ma12
	temp.Ma12 = self.Ma13
	temp.Ma20 = self.Ma20
	temp.Ma21 = self.Ma22
	temp.Ma22 = self.Ma23
	transtemp.Ma31 = temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma00
	temp.Ma01 = self.Ma01
	temp.Ma02 = self.Ma03
	temp.Ma10 = self.Ma10
	temp.Ma11 = self.Ma11
	temp.Ma12 = self.Ma13
	temp.Ma20 = self.Ma20
	temp.Ma21 = self.Ma21
	temp.Ma22 = self.Ma23
	transtemp.Ma32 = -temp:GetDeterminant3x3()

	temp.Ma00 = self.Ma00
	temp.Ma01 = self.Ma01
	temp.Ma02 = self.Ma02
	temp.Ma10 = self.Ma10
	temp.Ma11 = self.Ma11
	temp.Ma12 = self.Ma12
	temp.Ma20 = self.Ma20
	temp.Ma21 = self.Ma21
	temp.Ma22 = self.Ma22
	transtemp.Ma33 = temp:GetDeterminant3x3()
	
	odet = 1/self:GetDeterminant4x4()
	
	transtemp:SetTranspose()
	self:CopyValues(transtemp)
	self.Ma00 = odet * self.Ma00
	self.Ma01 = odet * self.Ma01
	self.Ma02 = odet * self.Ma02
	self.Ma03 = odet * self.Ma03
	self.Ma10 = odet * self.Ma10
	self.Ma11 = odet * self.Ma11
	self.Ma12 = odet * self.Ma12
	self.Ma13 = odet * self.Ma13
	self.Ma20 = odet * self.Ma20
	self.Ma21 = odet * self.Ma21
	self.Ma22 = odet * self.Ma22
	self.Ma23 = odet * self.Ma23
	self.Ma30 = odet * self.Ma30
	self.Ma31 = odet * self.Ma31
	self.Ma32 = odet * self.Ma32
	self.Ma33 = odet * self.Ma33 
end

function Matrix4x4:SetShearing(ind1, ind2, value)
	self:SetIdentity()
	if(ind1==0)
	then
		if(ind2==0)
		then
			self.Ma00 = 1.0
		end
		if(ind2==1)
		then
			self.Ma01 = value
		end
		if(ind2==2)
		then
			self.Ma02 = value
		end
	end
	
	if(ind1==1)
	then
		if(ind2==0)
		then
			self.Ma10 = value
		end
		if(ind2==1)
		then
			self.Ma11 = 1.0
		end
		if(ind2==2)
		then
			self.Ma12 = value
		end
	end
	if(ind1==2)
	then
		if(ind2==0)
		then
			self.Ma20 = value
		end
		if(ind2==1)
		then
			self.Ma21 = value
		end
		if(ind2==2)
		then
			self.Ma22 = 1.0
		end
	end
	
end


function Matrix4x4:GetDeterminant4x4()
	temp1 = Matrix4x4()
	temp1.Ma00 = self.Ma11
	temp1.Ma01 = self.Ma12
	temp1.Ma02 = self.Ma13
	temp1.Ma10 = self.Ma21
	temp1.Ma11 = self.Ma22
	temp1.Ma12 = self.Ma23
	temp1.Ma20 = self.Ma31
	temp1.Ma21 = self.Ma32
	temp1.Ma22 = self.Ma33

	temp2 = Matrix4x4()
	temp2.Ma00 = self.Ma10
	temp2.Ma01 = self.Ma12
	temp2.Ma02 = self.Ma13
	temp2.Ma10 = self.Ma20
	temp2.Ma11 = self.Ma22
	temp2.Ma12 = self.Ma23
	temp2.Ma20 = self.Ma30
	temp2.Ma21 = self.Ma32
	temp2.Ma22 = self.Ma33

	temp3 = Matrix4x4()
	temp3.Ma00 = self.Ma10
	temp3.Ma01 = self.Ma11
	temp3.Ma02 = self.Ma13
	temp3.Ma10 = self.Ma20
	temp3.Ma11 = self.Ma21
	temp3.Ma12 = self.Ma23
	temp3.Ma20 = self.Ma30
	temp3.Ma21 = self.Ma31
	temp3.Ma22 = self.Ma33

	temp4 = Matrix4x4()
	temp4.Ma00 = self.Ma10
	temp4.Ma01 = self.Ma11
	temp4.Ma02 = self.Ma12
	temp4.Ma10 = self.Ma20
	temp4.Ma11 = self.Ma21
	temp4.Ma12 = self.Ma22
	temp4.Ma20 = self.Ma30
	temp4.Ma21 = self.Ma31
	temp4.Ma22 = self.Ma32
	return self.Ma00*temp1:GetDeterminant3x3() - self.Ma01*temp2:GetDeterminant3x3() + self.Ma02*temp3:GetDeterminant3x3() - self.Ma03*temp4:GetDeterminant3x3()
end

--todo : needs Point3D
function Matrix4x4:SetTransformation(scaling,rotation,translation)
end

function Matrix4x4:SetPerspective(half_width, half_height, nearPlane, farPlane)
	self.Ma01 = 0.0
	self.Ma02 = 0.0
	self.Ma03 = 0.0
	self.Ma10 = 0.0
	self.Ma12 = 0.0
	self.Ma13 = 0.0
	self.Ma20 = 0.0
	self.Ma21 = 0.0
	self.Ma30 = 0.0
	self.Ma31 = 0.0

	self.Ma00 = half_height
	self.Ma11 = half_width
	self.Ma22 = (half_height*half_width*farPlane)/(nearPlane*(farPlane - nearPlane))
	self.Ma32 = -(half_height*half_width*farPlane)/(farPlane - nearPlane)
	self.Ma23 = (half_height*half_width)/nearPlane
	self.Ma33 = 0.0
end

function Matrix4x4:SetPerspectiveAsOGL(fieldOfViewY, aspect, nearz, farz)
		if(not aspect) then
			aspect = 1
		end
		fview = fieldOfViewY*PIOVER360
		cot = 1/Math.tan(fview)
		self.Ma00 = cot/aspect
		self.Ma01 = 0.0
		self.Ma02 = 0.0
		self.Ma03 = 0.0
		
		self.Ma10 = 0.0
		self.Ma11 = cot
		self.Ma12 = 0.0
		self.Ma13 = 0.0
		
		self.Ma20 = 0.0
		self.Ma21 = 0.0
		self.Ma22 = (farz+nearz)/(nearz-farz)
		self.Ma23 = (2*farz*nearz)/(nearz-farz)
		
		self.Ma30 = 0.0
		self.Ma31 = 0.0
		self.Ma32 = -1.0
		self.Ma33 = 0.0
end

--todo: needs Point3D
function Matrix4x4:SetLookAt()
end

--todo: needs Point3D
function Matrix4x4:SetLookAtAsOGL()
end

function Matrix4x4:SetFrustumAsOGL(left, right, bottom, top, nearz, farz)
	self.Ma00 = (2*nearz)/(right-left)
	self.Ma01 = 0.0
	self.Ma02 = (right+left)/(right-left)
	self.Ma03 = 0.0
	self.Ma10 = 0.0
	self.Ma11 = (2*nearz)/(top-bottom)
	self.Ma12 = (top+bottom)/(top-bottom)
	self.Ma12 = 0.0
	self.Ma20 = 0.0
	self.Ma21 = 0.0
	self.Ma22 = (farz+nearz)/(nearz-farz)
	self.Ma23 = (2*farz*nearz)/(nearz-farz)
	self.Ma30 = 0.0
	self.Ma31 = 0.0
	self.Ma32 = -1.0
	self.Ma33 = 0.0
end

function Matrix4x4:SetOrthoAsOGL(left, right, bottom, top, nearz, farz)
	self.Ma00 = 2/(right-left)
	self.Ma01 = 0.0
	self.Ma02 = 0.0
	self.Ma03 = (right+left)/(left-right)
	self.Ma10 = 0.0
	self.Ma11 = 2/(top-bottom)
	self.Ma12 = 0.0
	self.Ma13 = (top+bottom)/(bottom-top)
	self.Ma20 = 0.0
	self.Ma21 = 0.0
	self.Ma22 = 2/(nearz-farz)
	self.Ma23 = (farz+nearz)/(nearz-farz)
	self.Ma30 = 0.0
	self.Ma31 = 0.0
	self.Ma32 = 0.0
	self.Ma33 = 1.0
end

function Matrix4x4:SetOrtho2DAsOGL(left, right, bottom, top)
	self.Ma00 = 2/(right-left)
	self.Ma01 = 0.0
	self.Ma02 = 0.0
	self.Ma03 = (right+left)/(left-right)
	self.Ma10 = 0.0
	self.Ma11 = 2/(top-bottom)
	self.Ma12 = 0.0
	self.Ma13 = (top+bottom)/(bottom-top)
	self.Ma20 = 0.0
	self.Ma21 = 0.0
	self.Ma22 = -1.0
	self.Ma23 = 0.0
	self.Ma30 = 0.0
	self.Ma31 = 0.0
	self.Ma32 = 0.0
	self.Ma33 = 1.0
end

function Matrix4x4:Clear()
self.Ma00 = 0.0
self.Ma01 = 0.0
self.Ma02 = 0.0
self.Ma03 = 0.0
self.Ma10 = 0.0
self.Ma11 = 0.0
self.Ma12 = 0.0
self.Ma13 = 0.0
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = 0.0
self.Ma23 = 0.0
self.Ma30 = 0.0
self.Ma31 = 0.0
self.Ma32 = 0.0
self.Ma33 = 0.0
end

function Matrix4x4:SetScale(sx,sy,sz)
self.Ma00 = sx
self.Ma01 = 0.0
self.Ma02 = 0.0
self.Ma03 = 0.0
self.Ma10 = 0.0
self.Ma11 = sy
self.Ma12 = 0.0
self.Ma13 = 0.0
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = sz
self.Ma23 = 0.0
self.Ma30 = 0.0
self.Ma31 = 0.0
self.Ma32 = 0.0
self.Ma33 = 1.0
end

function Matrix4x4:SetTranslate(tx,ty,tz)
self.Ma00 = 1.0
self.Ma01 = 0.0
self.Ma02 = 0.0
self.Ma03 = tx
self.Ma10 = 0.0
self.Ma11 = 1.0
self.Ma12 = 0.0
self.Ma13 = ty
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = 1.0
self.Ma23 = tz
self.Ma30 = 0.0
self.Ma31 = 0.0
self.Ma32 = 0.0
self.Ma33 = 1.0
end

function Matrix4x4:SetRotateOnZ(angle)
angle = angle*PIOVER180
self.Ma00 = math.cos(angle)
self.Ma01 = -math.sin(angle)
self.Ma02 = 0.0
self.Ma03 = 0.0
self.Ma10 = math.sin(angle)
self.Ma11 = mathcos(angle)
self.Ma12 = 0.0
self.Ma13 = 0.0
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = 1.0
self.Ma23 = 0.0
self.Ma30 = 0.0
self.Ma31 = 0.0
self.Ma32 = 0.0
self.Ma33 = 1.0
end


function Matrix4x4:SetInverse3x3()
	det = self:GetDeterminant3x3()
	if((det <= -FUN_EPSILON) or (det >=FUN_EPSILON))
	then
		inv = Matrix4x4()
		onedet = (1/det)
		inv.Ma00 = onedet * (Ma11*Ma22 - Ma12*Ma21)
		inv.Ma01 = onedet * (self.Ma02*self.Ma21 - self.Ma01*self.Ma22)
		inv.Ma02 = onedet * (self.Ma01*self.Ma12 - self.Ma02*self.Ma11)
		inv.Ma03 = 0
		inv.Ma10 = onedet * (self.Ma12*self.Ma20 - self.Ma10*self.Ma22)
		inv.Ma11 = onedet * (self.Ma00*self.Ma22 - self.Ma02*self.Ma20)
		inv.Ma12 = onedet * (self.Ma02*self.Ma10 - self.Ma00*self.Ma12)
		inv.Ma13 = 0
		inv.Ma20 = onedet * (self.Ma10*self.Ma21 - self.Ma11*self.Ma20)
		inv.Ma21 = onedet * (self.Ma01*self.Ma20 - self.Ma00*self.Ma21)
		inv.Ma22 = onedet * (self.Ma00*self.Ma11 - self.Ma01*self.Ma10)
		inv.Ma23 = 0
		inv.Ma30 = 0
		inv.Ma31 = 0
		inv.Ma32 = 0
		inv.Ma33 = onedet
		self:CopyValues(inv)
	end
end

function Matrix4x4:SetIdentity()
self.Ma00 = 1.0
self.Ma01 = 0.0
self.Ma02 = 0.0
self.Ma03 = 0.0
self.Ma10 = 0.0
self.Ma11 = 1.0
self.Ma12 = 0.0
self.Ma13 = 0.0
self.Ma20 = 0.0
self.Ma21 = 0.0
self.Ma22 = 1.0
self.Ma23 = 0.0
self.Ma30 = 0.0
self.Ma31 = 0.0
self.Ma32 = 0.0
self.Ma33 = 1.0
end

function Matrix4x4:SetTranspose()
temp = self.Matrix4x4()
temp.Ma00 = self.Ma00
temp.Ma01 = self.Ma10
temp.Ma02 = self.Ma20
temp.Ma03 = self.Ma30
temp.Ma10 = self.Ma01
temp.Ma11 = self.Ma11
temp.Ma12 = self.Ma21
temp.Ma13 = self.Ma31
temp.Ma20 = self.Ma02
temp.Ma21 = self.Ma12
temp.Ma22 = self.Ma22
temp.Ma23 = self.Ma32
temp.Ma30 = self.Ma03
temp.Ma31 = self.Ma13
temp.Ma32 = self.Ma23
temp.Ma33 = self.Ma33
self:CopyValues(temp)
end


function Matrix4x4:GetDeterminant3x3()
return  self.Ma00*(self.Ma11*self.Ma22 - self.Ma12*self.Ma21) - 
		self.Ma01*(self.Ma10*self.Ma22 - self.Ma12*self.Ma20) + 
		self.Ma02*(self.Ma10*self.Ma21 - self.Ma11*self.Ma20)
end

function Matrix4x4:CopyValues(m)
self.Ma00 = m.Ma00
self.Ma01 = m.Ma10
self.Ma02 = m.Ma20
self.Ma03 = m.Ma30
self.Ma10 = m.Ma01
self.Ma11 = m.Ma11
self.Ma12 = m.Ma21
self.Ma13 = m.Ma31
self.Ma20 = m.Ma02
self.Ma21 = m.Ma12
self.Ma22 = m.Ma22
self.Ma23 = m.Ma32
self.Ma30 = m.Ma03
self.Ma31 = m.Ma13
self.Ma32 = m.Ma23
self.Ma33 = m.Ma33
end

function Matrix4x4:SetOpposite()
	det = self:GetDeterminant3x3()
	if((det <= -FUN_EPSILON) or (det >=FUN_EPSILON))
	then
		oneDet = 1/det
		temp.Ma00 = oneDet * (self.Ma11*self.Ma22 - self.Ma12*self.Ma21)
		temp.Ma01 = oneDet * (self.Ma02*self.Ma21 - self.Ma01*self.Ma22)
		temp.Ma02 = oneDet * (self.Ma01*self.Ma12 - self.Ma02*self.Ma11)
		temp.Ma03 = 0.0
		temp.Ma10 = oneDet * (self.Ma12*self.Ma20 - self.Ma10*self.Ma22)
		temp.Ma11 = oneDet * (self.Ma00*self.Ma22 - self.Ma02*self.Ma20)
		temp.Ma12 = oneDet * (self.Ma02*self.Ma10 - self.Ma00*self.Ma12)
		temp.Ma13 = 0.0
		temp.Ma20 = oneDet * (self.Ma10*self.Ma21 - self.Ma11*self.Ma20)
		temp.Ma21 = oneDet * (self.Ma01*self.Ma20 - self.Ma00*self.Ma21)
		temp.Ma22 = oneDet * (self.Ma00*self.Ma11 - self.Ma01*self.Ma10)
		temp.Ma23 = 0.0
		temp.Ma30 = 0.0
		temp.Ma31 = 0.0
		temp.Ma32 = 0.0
		temp.Ma33 = oneDet
		self:CopyValues(temp)
	end
end

-- this is used by C++ to create a lua Matrix4x4
function CreateMatrix4x4()
local pt = Matrix4x4()
return pt
end