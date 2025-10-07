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

#include "CGIReader.hpp"

CGIReader::CGIReader(int fd, PollSet &pset, std::streambuf *buf,
                     HttpHeaders *hdrs):
        FdReader(fd, pset, buf),
        headers_parsed(false),
        headers(hdrs)
{
        pset.registerCallback(POLLHUP, this);
}


CGIReader::~CGIReader()
{
        this->pset.removeCallback(POLLHUP, this);
}
