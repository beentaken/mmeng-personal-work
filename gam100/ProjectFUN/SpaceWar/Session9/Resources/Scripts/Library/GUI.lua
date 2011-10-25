ScrollType = {Horizontal = 0, Vertical = 1}

--MouseEvent Class (table)
MouseEvent = {Button = 0,Clicks = 0,Delta = 0, X = 0, Y = 0 ,  className = "MouseEvent"}
--MouseEvent Class Metatable
MouseEvent.mt = {}

--Creation by Constructor simulation
MouseEvent.mt.__call = function(caller)
p = {}
setmetatable(p,MouseEvent)
MouseEvent.__index = MouseEvent
p.X = 0
p.Y = 0
p.Button = Button.None
p.Clicks = 0
p.Delta  = 0
p.className = "MouseEvent"
return p
end
setmetatable(MouseEvent,MouseEvent.mt)

--Creation with new
function MouseEvent:new()
p = {}
setmetatable(p,self)
self.__index = self
p.X = 0
p.Y = 0
p.Button = Button.None
p.Clicks = 0
p.Delta  = 0
p.className = "MouseEvent"
return p
end

-- this is used by C++ to create a lua MouseEvent
function CreateMouseEvent()
local pt = MouseEvent()
return pt
end


--Size Class (table)
Size = {Width = 0,Height = 0, className = "Size"}
--Size Class Metatable
Size.mt = {}

--Creation by Constructor simulation
Size.mt.__call = function(caller,x,y)
x = x or 0 --set x to 0 if it is nil
y = y or 0 --set y to 0 if it is nil
p = {}
setmetatable(p,Size)
Size.__index = Size
p.Width = x
p.Height = y
p.className = "Size"
return p
end
setmetatable(Size,Size.mt)

--Creation with new
function Size:new(x,y)
x = x or 0 --set x to 0 if it is nil
y = y or 0 --set y to 0 if it is nil
p = {}
setmetatable(p,self)
self.__index = self
p.Width = x
p.Height = y
p.className = "Size"
return p
end

-- this is used by C++ to create a lua Size
function CreateSize()
local pt = Size()
return pt
end