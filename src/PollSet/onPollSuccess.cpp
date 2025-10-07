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

void	PollSet::onPollSuccess(int n)
{
        console::debug << "PollSuccess (" << n << ")!" << std::endl;

        // TODO: use n, it holds the number of fds
        // that have events to be processed
        (void) n;

        size_t	cursize = this->_pollfdset.size();
        for (size_t i = 0; i < cursize; i++)
        {
                int				fd = this->_pollfdset.ptr()[i].fd;
                const short&	registered_events = this->_pollfdset.ptr()[i].events;
                short&			received_events = this->_pollfdset.ptr()[i].revents;

                for(size_t ev = 0; ev < PollEvents::number_of_events; ev++)
                {
                        if (PollEvents::array[ev] & registered_events)
                        {
                                if (PollEvents::array[ev] & received_events)
                                {
                                        this->_callbacks.execute(fd, PollEvents::array[ev]);
                                        received_events &= ~(PollEvents::array[ev]);
                                }
                        }
                }
        }
}
