#ifdef BOOST_BUILD_PCH_ENABLED
#include "pch.hpp"
#endif

#include "cube.h"
#include "game.h"
#include "hopmod.hpp"
#include "extapi.hpp"
#include "string_var.hpp"
#include <fungu/script.hpp>
#include <fungu/script/variable.hpp>
using namespace fungu;
#include <unistd.h>

void start_http_server(const char * ip, const char * port);
void stop_http_server();

static std::vector<script::any> player_kick_defargs;
static std::vector<script::any> changemap_defargs;
static std::vector<script::any> recorddemo_defargs;
extern bool reloaded; //startup.cpp

static void setup_default_arguments()
{
    player_kick_defargs.clear();
    player_kick_defargs.push_back(14400);
    player_kick_defargs.push_back(std::string("server"));
    player_kick_defargs.push_back(std::string(""));
    
    changemap_defargs.clear();
    changemap_defargs.push_back(const_string());
    changemap_defargs.push_back(-1);
    
    recorddemo_defargs.clear();
    recorddemo_defargs.push_back(std::string(""));
}

void register_server_script_bindings(script::env & env)
{
    setup_default_arguments();
    
    // Player-oriented functions
    script::bind_freefunc(server::player_msg, "player_msg", env);
    script::bind_freefunc(process_player_command, "process_player_command", env);
    script::bind_freefunc(server::kick, "kick", env, &player_kick_defargs);
    script::bind_const((int)DISC_NONE, "DISC_NONE", env);
    script::bind_const((int)DISC_EOP, "DISC_EOP", env);
    script::bind_const((int)DISC_EOP, "DISC_CN", env);
    script::bind_const((int)DISC_EOP, "DISC_KICK", env);
    script::bind_const((int)DISC_EOP, "DISC_TAGT", env);
    script::bind_const((int)DISC_EOP, "DISC_IPBAN", env);
    script::bind_const((int)DISC_EOP, "DISC_PRIVATE", env);
    script::bind_const((int)DISC_EOP, "DISC_MAXCLIENTS", env);
    script::bind_const((int)DISC_EOP, "DISC_TIMEOUT", env);
    script::bind_const((int)DISC_EOP, "DISC_NUM", env);
    script::bind_freefunc(server::disconnect, "disconnect", env);
    script::bind_var(server::kick_bannedip_group, "kick_bannedip_group", env);
    script::bind_freefunc(server::player_name, "player_name", env);
    script::bind_freefunc(server::player_displayname, "player_displayname", env);
    script::bind_freefunc(server::player_team, "player_team", env);
    script::bind_freefunc(server::player_privilege, "player_priv", env);
    script::bind_freefunc(server::player_privilege_code, "player_priv_code", env);
    script::bind_const((int)PRIV_NONE, "PRIV_NONE", env);
    script::bind_const((int)PRIV_MASTER, "PRIV_MASTER", env);
    script::bind_const((int)PRIV_ADMIN, "PRIV_ADMIN", env);
    script::bind_freefunc(server::player_id, "player_id", env);
    script::bind_freefunc(clear_player_ids, "clear_player_ids", env);
    script::bind_freefunc(server::player_sessionid, "player_sessionid", env);
    script::bind_freefunc(server::player_ping, "player_ping", env);
    script::bind_freefunc(server::player_ping_update, "player_ping_update", env);
    script::bind_freefunc(server::player_lag, "player_lag", env);
    script::bind_freefunc(server::player_ip, "player_ip", env);
    script::bind_freefunc(server::player_iplong, "player_iplong", env);
    script::bind_freefunc(server::player_status, "player_status", env);
    script::bind_freefunc(server::player_status_code, "player_status_code", env);
    script::bind_freefunc(server::player_frags, "player_frags", env);
    script::bind_freefunc(server::player_deaths, "player_deaths", env);
    script::bind_freefunc(server::player_suicides, "player_suicides", env);
    script::bind_freefunc(server::player_teamkills, "player_teamkills", env);
    script::bind_freefunc(server::player_damage, "player_damage", env);
    script::bind_freefunc(server::player_damagewasted, "player_damagewasted", env);
    script::bind_freefunc(server::player_maxhealth, "player_maxhealth", env);
    script::bind_freefunc(server::player_health, "player_health", env);
    script::bind_freefunc(server::player_gun, "player_gun", env);
    script::bind_freefunc(server::player_hits, "player_hits", env);
    script::bind_freefunc(server::player_misses, "player_misses", env);
    script::bind_freefunc(server::player_shots, "player_shots", env);
    script::bind_freefunc(server::player_accuracy, "player_accuracy", env);
    script::bind_freefunc(server::player_timeplayed, "player_timeplayed", env);
    script::bind_freefunc(server::player_win, "player_win", env);
    script::bind_freefunc(server::player_slay, "player_slay", env);
    script::bind_freefunc((void (*)(int))server::suicide, "player_suicide", env);
    script::bind_freefunc(server::player_changeteam, "changeteam", env);
    script::bind_freefunc(server::player_bots, "player_bots", env);
    script::bind_freefunc(server::player_rank, "player_rank", env);
    script::bind_freefunc(server::player_isbot, "player_isbot", env);
    script::bind_freefunc(server::player_mapcrc, "player_mapcrc", env);
    script::bind_freefunc((std::vector<float>(*)(int))server::player_pos, "player_pos", env);
    register_lua_function((int (*)(lua_State *))&server::player_pos, "player_pos");
    script::bind_freefunc(server::send_auth_request, "send_auth_request", env);
    script::bind_freefunc(server::sendauthchallenge, "send_auth_challenge_to_client", env);
    script::bind_freefunc(server::send_item, "send_item", env);
    
    script::bind_const((int)CS_ALIVE, "ALIVE", env);
    script::bind_const((int)CS_DEAD, "DEAD", env);
    script::bind_const((int)CS_SPAWNING, "SPAWNING", env);
    script::bind_const((int)CS_LAGGED, "LAGGED", env);
    script::bind_const((int)CS_SPECTATOR, "SPECTATOR", env);
    script::bind_const((int)CS_EDITING, "EDITING", env);
    script::bind_freefunc(server::player_connection_time, "player_connection_time", env);
    script::bind_freefunc(server::player_spec, "spec", env);
    script::bind_freefunc(server::player_unspec, "unspec", env);
    script::bind_freefunc(server::unsetmaster, "unsetmaster", env);
    script::bind_freefunc(server::set_player_master, "setmaster", env);
    script::bind_freefunc(server::set_player_admin, "setadmin", env);
    script::bind_freefunc(server::set_player_private_admin, "set_invadmin", env);
    script::bind_freefunc(server::set_player_private_master, "set_invmaster", env);
    script::bind_freefunc(server::unset_player_privilege, "unsetpriv", env);
    
    script::bind_freefunc(server::cs_player_list, "players", env);
    script::bind_freefunc(server::cs_spec_list, "spectators", env);
    script::bind_freefunc(server::cs_bot_list, "bots", env);
    register_lua_function(&server::lua_player_list, "players");
    register_lua_function(&server::lua_spec_list, "spectators");
    register_lua_function(&server::lua_bot_list, "bots");
    
    register_lua_function(&server::lua_gamemodeinfo, "gengamemodeinfo");
    
    // Team-oriented functions
    script::bind_freefunc(server::team_msg,"team_msg", env);
    script::bind_freefunc(server::get_teams, "teams", env);
    register_lua_function(&server::lua_team_list, "teams");
    script::bind_freefunc(server::get_team_score, "team_score", env);
    script::bind_freefunc(server::team_win, "team_win", env);
    script::bind_freefunc(server::team_draw, "team_draw", env);
    script::bind_freefunc(server::get_team_players, "team_players", env);
    register_lua_function(&server::lua_team_players, "team_players");
    
    // Server-oriented functions and variables
    script::bind_freefunc(reload_hopmod, "reloadscripts", env);
    script::bind_freefunc(server::pausegame,"pausegame",env);
    script::bind_ro_var(server::gamepaused, "paused", env);
    script::bind_freefunc(server::sendservmsg, "msg", env);
    script::bind_freefunc(server::shutdown, "shutdown", env);
    script::bind_freefunc(restart_now, "restart_now", env);
    script::bind_freefunc(server::changetime, "changetime", env);
    script::bind_freefunc(server::changemap,"changemap", env, &changemap_defargs);
    script::bind_freefunc(server::addpermban, "permban", env);
    script::bind_freefunc(server::unsetban, "unsetban", env);
    script::bind_freefunc(server::clearbans, "clearbans", env);
    script::bind_freefunc(server::get_bans, "bans", env);
    script::bind_freefunc(server::addbot, "addbot", env);
    script::bind_freefunc(server::aiman::deleteai, "delbot", env);
    script::bind_freefunc(server::recorddemo, "recorddemo", env, &recorddemo_defargs);
    script::bind_freefunc(server::enddemorecord, "stopdemo", env);
    script::bind_freefunc(server::add_allowed_ip, "allow_ip", env);
    
    script::bind_var(server::serverdesc, "servername", env);
    script::bind_ro_var(server::smapname, "map", env);
    script::bind_var(server::serverpass, "server_password", env);
    script::bind_wo_var(server::masterpass, "admin_password", env);
    script::bind_freefunc(server::compare_admin_password, "check_admin_password", env);
    script::bind_ro_var(server::currentmaster, "master", env);
    script::bind_ro_var(server::minremain, "timeleft", env);
    script::bind_var(server::interm, "intermission", env);
    script::bind_ro_var(totalmillis, "uptime", env);
    script::bind_ro_var(server::gamemillis, "gamemillis", env);
    script::bind_ro_var(server::gamelimit, "gamelimit", env);
    script::bind_var(maxclients, "maxplayers", env);
    script::bind_var(serverip, "serverip", env);
    script::bind_var(serverport, "serverport", env);
    script::bind_var(server::next_gamemode, "next_mode", env);
    script::bind_var(server::next_mapname, "next_map", env);
    script::bind_var(server::next_gametime, "next_gametime", env);
    script::bind_var(server::reassignteams, "reassignteams", env);
    script::bind_funvar<int>(server::getplayercount, "playercount", env);
    script::bind_funvar<int>(server::getspeccount, "speccount", env);
    script::bind_funvar<int>(server::getbotcount, "botcount", env);
    script::bind_var(server::aiman::botlimit, "botlimit", env);
    script::bind_var(server::aiman::botbalance, "botbalance", env);
    script::bind_funvar<const char *>(server::gamemodename, "gamemode", env);
    
    script::bind_var(server::allow_mm_veto, "allow_mastermode_veto", env);
    script::bind_var(server::allow_mm_locked, "allow_mastermode_locked", env);
    script::bind_var(server::allow_mm_private, "allow_mastermode_private", env);
    
    script::bind_var(server::allow_item[I_SHELLS-I_SHELLS], "allow_shells", env);
    script::bind_var(server::allow_item[I_BULLETS-I_SHELLS], "allow_bullets", env);
    script::bind_var(server::allow_item[I_ROCKETS-I_SHELLS], "allow_rockets", env);
    script::bind_var(server::allow_item[I_ROUNDS-I_SHELLS], "allow_rounds", env);
    script::bind_var(server::allow_item[I_GRENADES-I_SHELLS], "allow_grenades", env);
    script::bind_var(server::allow_item[I_CARTRIDGES-I_SHELLS], "allow_cartridges", env);
    script::bind_var(server::allow_item[I_HEALTH-I_SHELLS], "allow_health", env);
    script::bind_var(server::allow_item[I_BOOST-I_SHELLS], "allow_healthboost", env);
    script::bind_var(server::allow_item[I_GREENARMOUR-I_SHELLS], "allow_greenarmour", env);
    script::bind_var(server::allow_item[I_YELLOWARMOUR-I_SHELLS], "allow_yellowarmour", env);
    script::bind_var(server::allow_item[I_QUAD-I_SHELLS], "allow_quad", env);

    script::bind_const((int)I_SHELLS, "ITEM_SHELLS", env);
    script::bind_const((int)I_BULLETS, "ITEM_BULLETS", env);
    script::bind_const((int)I_ROCKETS, "ITEM_ROCKETS", env);
    script::bind_const((int)I_ROUNDS, "ITEM_ROUNDS", env);
    script::bind_const((int)I_GRENADES, "ITEM_GRENADES", env);
    script::bind_const((int)I_CARTRIDGES, "ITEM_CARTRIDGES", env);
    script::bind_const((int)I_HEALTH, "ITEM_HEALTH", env);
    script::bind_const((int)I_BOOST, "ITEM_HEALTHBOOST", env);
    script::bind_const((int)I_GREENARMOUR, "ITEM_GREENARMOUR", env);
    script::bind_const((int)I_YELLOWARMOUR, "ITEM_YELLOWARMOUR", env);
    script::bind_const((int)I_QUAD, "ITEM_QUAD", env);

    script::bind_var(server::reservedslots, "reservedslots", env);
    script::bind_ro_var(server::reservedslots_use, "reservedslots_occupied", env);
    script::bind_ro_var(reloaded, "reloaded", env);
    
    script::bind_const((int)SHUTDOWN_NORMAL, "SHUTDOWN_NORMAL", env);
    script::bind_const((int)SHUTDOWN_RESTART, "SHUTDOWN_RESTART", env);
    script::bind_const((int)SHUTDOWN_RELOAD, "SHUTDOWN_RELOAD", env);
    
    script::bind_property<int>(
        boost::bind(script::property<int>::generic_getter, boost::ref(server::mastermode)),
        server::script_set_mastermode, "mastermode", env);
    
    script::bind_var(server::mastermode_owner, "mastermode_owner", env);
    script::bind_const((int)MM_OPEN, "MM_OPEN", env);
    script::bind_const((int)MM_VETO, "MM_VETO", env);
    script::bind_const((int)MM_LOCKED, "MM_LOCKED", env);
    script::bind_const((int)MM_PRIVATE, "MM_PRIVATE", env);
    script::bind_const((int)MM_PASSWORD, "MM_PASSWORD", env);
    
    script::bind_var(server::sv_text_hit_length, "flood_protect_text", env);
    script::bind_var(server::sv_sayteam_hit_length, "flood_protect_sayteam", env);
    script::bind_var(server::sv_mapvote_hit_length, "flood_protect_mapvote", env);
    script::bind_var(server::sv_switchname_hit_length, "flood_protect_switchname", env);
    script::bind_var(server::sv_switchteam_hit_length, "flood_protect_switchteam", env);
    script::bind_var(server::sv_kick_hit_length, "flood_protect_kick", env);
    script::bind_var(server::sv_remip_hit_length, "flood_protect_remip", env);
    script::bind_var(server::sv_newmap_hit_length, "flood_protect_newmap", env);
    script::bind_var(server::sv_spec_hit_length, "flood_protect_spectator", env);
    
    script::bind_var(server::broadcast_mapmodified, "broadcast_mapmodified", env);
    
    script::bind_var(tx_bytes, "tx_bytes", env);
    script::bind_var(rx_bytes, "rx_bytes", env);
    script::bind_var(tx_packets, "tx_packets", env);
    script::bind_var(rx_packets, "rx_packets", env);
    
    script::bind_var(server::timer_alarm_threshold, "timer_alarm_threshold", env);
    
    script::bind_var(server::enable_extinfo, "enable_extinfo", env);
    
    static char cwd[1024];
    if(getcwd(cwd,sizeof(cwd)))
        script::bind_const((const char *)cwd, "PWD", env);
    
    script::bind_const(getuid(), "UID", env); //FIXME user id is not constant
    
    script::bind_var(command_prefix, "command_prefix", env);
    script::bind_var(using_command_prefix, "use_command_prefix", env);
    
    // Utility Functions
    
    script::bind_freefunc(unset_global, "unset_global", env);
    
    script::bind_freefunc(concol, "concol", env);
    script::bind_freefunc(green, "green", env);
    script::bind_freefunc(info, "info", env);
    script::bind_freefunc(err, "err", env);
    script::bind_freefunc(grey, "grey", env);
    script::bind_freefunc(magenta, "magenta", env);
    script::bind_freefunc(orange, "orange", env);
    script::bind_freefunc(gameplay, "gameplay", env);
    script::bind_freefunc(red, "red", env);
    script::bind_freefunc(blue, "blue", env);
    script::bind_freefunc(yellow, "yellow", env);
    
    script::bind_freefunc(mins, "mins", env);
    script::bind_freefunc(secs, "secs", env);
    
    script::bind_freefunc(parse_player_command_line, "parse_player_command", env);
    
    script::bind_property<unsigned int>(
        boost::bind(script::property<unsigned int>::generic_getter, maintenance_frequency),
        set_maintenance_frequency, "maintenance_frequency", env);
    
    script::bind_freefunc(file_exists, "file_exists", env);
    script::bind_freefunc(dir_exists, "dir_exists", env);
    
    script::bind_property<bool>(
        server::get_setmaster_autoapprove, server::enable_setmaster_autoapprove, "allow_setmaster", env);
    
    script::bind_freefunc(start_http_server, "start_http_server", env);
    script::bind_freefunc(stop_http_server, "stop_http_server", env);
}
