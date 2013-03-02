if (console) then
	console:resize(15)
end
print("Checking scenario...")
scheduler:schedule("check1", 0.5)
scheduler:schedule("check2", 2.5)
scheduler:schedule("check3", 20)
platform3initpos = objects.platform3:getPosition()
platform3body = moon.cast(objects.platform3):getBody()

function check1()
	print("check1")
	test.check(objects.platform3:getPosition():z() < platform3initpos:z(), "platform descent")
	test.check(platform3body:isEnabled(), "platform enabled")
end

function check2()
	print("check2")
	test.check((objects.ball1:getPosition() - vec(-5,0,10)):length() < 0.5, "ball1 position")
	test.check((objects.ball2:getPosition() - vec(0,0,9.5)):length() < 0.5, "ball2 position")
	test.check((objects.ball3:getPosition() - vec(5,0,7)):length() < 0.5, "ball3 position")
end

function check3()
	print("check3")
	test.check((objects.ball3:getPosition() - vec(5,0,4)):length() < 0.5, "ball3 position")
	test.check(not platform3body:isEnabled(), "platform disabled")
end
