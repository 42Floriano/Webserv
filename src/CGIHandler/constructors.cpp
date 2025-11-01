/*

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as
 published by the Free Software Foundation, either version 3 of the
 License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "CGIHandler.hpp"
#include <sstream>

static void     spawn_cgi(Process &p, Request &req);
static void     add_cgi_env(Process &p, Request &req);
// static char *create_envvar(const std::string &k, const std::string &v);

CGIHandler::CGIHandler(const std::string &cmd, Request &req, Response &res,
                       PollSet &pset):
        proc(cmd),
        read_callback(pset, this->proc.stdout(), res._body.rdbuf(), &res._headers),
        write_callback(pset, this->proc.stdin(), req._body.rdbuf())
{
        //write(proc.stdin(), "Hello", 6);
        spawn_cgi(this->proc, req);
};

/* static functions */

// static char *create_envvar(const std::string &k, const std::string &v)
// {
//         std::string svar;
//         char		*var;

//         svar = k + "=" + v;
//         var = new char[k.size() + v.size() + 2];
//         for (size_t i = 0; i <= svar.size(); i++)
//         {
//                 var[i] = svar.c_str()[i];
//         }
//         return var;
// }

static void     free_env(Process &p)
{
        for (size_t i = 0; i < p.envp.size(); ++i)
        {
                delete[] p.envp[i];
        }
}

static std::string     reformat_to_upper(const std::string &key)
{
        std::string     metaVar = "HTTP_";

        for (size_t i = 0; i < key.size(); ++i)
        {

                char    c = key[i];
                if (c == '-')
                        metaVar += '_';
                else
                        metaVar += std::toupper(c);
        }
        return (metaVar);
}

// static void	spawn_cgi(Process &p, HttpHeaders &req_headers)
// {
//         for (std::map<std::string, std::string>::const_iterator it =
//                                 req_headers.begin();
//                         it != req_headers.end(); ++it)
//         {
//                 std::string key = reformat_to_upper(it->first);
//                 p.env[key] = it->second;
//         }
//         p.spawn();
//         free_env(p);
// }

static void     add_cgi_env(Process &p, Request &req)
{
        for (std::map<std::string, std::string>::const_iterator it = req._headers.begin();
                it != req._headers.end(); ++it)
        {
                std::string key = reformat_to_upper(it->first);
                p.env[key] = it->second;
        }
       console::error <<
       Config::normalize_path(std::string(::getenv("PWD")) + "/" 
       + (p.argv.size() > 1 ? p.argv[1] : ""));
       //console::info << p.command  << std::endl;
       //console::info << p.argv[1] << std::endl;
        //exit(-1);

        p.env["GATEWAY_INTERFACE"] = "CGI/1.1";
        p.env["SERVER_PROTOCOL"]  = "HTTP/1.1";
        p.env["SERVER_SOFTWARE"]  = "webserv/1.0";
        p.env["REQUEST_METHOD"]   = req.method();
        p.env["SCRIPT_FILENAME"]  = Config::normalize_path(std::string(::getenv("PWD")) + "/" + (p.argv.size() > 1 ? p.argv[1] : ""));
        p.env["SCRIPT_NAME"]      = req.url->hier;
        p.env["PATH_INFO"]        = "";
        p.env["QUERY_STRING"]     = req.url->query;
        p.env["REDIRECT_STATUS"] = "200";

        const std::string       *value = req._headers.get("Content-Type");
        if (value)
                p.env["CONTENT_TYPE"] = *value;
        if (req._content_length > 0)
        {
                std::stringstream ss;
                ss << req._content_length;
                p.env["CONTENT_LENGTH"] = ss.str();
        }
        else p.env["CONTENT_LENGTH"] = "0";
        std::cout << req._content_length << std::endl;
        const std::string       *host_header = req._headers.get("Host");

        if (host_header) {
                std::string::size_type pos = host_header->find(':');
                if (pos != std::string::npos) {
                        p.env["SERVER_NAME"] = host_header->substr(0, pos);
                        std::stringstream       ss(host_header->substr(pos + 1));
                        p.env["SERVER_PORT"] = ss.str();
                } else {
                        p.env["SERVER_NAME"] = *host_header;
                }
        }
}

static void     spawn_cgi(Process &p, Request &req)
{
        add_cgi_env(p, req);
        p.spawn();
        free_env(p);
}
