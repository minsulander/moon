if (console) then
	console:resize(15)
end
print("Checking scenario...")
ball1initpos = objects.ball1:getPosition()
ball2initpos = objects.ball2:getPosition()
ball3initpos = objects.ball3:getPosition()

scheduler:schedule("check1", 2.5)
scheduler:schedule("check2", 3)

function check1()
	print("check1")
	test.check((objects.ball1:getPosition() - ball1initpos):length() > 0.1, "ball1 movement")
	test.check((objects.ball2:getPosition() - ball2initpos):length() > 0.1, "ball2 movement")
	test.check((objects.ball3:getPosition() - ball3initpos):length() > 0.1, "ball3 movement")
	objects.ball3:unrealize()
	ball3unrealizepos = objects.ball3:getPosition()
end

function check2()
	print("check2")
	test.check(not objects.ball3:isRealized(), "ball3 unrealized")
	test.check((objects.ball3:getPosition() - ball3unrealizepos):length() < 0.1, "ball3 stopped")
end
