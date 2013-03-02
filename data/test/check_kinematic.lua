if (console) then
	console:resize(15)
end
print("Checking scenario...")
scheduler:schedule("check1", 2)
function check1()
	print("check1")
	test.check(objects.rotating:getAttitude():x() - 2 < 0.1, "rotating attitude")
	test.check(objects.circling:getAttitude():x() - objects.rotating:getAttitude():x() < 0.1, "circling attitude = rotating")
	test.check((objects.circling:getPosition() - vec(1.4,2.9,0)):length() < 0.5, "circling position")
	test.check((objects.animated:getPosition() - vec(0,0,-3)):length() < 0.5, "animated position")
end
