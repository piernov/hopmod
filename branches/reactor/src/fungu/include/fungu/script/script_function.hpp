/*   
 *   The Fungu Scripting Engine Library
 *   
 *   Copyright (c) 2008-2009 Graham Daws.
 *
 *   Distributed under a BSD style license (see accompanying file LICENSE.txt)
 */
#ifndef FUNGU_SCRIPT_SCRIPT_FUNCTION_HPP
#define FUNGU_SCRIPT_SCRIPT_FUNCTION_HPP

#include "arguments_container.hpp"
#include "call_serializer.hpp"
#include "../generic_script_function.hpp"
#include <boost/function.hpp>
#include <vector>

namespace fungu{
namespace script{

template<typename Signature>
class script_function:public generic_script_function<Signature, std::vector<result_type>, call_serializer, error>
{
public:
    typedef any (* error_handler_function)(error_trace *);
    
    script_function(env::object::shared_ptr object, env * environment, error_handler_function error_handler)
     :m_object(object),
      m_env(environment),
      m_error_handler(error_handler)
    {
        
    }
protected:
    std::vector<result_type>::value_type call(std::vector<result_type> * args)
    {
        result_type result;

        try
        {
            env::frame callframe(m_env);
            arguments_container callargs(*args);
            
            result = m_object->call(callargs, &callframe);
        }
        catch(error e)
        {
            result = m_error_handler(create_error_trace(e, m_env->get_source_context()));
        }
        catch(error_trace * errinfo)
        {
            result = m_error_handler(errinfo);
        }
        
        return result;
    }
    
    std::vector<result_type>::value_type error_handler(int arg, error err)
    {
        return m_error_handler(create_error_trace(err,NULL));
    }
private:
    error_trace * create_error_trace(error e,const source_context * ctx)
    {
        source_context * newCtx = ctx ? ctx->clone() : NULL;
        return new error_trace(e,"",newCtx);
    }
    
    env::object::shared_ptr m_object;
    env * m_env;
    error_handler_function m_error_handler;
};

} //namespace script
} //namespace fungu

#endif
