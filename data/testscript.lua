print("script test scenario: " .. self:getName())

t = 0
function pulseConsoleBackground(interval)
	t = t + interval
	console:setBackgroundColor(vec(0,0,0,0.5 + math.sin(t)*0.1))
end
scheduler:schedule("pulseConsoleBackground",1/30,true)

function event.newScenario(scenario)
	if (scenario == nil) then
		print("No scenario")
	else
		print("New scenario " .. scenario:getName())
	end
end

function self:onReset()
	mdraw.notify("Thou shalt reset thyself!")
end

function self:onAddObject(object)
	print("object " .. object:getName() .. " added to scenario " .. self:getName())
end

function self:onRemoveObject(object)
	print("object " .. object:getName() .. " removed from scenario " .. self:getName())
end

