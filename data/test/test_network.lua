myname = moonet.Player:myName()
client2 = nil
waitTime = 0.5

scheduler:schedule("wait", 0.5)
function wait()
	if (moonet.Client:getNumClients() >= 2) then
		scheduler:scheduleAtGameTime("sync", 1.5)
	else
		print(myname .. " waiting, " .. moonet.Client:getNumClients() .. " connected")
		scheduler:schedule("wait", 0.5)
	end
end

function sync()
	time = sim:getTime() + sim:getGameTimeOffset();
	print(myname .. " synced time " .. time .. " offset " .. sim:getGameTimeOffset())
	scheduler:scheduleAtGameTime("check1", time+waitTime+0.3);
	scheduler:scheduleAtGameTime("setup2", time+waitTime+0.4);
	scheduler:scheduleAtGameTime("check2", time+waitTime+0.7);
	scheduler:scheduleAtGameTime("setup3", time+waitTime+0.8);
	scheduler:scheduleAtGameTime("check3", time+waitTime+1.1);
	scheduler:scheduleAtGameTime("setup4", time+waitTime+1.2);
	scheduler:scheduleAtGameTime("check4", time+waitTime+1.5);
	scheduler:scheduleAtGameTime("setup5", time+waitTime+1.6);
	scheduler:scheduleAtGameTime("check5", time+waitTime+1.9);
	if (myname == "server") then
		for c = 0,moonet.Client:getNumClients()-1 do
			if (moonet.Client:getClient(c):getPlayer():getName() == "client2") then
				client2 = moonet.Client:getClient(c)
			end
		end
		test.check(client2, "client2 connected")
	end
end

function check1()
	print(myname .. " check1")
	test.check(objects.ball1:getOwner() == nil, "ball1 owner (1)")
	test.check(objects.ball2:getOwner() == nil, "ball1 owner (1)")
	test.check(not objects.commonball:isRemote(), "commonball not remote")
	test.check(not objects.commonball:isConstructed(), "commonball not constructed")
	if (moonet.Player:me()) then
		test.check(objects.cam, "spawned camera")
	end
end

function setup2()
	-- Client 1 takes ownership of ball1
	if (myname == "client1") then
		objects.ball1:setOwner(moonet.Client:me())
		objects.ball1:setPosition(0,0,5)
	elseif (myname == "server") then
		objects.ball2:setOwner(client2)
	end
end

function check2()
	print(myname .. " check2")
	test.check(objects.ball1:getOwner():getPlayer():getName() == "client1", "ball1 owner (2)")
	test.check((objects.ball1:getPosition() - vec(0,0,5)):length() < 0.1, "ball1 position (2)")
	test.check(objects.ball2:getOwner():getPlayer():getName() == "client2", "ball2 owner (2)")
end

function setup3()
	-- Client 2 tries to "steal" ball1
	if (myname == "client2") then
		objects.ball1:setOwner(moonet.Client:me())
		objects.ball1:setPosition(0,0,10)
	elseif (myname == "client1") then
		objects.ball1:setPosition(0,0,6)
	end
end

function check3()
	print(myname .. " check3")
	test.check(objects.ball1:getOwner():getPlayer():getName() == "client1", "ball1 owner (3)")
	test.check((objects.ball1:getPosition() - vec(0,0,6)):length() < 0.1, "ball1 position (3)")
end

function setup4()
	-- Client 2 tries to give ball1 to server
	if (myname == "client2") then
		objects.ball1:setOwner(nil)
		objects.ball1:setPosition(0,0,10)
	elseif (myname == "client1") then
		objects.ball1:setPosition(0,0,7)
	end
end

function check4()
	print(myname .. " check4")
	test.check(objects.ball1:getOwner():getPlayer():getName() == "client1", "ball1 owner (4)")
	test.check((objects.ball1:getPosition() - vec(0,0,7)):length() < 0.1, "ball1 position (4)")
end

function setup5()
	-- Server takes ball1 back
	if (myname == "server") then
		objects.ball1:setOwner(nil)
	end
end

function check5()
	print(myname .. " check5")
	test.check(objects.ball1:getOwner() == nil, "ball1 owner (5)")
end
