-- Redefine print function for printing to console
tprint = print
function print(...)
	for i,v in ipairs(arg) do
		if (console) then
			console:print(tostring(v))
		else
			tprint(v)
		end
	end
end

-- Create an osg.Vec3 or osg.Vec4
function vec(x,y,z,w)
   if (w == nil) then
      return osg.Vec3:new(x,y,z)
   else
      return osg.Vec4:new(x,y,z,w)
   end
end

-- Show info on any object (if available)
function info(object)
   print(tolua.type(object) .. ": " .. tostring(object))
   if (type(object) == "table") then
      local i = 0
      local list = {}
      for k,v in pairs(object) do
      	if (not (tolua.type(v) == "function" and string.match(k,"__") ~= nil)) then
	        i = i + 1
    	    list[i] = "  " .. tolua.type(v) .. ": " .. k	
      	end
      end
      table.sort(list)
      for i,v in ipairs(list) do
         print(v)
      end
   end
end

-- Cast a BaseObject to its own type
function moon.cast(obj)
	return tolua.cast(obj, obj:libraryName() .. "::" .. obj:className())
end

-- Set default prompts
_PROMPT = ">"
_PROMPT2 = ">>"

mlog.dout(1, "init.lua loaded OK\n", moon.SCRIPT)
