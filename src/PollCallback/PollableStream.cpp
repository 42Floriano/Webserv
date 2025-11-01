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

#include <unistd.h>
#include "PollableStream.hpp"

PollableStream::PollableStream(PollSet &pset, int fd, std::streambuf *buf):
        PollCallback(pset, fd), BUFFER_SIZE(4096), _buffer(buf)
{
}

size_t	PollableStream::buffer_size(void) const
{
        return this->BUFFER_SIZE;
}

void	PollableStream::buffer_size(size_t newval)
{
        this->BUFFER_SIZE = newval;
}
