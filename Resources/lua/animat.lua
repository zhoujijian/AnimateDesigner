local logger = function(...) print(string.format(...)) end
local serialize

local function write_indent(indent)
	for i = 1, indent do
		file_handler:write(" ")
	end
end

local function write_key_t(key_t, indent)
	write_indent(indent)
	if type(key_t) == "string" then
		file_handler:write(string.format("%s = ", key_t))
	end
end

local function write_table(key_t, val_t, indent)
	write_key_t(key_t, indent)
	file_handler:write("{\n")
	serialize(val_t, indent + 4)
	write_indent(indent)
	file_handler:write("}", ",\n")
end

function serialize(infor, indent)
	local end_char = ",\n"
	for key, val in pairs(infor) do
		if type(val) == "number" then
			write_key_t(key, indent)
			file_handler:write(val, end_char)
		elseif type(val) == "string" then
			write_key_t(key, indent)
			file_handler:write(string.format("%q", val), end_char)
		elseif type(val) == "table" then
			write_table(key, val, indent)
		end
	end
end

local function write(path, f)
	file_handler = assert(io.open(path, "w+"))
	f(file_handler)
	file_handler:flush()
	file_handler:close()
	file_handler = nil
end

function save_animate()
	local ejoy = require "eoy"

	ejoy.clear()
	local eo = ejoy.geneoy()
	write("animate_frame.lua", function(handler)
		handler:write("return {\n")
		serialize(eo, 4)
		handler:write("}\n")
	end)

	logger("flush animation frame infor!")
end

function save_solution(path, solution)
	write(path, function(handler)
		handler:write("local solution = {\n")
		serialize(solution, 4)
		handler:write("}\nreturn solution")
	end)
	print("flush solution config over!")
end

function save_project(path, project)
	write(path, function(handler)
		handler:write("local project = {\n")
		serialize(project, 4)
		handler:write("}\nreturn project")
	end)
	logger("flush project config over!")
end
