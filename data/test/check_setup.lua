-- Check that Lua bindings have been setup correctly
test.check(moon, "moon bindings")
test.check(app, "app object")
test.check(objects, "objects table")
test.check(event, "event table")
test.check(tprint ~= nil, "print function")
test.check(info ~= nil, "info function")

