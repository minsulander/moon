-- Global event handler for key presses

function event.keyPress(id)

	mlog.dout(6, "event.keyPress(" .. id .. ")\n")

	-- Ctrl-Shift-D - Toggle debug display mode
	if (id == 327684 or id == 327748 or id == 16842852) then
		if (scenario:getDisplayMode() == moon.BaseObject.DISPLAY_NORMAL) then
			scenario:setDisplayMode(moon.BaseObject.DISPLAY_DEBUG)
		else
			scenario:setDisplayMode(moon.BaseObject.DISPLAY_NORMAL)
		end
		return true
		
	-- Ctrl-Shift-P - Toggle pause
	elseif (id == 327696 or id == 327760 or id == 16842864) then
		paused = moon.SimulationManager:instance():isPaused()
		moon.SimulationManager:instance():setPaused(not paused)
		return true
		
	-- Ctrl-Shift-R - Reset scenario
	elseif (id == 327698 or id == 327762 or id == 16842866) then
		moon.SimulationManager:instance():setTime(0)
		scenario:reset()
		return true
		
	-- Ctrl-Shift-C - Toggle console
	elseif (id == 327683 or id == 327747 or id == 16842851) then
		viewer:showConsoleWindow(not viewer:isConsoleWindowShown())
		return true

	-- Ctrl-Shit-E - Toggle edit mode
	elseif (id == 327685 or id == 327749 or id == 16842853) then
		viewer:setEditMode(not viewer:isEditing())
		event.pause(moon.SimulationManager:instance():isPaused()) -- reset banner text
		return true
		
	end
	
	
	return false
end
