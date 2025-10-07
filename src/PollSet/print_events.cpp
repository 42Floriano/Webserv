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

#include "PollEvents.hpp"
#include "PollSet.hpp"

void	PollSet::print_events(std::ostream &os)
{
        os << "~~~ PollSet: events ~~~" << std::endl;
        for (size_t i = 0; i < this->_pollfdset.size(); i++)
        {
                int fd = this->_pollfdset.ptr()[i].fd;
                int received_events = this->_pollfdset.ptr()[i].revents;

                os
                                << "Events on fd " << fd << "(" << received_events << "): "
                                << PollEvents::events_to_string(received_events) << std::endl;
        }
        os << "~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~~ ~~" << std::endl;
}
