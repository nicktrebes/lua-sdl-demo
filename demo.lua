sdl = require("libluasdl","luaopen_libluasdl")

local ok, err = sdl.init()
if not ok then
	print(err)
	os.exit(1)
end

local window, err = sdl.createWindow("Click and Drag!", 1200, 800);
if not window then
	print(err)
	os.exit(1)
end

local renderer, err = window:createRenderer()
if not renderer then
	print(err)
	os.exit(1)
end

local mouse, mx, my = false, 0, 0

while true do
	while true do
		local event = sdl.pollEvent()
		if event then
			if event.type == "quit" then
				renderer:destroy()
				window:destroy()
				sdl.quit()
				os.exit()
			elseif event.type == "mouseDown" then
				mouse = true
				mx = event.x
				my = event.y
			elseif event.type == "mouseMove" then
				mx = event.x
				my = event.y
			elseif event.type == "mouseUp" then
				mouse = false
			end
		else
			break
		end
	end

	renderer:setColor(0xff, 0xff, 0xff)
	renderer:clear()

	if mouse then
		renderer:setColor(0xff, 0x00, 0x00, 0x80)
		renderer:fillRect((mx - 25), (my - 25), 50, 50)
	end

	renderer:present()
end

