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

template<typename ClientHandler>
void	Server<ClientHandler>::onConnection(int clientfd, Address *clientaddr)
{
        if (clientfd == -1)
        {
                console::error << "accept failed" << std::endl;
                this->onTooManyConnections();
        }
        else
        {
                console::info
                                << *this << " has a new connection (fd " << clientfd << ")"
                                << std::endl;
                ++console::info;
                ClientHandler	*client = new ClientHandler(
                        this->_pset,
                        clientfd,
                        clientaddr,
                        this->config);
                client->state = Socket::connected;
                --console::info;

                this->_pset.registerCallback(POLLIN, client);
                this->_pset.registerCallback(POLLERR, client);
                this->_pset.registerCallback(POLLHUP, client);
        }
}
