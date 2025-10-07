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

#include "Webserv.hpp"

void	Webserv::init()
{

        ::signal(SIGINT, Webserv::catchsig);
        ::signal(SIGPIPE, SIG_IGN);

        ConfigIter	server_config = ConfigIter::begin(this->conf, "server");
        ConfigIter	end = ConfigIter::end(this->conf);


        for (; server_config != end; ++server_config)
        {
                const std::string *host;
                const std::string *port;
                host = (*(*server_config)["host"])[0];
                port = (*(*server_config)["listen"])[0];
                if (host && port)
                {
                        try
                        {
                                new Server<HttpClient>(this->conf, this->aio, *host, *port);
                        }
                        catch (int)
                        {
                                // most likely accept faild
                                // TODO: handle it somewhere else, the trycatch here
                                // is ugly af
                        }
                }
                else
                {
                        // host and port are missing from server configItem
                        // is this handled in by the specs? yes / no
                }
        }
}
