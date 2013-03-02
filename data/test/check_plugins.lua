test.check(plugin:get("test"), "test plugin")
if (plugin:get("maudio")) then
	print("maudio plugin available")
	test.check(maudio, "maudio bindings")
end
if (plugin:get("moodyn")) then
	print("moodyn plugin available")
	test.check(moodyn, "moodyn bindings")
end
