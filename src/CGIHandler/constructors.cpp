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

static void	spawn_cgi(Process &p, HttpHeaders &req_headers);
static char *create_envvar(const std::string &k, const std::string &v);

CGIHandler::CGIHandler(const std::string &cmd, Request &req, Response &res,
                       PollSet &pset):
        proc(cmd),
        read_callback(this->proc.stdout(), pset, res._body.rdbuf(), &res._headers),
        write_callback(this->proc.stdin(), pset, req._body.rdbuf())
{
        spawn_cgi(this->proc, req._headers);
};

/* static functions */

static char *create_envvar(const std::string &k, const std::string &v)
{
        std::string svar;
        char		*var;

        svar = k + "=" + v;
        var = new char[k.size() + v.size() + 2];
        for (size_t i = 0; i <= svar.size(); i++)
        {
                var[i] = svar.c_str()[i];
        }
        return var;
}

static void     free_env(Process &p)
{
        for (size_t i = 0; i < p.envp.size(); ++i)
        {
                delete[] p.envp[i];
        }
}

static void	spawn_cgi(Process &p, HttpHeaders &req_headers)
{
        std::map<std::string, std::string>::iterator	it = req_headers.begin();
        std::map<std::string, std::string>::iterator	end = req_headers.end();

        for (; it != end; ++it)
        {
                p.envp.push_back(create_envvar(it->first, it->second));
        }
        p.spawn();
        free_env(p);
}
