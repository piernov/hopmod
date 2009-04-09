
dofile("./script/playervars.lua")

function round(num, idp)
  local mult = 10^(idp or 0)
  return math.floor(num * mult + 0.5) / mult
end

function format_filesize(bytes)
    bytes = tonumber(bytes)
    if bytes < 1024 then return bytes .. "B"
    elseif bytes < (1024*1024) then return round(bytes/1024) .. "KB"
    else return round(bytes/(1024*1024)) .. "MB"
    end
end

server.format_filesize = format_filesize

-- color formatting strings

function formatcol(col, text)
    if text then return "\fs\f" .. col .. text .. "\fr" else return "\f" ..col end
end

function red(text) return formatcol(3,text) end
function orange(text) return formatcol(6, text) end
function green(text) return formatcol(0, text) end
function white(text) return formatcol(10, text) end

local set_cancel_restart = false

function server.restart()
    
    set_cancel_restart = false
    local warning_msg = "The server is set for a restart at the end of this game."
    
    server.msg(warning_msg)
    
    local con_handler -- seems it must be declared before assignment to be included in event handler's closure
    con_handler = server.event_handler("connect", function(cn)
    
        if set_cancel_restart then
            server.cancel_handler(con_handler)
        else
            server.player_msg(cn, warning_msg) 
        end
    end)
    
    local mapch_handler
    mapch_handler = server.event_handler("setnextgame", function()
        
        if set_cancel_restart then
           server.cancel_handler(mapch_handler)
        else
            server.restart_now()
        end
    end)
    
end

function server.cancel_restart()
    server.msg("Server restart cancelled.")
    set_cancel_restart = true
end

function server.restart_now()
    server.msg("Server restarting...")
    server.exec_restarter()
    server.shutdown()
end

function server.log_status(msg)
    print(msg)
end

function server.mute(cn)
    server.player_pvar(cn, "mute", true)
end

function server.unmute(cn)
    server.player_unsetpvar(cn, "mute")
end

function server.specall()
    for i,cn in ipairs(server.players()) do server.spec(cn) end
end

function server.unspecall()
    for i,cn in ipairs(server.spectators()) do server.unspec(cn) end
end
