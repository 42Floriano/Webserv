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

template <class ClientHandler>
void			Server<ClientHandler>::reserve_fd()
{
        if (this->reserved_fd == -1)
        {
                console::debug << "reserving fd for server " << this->fd() << std::endl;

                this->reserved_fd = ::dup(this->fd());

                if (this->reserved_fd == -1)
                {
                        throw std::runtime_error("Server: could not reserve fd");
                }
                else
                {
                        console::debug << "reserved:  " << this->reserved_fd << std::endl;
                }
        }
}

