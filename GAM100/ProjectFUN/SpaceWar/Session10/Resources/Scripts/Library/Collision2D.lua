--The following File is a wrapper for ProjectFun 2DCollision utility classes
--The original C++ declaration can be found in: Collision_Utilities.h
--it is only meant to be used when the user wants to retrive information
--about a collision object. the user cannot use these structures
--to add collision info!
NEIGHBOR = {N_NONE = 0, 
			N_UP = 1, 
			N_DOWN = 2, 
			N_LEFT = 3, 
			N_RIGHT = 4, 
			N_UP_RIGHT = 5, 
			N_DOWN_RIGHT = 6, 
			N_UP_LEFT = 7, 
			N_DOWN_LEFT = 8}

----------------------------------------------------------------------------
--COLLISION_C
----------------------------------------------------------------------------

COLLISION_C= {id = 0,
		  contactPosition = Point2D(),
		  contactOrientation = 0,
		  penetrationDistance = 0,
		  className = "COLLISION_C"}
COLLISION_C.mt = {}

--Creation by Constructor simulation
COLLISION_C.mt.__call = function(caller)
p = {}
setmetatable(p,COLLISION_C)
COLLISION_C.__index = COLLISION_C
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.className = "COLLISION_C"
return p
end

setmetatable(COLLISION_C,COLLISION_C.mt)

--Creation with new
function COLLISION_C:new()
p = {}
setmetatable(p,self)
self.__index = self
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.className = "COLLISION_C"
return p
end


-- this is used by C++ to create a lua COLLISION_C
function CreateCOLLISION_C()
local pt = COLLISION_C()
return pt
end


----------------------------------------------------------------------------
--BRECT_C
----------------------------------------------------------------------------
BRECT_C= {id = 0,
		  rectangleIntersection= {top =0, left = 0, right = 0, bottom = 0},
		  contactPosition = Point2D(),
		  contactOrientation= 0,
		  className = "BRECT_C"}
BRECT_C.mt = {}

--Creation by Constructor simulation
BRECT_C.mt.__call = function(caller)
p = {}
setmetatable(p,BRECT_C)
BRECT_C.__index = BRECT_C
p.id = 0
p.rectangleIntersection= {top =0, left = 0, right = 0, bottom = 0}
p.contactPosition = Point2D()
p.contactOrientation = 0
p.className = "BRECT_C"
return p
end

setmetatable(BRECT_C,BRECT_C.mt)

--Creation with new
function BRECT_C:new()
p = {}
setmetatable(p,self)
self.__index = self
p.id = 0
p.rectangleIntersection= {top =0, left = 0, right = 0, bottom = 0}
p.contactPosition = Point2D()
p.contactOrientation = 0
p.className = "BRECT_C"
return p
end


-- this is used by C++ to create a lua BRECT_C
function CreateBRECT_C()
local pt = BRECT_C()
return pt
end

----------------------------------------------------------------------------
--CIR_C
----------------------------------------------------------------------------
CIR_C= {id = 0,
		  contactPosition = Point2D(),
		  contactOrientation = 0,
		  penetrationDistance = 0,
		  contactPoint = {Point2D(),Point2D(),Point2D(),Point2D()},
		  normal = {Vector2D(),Vector2D(),Vector2D(),Vector2D()},
		  numberOfIntersectedPoints = 0,
		  userId = 0,
		  myCircleUserId = {0,0,0,0},
		  myLineSegmentUserId = {0,0,0,0},
		  className = "CIR_C"
}
CIR_C.mt = {}

--Creation by Constructor simulation
CIR_C.mt.__call = function(caller)
p = {}
setmetatable(p,CIR_C)
CIR_C.__index = CIR_C
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.contactPoint = {Point2D(),Point2D(),Point2D(),Point2D()}
p.normal = {Vector2D(),Vector2D(),Vector2D(),Vector2D()}
p.numberOfIntersectedPoints = 0
p.userId = 0
p.myCircleUserId = {0,0,0,0}
p.myLineSegmentUserId = {0,0,0,0}
p.className = "CIR_C"
return p
end

setmetatable(CIR_C,CIR_C.mt)

