
require "Json"

local function commit_game(game, players, teams)

    local d = os.date("%0e%b%Y_%H:%M")
    local filename = string.format("log/game/%s_%s.json", d, game.map)
    
    local file = io.open(filename,"w");
    
    local root = {}
    root.game = game
    root.players = map_to_array(players)
    root.teams = teams
    
    file:write(Json.Encode(root))
    file:flush()
end

return {commit_game = commit_game}
