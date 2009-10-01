--[[

	A player command to unmute a player

]]


return function(cn,tcn)

	if not tcn then

		return false, "#unmute <cn>|\"<name>\""
	end

	if not server.valid_cn(tcn) then

		tcn = server.name_to_cn_list_matches(cn,tcn)

		if not tcn then

			return
		end
	end

	server.unmute(tcn)

end