--Creation with new
function CIR_C:new()
p = {}
setmetatable(p,self)
self.__index = self
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.contactPoint = {Point2D(),Point2D(),Point2D(),Point2D()}
p.normal = {Vector2D(),Vector2D(),Vector2D(),Vector2D()}
p.numberOfIntersectedPoints = 0
p.userId = 0
p.myCircleUserId = {0,0,0,0}
p.myLineSegmentUserId = {0,0,0,0}
p.className = "CIR_C"
return p
end


-- this is used by C++ to create a lua CIR_C
function CreateCIR_C()
local pt = CIR_C()
return pt
end

----------------------------------------------------------------------------
--LNS_C
----------------------------------------------------------------------------
LNS_C= {id = 0,
		  contactPosition = Point2D(),
		  contactOrientation = 0,
		  penetrationDistance = 0,
		  contactPoint = {Point2D(),Point2D(),Point2D(),Point2D()},
		  normal = {Vector2D(),Vector2D(),Vector2D(),Vector2D()},
		  numberOfIntersectedPoints = 0,
		  userId = 0,
		  myCircleUserId = {0,0,0,0},
		  myLineSegmentUserId = {0,0,0,0},
		  className = "LNS_C"
}
LNS_C.mt = {}

--Creation by Constructor simulation
LNS_C.mt.__call = function(caller)
p = {}
setmetatable(p,LNS_C)
LNS_C.__index = LNS_C
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.contactPoint = {Point2D(),Point2D(),Point2D(),Point2D()}
p.normal = {Vector2D(),Vector2D(),Vector2D(),Vector2D()}
p.numberOfIntersectedPoints = 0
p.userId = 0
p.myCircleUserId = {0,0,0,0}
p.myLineSegmentUserId = {0,0,0,0}
p.className = "LNS_C"
return p
end

setmetatable(LNS_C,LNS_C.mt)

--Creation with new
function LNS_C:new()
p = {}
setmetatable(p,self)
self.__index = self
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.contactPoint = {Point2D(),Point2D(),Point2D(),Point2D()}
p.normal = {Vector2D(),Vector2D(),Vector2D(),Vector2D()}
p.numberOfIntersectedPoints = 0
p.userId = 0
p.myCircleUserId = {0,0,0,0}
p.myLineSegmentUserId = {0,0,0,0}
p.className = "LNS_C"
return p
end


-- this is used by C++ to create a lua LNS_C
function CreateLNS_C()
local pt = LNS_C()
return pt
end

----------------------------------------------------------------------------
--DGEO_C
----------------------------------------------------------------------------
DGEO_C= {id = 0,
		  contactPosition = Point2D(),
		  contactOrientation = 0,
		  penetrationDistance = 0,
		  lineSegments = {},
		  circles = {},
		  currentLineSegmentsNumber = 0,
		  currentCirclesNumber = 0,
		  deltaBuffer = 0,
		  buffer_LineSegments = 0,
		  buffer_Circles = 0,
		  className = "DGEO_C"
}
DGEO_C.mt = {}

--Creation by Constructor simulation
DGEO_C.mt.__call = function(caller)
p = {}
setmetatable(p,DGEO_C)
DGEO_C.__index = DGEO_C
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.lineSegments = {}
p.circles = {}
p.currentLineSegmentsNumber = 0
p.currentCirclesNumber = 0
p.deltaBuffer = 0
p.buffer_LineSegments = 0
p.buffer_Circles = 0
p.className = "DGEO_C"
return p
end

setmetatable(DGEO_C,DGEO_C.mt)

--Creation with new
function DGEO_C:new()
p = {}
setmetatable(p,self)
self.__index = self
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.lineSegments = {}
p.circles = {}
p.currentLineSegmentsNumber = 0
p.currentCirclesNumber = 0
p.deltaBuffer = 0
p.buffer_LineSegments = 0
p.buffer_Circles = 0
p.className = "DGEO_C"
return p
end


-- this is used by C++ to create a lua DGEO_C
function CreateDGEO_C()
local pt = DGEO_C()
return pt
end


----------------------------------------------------------------------------
--TMAP_DATA_BASE
----------------------------------------------------------------------------
TMAP_DATA_BASE= {id = 0,
		  cellX = 0,
		  cellY = 0,
		  collisionSide = 0,
		  hotSpotIndex = 0,
		  className = "TMAP_DATA_BASE"
}
TMAP_DATA_BASE.mt = {}

