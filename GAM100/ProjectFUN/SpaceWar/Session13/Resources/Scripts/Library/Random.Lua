RAND_MAX = 32767
function Random.SetSeed(seed) -- 1 to reset
	math.srand(seed)
end
        
function Random.GetNumber() --0.0f -> 1.0f
return Math.rand()/RAND_MAX   
end

function GetNumber(value) --0.0f->value if value > 0.0f or value->0.0f if value < 0.0f
return Random.GetNumber() * value
end



function Random.GetNumber(value) --0->value if value > 0 or value->0 if value < 0
	s = 0

	if(value < 0)
	then
		s     = -1;
		value = -value;
	else
        s = 1;
	end

	f = Random.GetNumber() * value
	i = Utility.ToInteger(f)

	if(f - i > 0.5)
	then return s * (i + 1)
	end

	return s * i
end

function Random.GetNumber( minimum,  maximum)
{
    return Random.GetNumber(maximum - minimum) + minimum;        
}

function Random.GetNumber(minimum, maximum)
{
	return Random.GetNumber(maximum - minimum) + minimum;
}

function Random.GetVector2D(vector1, vector2)
{        
    return (vector2 - vector1) * Random.GetNumber() + vector1;
}

function Random.GetColor(color1, color2)
{
    return (color2 - color1) * Random.GetNumber() + color1;
}