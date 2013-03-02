function osg.Vec3:__tostring()
	return "(" .. self:x() .. "," .. self:y() .. "," .. self:z() .. ")"
end

function osg.Vec4:__tostring()
	return "(" .. self:x() .. "," .. self:y() .. "," .. self:z() .. "," .. self:w() .. ")"
end

function moon.BaseObject:__tostring()
	return "Object '" .. self:getName() .. "'"
end

function moon.Camera:__tostring()
	return "Camera '" .. self:getName() .. "'"
end

function moon.Scenario:__tostring()
	return "Scenario '" .. self:getName() .. "'"
end
