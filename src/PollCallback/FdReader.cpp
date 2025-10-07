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

#include "Console.hpp"
#include "PollSet.hpp"
#include "PollableReadable.hpp"
#include "FdReader.hpp"

FdReader::FdReader(int fd, PollSet &pset, std::streambuf *buff):
        PollableReadable(fd, buff),
        pset(pset),
        done(false)
{
        this->buffer_size(4096);
        this->_buffer.std::ios::rdbuf(buff);
        pset.registerCallback(POLLIN, this);

        console::debug
                        << "new FdReader on fd " << this->fd()
                        << " with buffer size: " << this->buffer_size()
                        << std::endl;
}

void	FdReader::on_data_callback(void)
{
        console::debug
                        << "FdReader: on-data: total bytes read: " << this->bytesread
                        << std::endl;
}

void	FdReader::on_eof_callback(void)
{
        console::debug
                        << "FdReader: end-of-file: total bytes read: " << this->bytesread
                        << std::endl;
        this->done = true;
        this->close();
        pset.removeCallback(POLLIN, this);
}

FdReader::~FdReader(void)
{
        this->pset.removeCallback(POLLIN, this);
}
