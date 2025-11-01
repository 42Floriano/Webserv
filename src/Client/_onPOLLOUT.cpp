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

void	Client::dispatch_wchunk(void)
{
        console::error("Client::dispatch_wchunk");
        errno = 0;
        ssize_t writelen = this->write(this->wchunk.data(), this->wchunk.size());

        // on error
        if (writelen == -1)
        {
                console::error << "Write error: " << strerror(errno) <<std::endl;
        }

        // on success
        this->byteswritten += writelen;

        if (-1 < writelen && writelen < (ssize_t) this->wchunk.size())
        {
                console::error << "Partial write" << std::endl;
                throw std::runtime_error("Unhandled partial write");
        }
        console::error("");
}

void	Client::prepare_wchunk(void)
{
        this->_prepare_chunk();

        this->wbuf.clear();
        this->wchunk.resize(this->buffer_size);
        this->wbuf.read((char *)wchunk.data(), wchunk.size());
        wchunk.resize(this->wbuf.gcount());
}

void	Client::_onPOLLOUT(void)
{
        // prepares the buffer
        this->prepare_wchunk();

        if (this->wchunk.size() > 0)
        {
                this->dispatch_wchunk();
        }
        else
        {
                this->on_nothing_to_write();
        }
}
