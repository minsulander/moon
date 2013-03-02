function self:onRealize()
	lon = self:getPositionLatLongHeight()[1]*180/math.pi
	self:setScriptUpdateInterval(0.1)
end

function self:onUpdate(dt)
	lon = lon - 1
	if (lon < -180) then
		lon = 180
	end
	llh = self:getPositionLatLongHeight()
	self:setPositionLatLongHeight(llh[0],lon*math.pi/180,llh[2])
end
