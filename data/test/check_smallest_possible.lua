-- check script for scenario examples/smallest_possible.xml
test.check(objects.ball, "ball object")
test.check(objects.ball:getComponent(0):className() == "VisualModel")
test.check(objects.camera, "camera object")
test.check((objects.camera:getPosition() - vec(0,-20,0)):length() < 0.1)