--Creation by Constructor simulation
TMAP_DATA_BASE.mt.__call = function(caller)
p = {}
setmetatable(p,TMAP_DATA_BASE)
TMAP_DATA_BASE.__index = TMAP_DATA_BASE
p.id = 0
p.cellX = 0
p.cellY = 0
p.collisionSide = 0
p.hotSpotIndex = 0
p.className = "TMAP_DATA_BASE"
return p
end

setmetatable(TMAP_DATA_BASE,TMAP_DATA_BASE.mt)

--Creation with new
function TMAP_DATA_BASE:new()
p = {}
setmetatable(p,self)
self.__index = self
p.id = 0
p.cellX = 0
p.cellY = 0
p.collisionSide = 0
p.hotSpotIndex = 0
p.className = "TMAP_DATA_BASE"
return p
end


-- this is used by C++ to create a lua TMAP_DATA_BASE
function CreateTMAP_DATA_BASE()
local pt = TMAP_DATA_BASE()
return pt
end

----------------------------------------------------------------------------
--TMAP_DATA
----------------------------------------------------------------------------
TMAP_DATA= {id = 0,
		  cellX = 0,
		  cellY = 0,
		  collisionSide = 0,
		  hotSpotIndex = 0,
		  position = Point2D(),
		  normal = Vector2D(),
		  zAngle = 0,
		  className = "TMAP_DATA"
}
TMAP_DATA.mt = {}

--Creation by Constructor simulation
TMAP_DATA.mt.__call = function(caller)
p = {}
setmetatable(p,TMAP_DATA)
TMAP_DATA.__index = TMAP_DATA
p.id = 0
p.cellX = 0
p.cellY = 0
p.collisionSide = 0
p.hotSpotIndex = 0
p.position = Point2D()
p.normal = Vector2D()
p.zAngle = 0
p.className = "TMAP_DATA"
return p
end

setmetatable(TMAP_DATA,TMAP_DATA.mt)

--Creation with new
function TMAP_DATA:new()
p = {}
setmetatable(p,self)
self.__index = self
p.id = 0
p.cellX = 0
p.cellY = 0
p.collisionSide = 0
p.hotSpotIndex = 0
p.position = Point2D()
p.normal = Vector2D()
p.zAngle = 0
p.className = "TMAP_DATA"
return p
end


-- this is used by C++ to create a lua TMAP_DATA
function CreateTMAP_DATA()
local pt = TMAP_DATA()
return pt
end

----------------------------------------------------------------------------
--TMAP_C
----------------------------------------------------------------------------

TMAP_C= {id = 0,
		  contactPosition = Point2D(),
		  contactOrientation = 0,
		  penetrationDistance = 0,
		  deltaBuffer = 0,
		  currentNewIdsNumber = 0,
		  currentStaticIdsNumber = 0,
   		  buffer_NewIds = 0,
		  buffer_StaticIds = 0,
		  newEntries = {},
		  staticEntries = {},
		  className = "TMAP_C"}
TMAP_C.mt = {}

--Creation by Constructor simulation
TMAP_C.mt.__call = function(caller)
p = {}
setmetatable(p,TMAP_C)
TMAP_C.__index = TMAP_C
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.deltaBuffer = 0
p.currentNewIdsNumber = 0
p.currentStaticIdsNumber = 0
p.buffer_NewIds = 0
p.buffer_StaticIds = 0
p.newEntries = {}
p.staticEntries = {}
p.className = "TMAP_C"
return p
end

setmetatable(TMAP_C,TMAP_C.mt)

--Creation with new
function TMAP_C:new()
p = {}
setmetatable(p,self)
self.__index = self
p.id = 0
p.contactPosition = Point2D()
p.contactOrientation = 0
p.penetrationDistance = 0
p.deltaBuffer = 0
p.currentNewIdsNumber = 0
p.currentStaticIdsNumber = 0
p.buffer_NewIds = 0
p.buffer_StaticIds = 0
p.newEntries = {}
p.staticEntries = {}
p.className = "TMAP_C"
return p
end


-- this is used by C++ to create a lua TMAP_C
function CreateTMAP_C()
local pt = TMAP_C()
return pt
end

--utility:
function CreateArrayTable(array, v1,v2,v3,v4)
array[0] = v1
array[1] = v2
array[2] = v3
array[3] = v4
end

function CreateArrayTableVar(array, ...)
	index = 0
	for i,v in ipairs(arg) do
		array[index] = v
		index = index + 1
	end
end