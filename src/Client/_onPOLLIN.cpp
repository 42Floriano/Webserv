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

#include "Client.hpp"

void	Client::_onPOLLIN(void)
{
        console::debug
                        << "Client[" << this->fd() << "]: Trying to read "
                        << Client::buffer_size << "bytes"
                        << std::endl;

        ssize_t readlen = this->read((char *)rchunk.data(), Client::buffer_size);

        switch (readlen)
        {
        case -1:
                this->onError();
                break;
        case 0:
                this->onDisconnect();
                break;
        default:
                this->bytesread += readlen;
                this->rchunk.resize(readlen);
                this->rbuf.clear();
                this->rbuf << rchunk;
                this->onData();
        }
}
