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

#ifndef SERVER_HPP
# define SERVER_HPP

#include <unistd.h>
#include "Socket.hpp"
#include "PollSet.hpp"
#include "Client.hpp"
#include "Config.hpp"

// TODO: un-template this class
template<typename ClientHandler>
class	Server: public PollSock
{
public:
        //TODO: put the global pset in PollSet static fields, not here
        static PollSet	global_pset;

        Server(ConfigItem &cfg, PollSet &pset, const std::string &host,
               const std::string &port);
        ~Server();

        ConfigItem&	config;
        int			reserved_fd;

        void		reserve_fd();
        void		unreserve_fd();

        void	onConnection(int clientfd, Address *clientaddr);
        void	onTooManyConnections();
};

template<class ClientHandler>
std::ostream& operator<<(std::ostream &os, const Server<ClientHandler>& server)
{
        return os << "Server " << &server << " (fd " << server.fd() << ")";
}

# include "constructors.tpp"
# include "deconstructor.tpp"
# include "reserve_fd.tpp"
# include "unreserve_fd.tpp"
# include "onConnection.tpp"
# include "onTooManyConnections.tpp"

#endif
