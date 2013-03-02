event = {}

function event.newScenario()
	if (viewer == nil) then
		return
	end
	if (scenario == nil) then
		viewer:setBannerText("NO SCENARIO")
	elseif (objects.cam == nil and viewer:getManipulator() == 0) then
		viewer:setBannerText("NO CAMERA")
	elseif (moon.SimulationManager:instance():isPaused() and not viewer:isEditing()) then
		viewer:setBannerText("PAUSED")
	else
		viewer:setBannerText("")
	end
	viewer:setStatusText("")
end

event.pause = event.newScenario
event.run = event.newScenario

_save_try = 0
function event.editorSave(force)
	t = moon.SimulationManager:instance():getTime()
	if (t == 0 or _save_try > 0) then
		app:saveScenario("scenario.xml")
		mdraw.notify("Saved " .. app:getRootPath() .. "/" .. "scenario.xml")
		_save_try = 0
	else
		mdraw.notify("Simulation is not at t=0! Press ^R to reset scenario, or ^S again to force save.", vec(1,0,0,1))
		_save_try = _save_try + 1
	end
end

--------------- Network events ---------------------

function event.connect(client)
	if (net:isServer() and client ~= nil) then
		mdraw.notify("Client " .. client:toString() .. " connected")
	else
		mdraw.notify("Connected")
	end
end

function event.disconnect(client)
	if (net:isServer() and client ~= nil) then
		mdraw.notify("Client " .. client:toString() .. " disconnected")
	else
		mdraw.notify("Disconnected")
	end
end

function event.connectionFailed()
	mdraw.notify("Connection failed")
end

function event.noFreeIncomingConnections()
	mdraw.notify("No free incoming connections")
end

function event.connectionLost(client)
	if (net:isServer() and client ~= nil) then
		mdraw.notify("Client " .. client:toString() .. " lost connection")
	else
		mdraw.notify("Lost connection")
	end
end

function event.playerJoin(player)
	mdraw.notify("Player " .. player:getName() .. " joined")
end

function event.playerGone(player)
	mdraw.notify("Player " .. player:getName() .. " gone")
end

function event.joinGame(game)
	mdraw.notify("Joining game " .. game:getName())
end

function event.chat(message, player)
	if (player ~= nil) then
		str = player:getName()
	else
		str = "server"
	end
	str = str .. ": " .. message
	mdraw.notify(str)
end

