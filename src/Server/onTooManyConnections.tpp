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

template<class ClientHandler>
void	Server<ClientHandler>::onTooManyConnections()
{
        console::error << "Too many clients" << std::endl;

        int		client_fd;
        Address	*client_address;

        this->unreserve_fd();

        this->accept(&client_fd, &client_address);
        console::error << "Forced client has fd " << client_fd << std::endl;
        const char *res =
                "HTTP/1.1 503 Service Unavailable" CRLF
                "Content-Length: 0" CRLF
                CRLF
                ;
        ::write(client_fd, res, std::string(res).size());
        ::close(client_fd);

        this->reserve_fd();
}
