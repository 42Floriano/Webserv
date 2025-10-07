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

#include "PollSet.hpp"

ssize_t		PollSet::index(int fd) const
{
        for (size_t it = 0; it < this->_pollfdset.size(); ++it)
        {
                if (this->_pollfdset.const_ptr()[it].fd == fd)
                        return (it);
        }
        return (-1);
}

ssize_t		PollSet::index(PollCallback *cb) const
{
        if (!cb)
                return (-1);
        return (this->index(cb->fd()));
}
