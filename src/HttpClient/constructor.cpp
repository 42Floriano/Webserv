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

#include "HttpClient.hpp"

HttpClient::HttpClient(PollSet &pset, int clientfd, Address *clientaddr,
                       ConfigItem &cfg):
        Client(pset, clientfd, clientaddr),
        incoming(*this->rbuf.rdbuf()),
        outgoing(*this->wbuf.rdbuf()),
        _handler(incoming, outgoing, pset, cfg),
        handled(false)
{
        console::info << "new " << *this << std::endl;
}

HttpClient::~HttpClient(void)
{
        console::info << "Deconstructing client" << std::endl;
        try
        {
                if (this->_handler.isCGI())
                        delete ((CGIHandler *)(this->_handler.internal_handler));
                else
                {
                        console::info << "Deconstructing internal handler for non CGI req" << std::endl;
                        this->_pset.removeCallback((PollCallback *)(this->_handler.internal_handler));
                }
        }
        catch (const std::exception &err)
        {
                console::debug << "There was no POLLOUT callback to remove" << std::endl;
        }
}
