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

#ifndef HTTPCLIENT_HPP
# define HTTPCLIENT_HPP

#include "Client.hpp"
#include "ResponseHandler.hpp"

class HttpClient: public Client
{

public:
        HttpClient(PollSet &pset, int fd, Address *addr, ConfigItem &server_cfg);
        ~HttpClient(void);

protected:
        void			onData();
        void			onWritable();
        void			on_nothing_to_write(void);
        virtual void	handleRequest(void);

protected:
        Request			incoming;
        Response		outgoing;
        ResponseHandler _handler;

public:
        Request&	req(void);
        Response&	res(void);
        bool		handled;
};

std::ostream& operator<<(std::ostream &os, const HttpClient &client);

#endif
