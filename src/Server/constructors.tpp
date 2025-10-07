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
Server<ClientHandler>::Server(ConfigItem &server_cfg, PollSet &pset,
                              const std::string &host,
                              const std::string &port):
        PollSock(pset, AF_INET, SOCK_STREAM, IPPROTO_TCP),
        config(server_cfg),
        reserved_fd(-1)
{
        this->listen(host, port);
        this->reserve_fd();

        console::info << "new " << *this << ": " << std::endl;
        ++console::info;
        console::info << "listening at " << this->address << std::endl;
        console::info << "reserved fd: " << this->reserved_fd << std::endl;
        --console::info;
}
