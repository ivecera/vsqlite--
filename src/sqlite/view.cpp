/*##############################################################################
 VSQLite++ - virtuosic bytes SQLite3 C++ wrapper

 Copyright (c) 2006-2014 Vinzenz Feenstra vinzenz.feenstra@gmail.com
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 * Neither the name of virtuosic bytes nor the names of its contributors may
   be used to endorse or promote products derived from this software without
   specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

##############################################################################*/

#include <fmt/core.h>
#include <sqlite/connection.hpp>
#include <sqlite/execute.hpp>
#include <sqlite/view.hpp>

namespace sqlite{
    view::view(connection & con)
        :m_con(con){
    }

    view::~view(){
    }
    void view::create(bool temporary,
                      std::string const & database,
                      std::string const & alias,
                      std::string const & sql_query){
        std::string cmd = fmt::format("CREATE {1} VIEW {2}.{3} AS {4};",
                                      temporary ? "TEMPORARY" : "", database,
                                      alias, sql_query);
        execute(m_con,cmd.c_str(),true);
    }

    void view::create(bool temporary,
                      std::string const & alias,
                      std::string const & sql_query){
        std::string cmd = fmt::format("CREATE {1} VIEW {2} AS {3};",
                                      temporary ? "TEMPORARY" : "", alias,
                                      sql_query);
        execute(m_con,cmd.c_str(),true);
    }

    void view::drop(std::string const & alias){
        std::string cmd = fmt::format("DROP VIEW {1};", alias);
        execute(m_con,cmd.c_str(),true);
    }

    void view::drop(std::string const & database, std::string const & alias){
        std::string cmd = fmt::format("DROP VIEW {1}.{2};", database, alias);
        execute(m_con,cmd.c_str(),true);
    }
}

