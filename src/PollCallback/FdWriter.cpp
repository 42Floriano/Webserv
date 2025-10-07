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

#include "FdWriter.hpp"

FdWriter::FdWriter(int fd, PollSet &pset, std::streambuf *buff):
        PollableWritable(fd, buff),
        pset(pset)
{
        this->buffer_size(4096);
        pset.registerCallback(POLLOUT, this);
        console::debug
                        << "new FdWriter on fd " << this->fd()
                        << " with buffer size: " << this->buffer_size()
                        << std::endl;
}

void	FdWriter::on_nothing_to_write_callback(void)
{
        this->nothing_to_write = true;
}

void	FdWriter::on_write_success_callback(void)
{
        this->nothing_to_write = false;
}

FdWriter::~FdWriter(void)
{
        this->pset.removeCallback(POLLOUT, this);
}
