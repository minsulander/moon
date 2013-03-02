-- Test script for the cow object
self.t = 0

function self:onReset()
	print(self:getName() .. " reset")
	self.t = 0
end

function self:onRealize()
	print(self:getName() .. " realized")
	self:setScriptUpdateInterval(0.1)
end

function self:onUnrealize()
	print(self:getName() .. " unrealized")
	self:setScriptUpdateInterval(0)
	kin = moon.cast(self)
	kin:setVelocity(0,0,0)
	kin:setAngularVelocity(0,0,0)
end

function self:onUpdate(dt)
	self.t = self.t + dt
	kin = moon.cast(self)
	if (kin:getRange(objects.cam) < 100) then
		kin:setVelocity(0,0,math.sin(self.speed*self.t)*5)
	else
		kin:setVelocity(self.speed*(objects.cam:getPosition():x() - self:getPosition():x()),
						self.speed*(objects.cam:getPosition():y() - self:getPosition():y()),
						self.speed*(objects.cam:getPosition():z() - self:getPosition():z()))
	end
	kin:setAngularVelocity(self.speed*kin:getElevation(objects.cam),-3*kin:getAttitude():z(),-self.speed*kin:getAzimuth(objects.cam), true)
end

