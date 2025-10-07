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

int	PollSet::fd(ssize_t index) const
{
        if (-1 < index && (size_t) index < this->_pollfdset.size())
                return (this->_pollfdset.const_ptr()[index].fd);
        console::error << "PollSet: index out of bound" << std::endl;
        return (-1);
}
