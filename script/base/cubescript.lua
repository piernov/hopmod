
local library = require("cubescript_library")

-- Give the cubescript environment direct access to the core table
setmetatable(library, {
    __index = function(_, value)
        return core[value] or core.vars[value] or _G[value]
    end
})

exec = library.exec
exec_if_found = library.exec_if_found
search_paths = library.exec_search_paths
exec_handler = library.exec_type

function add_exec_search_path(path)
    search_paths[#search_paths + 1] = path
end

exec_handler["vars"] = library.exec_cubescript

--[[ Backwards compatibility stuff (deprecated) ]]

core.parse_list = library.parse_array

execIfFound = exec_if_found

library.global = function(name, value)
    local property_value = value
    core.vars[name] = function(value)
        if value then
            property_value = value
            return value
        else
            return property_value
        end
    end
end

function cubescript.eval_string(code)
    return cubescript.eval(code .. "\n", library)
end

