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

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include "Server.hpp"
#include "HttpClient.hpp"
#include "ConfigIter.hpp"

struct Webserv
{
        static void	catchsig(int sig);
        static void	init_console(char *option);
        static char	*parse_args(int ac, char **av);

        static int	signal;

        Webserv(const char *config_filename);
        ~Webserv();

        Config	conf;
        PollSet	aio;

        int		configure(const char *config_path);
        void	init();
        void	run(int timeout);
};

#endif
