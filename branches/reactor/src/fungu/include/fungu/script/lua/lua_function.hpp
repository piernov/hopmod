/*   
 *   The Fungu Scripting Engine Library
 *   
 *   Copyright (c) 2008-2009 Graham Daws.
 *
 *   Distributed under a BSD style license (see accompanying file LICENSE.txt)
 */
#ifndef FUNGU_SCRIPT_LUA_LUA_FUNCTION_HPP
#define FUNGU_SCRIPT_LUA_LUA_FUNCTION_HPP

#include "../env.hpp"
extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace fungu{
namespace script{
namespace lua{

class lua_function:public env::object
{
public:
    lua_function(lua_State *,int index, const char * name);
    lua_function(lua_State *); //function at top of stack
    ~lua_function();
    result_type call(call_arguments & args,env::frame * aFrame);
    int call(lua_State * L);
    const source_context * get_source_context()const;
private:
    void set_location(lua_State *);
    int m_ref;
    lua_State * m_lua;
    file_source_context m_location;
};

} //namespace lua
} //namespace script
} //namespace fungu

#endif
