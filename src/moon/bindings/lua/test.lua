-- Some unit testing functions

test = {}
function test.check(condition, message)
	if (not condition) then
		tprint("Failure: " .. message)
		if (console) then
			console:print("Failure: " .. message)
		end
		app:setExitCode(100)
	else
		if (console) then
			console:print("OK: " .. message)
		end
	end
end

