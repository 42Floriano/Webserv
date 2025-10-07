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

void	PollSet::removeCallback(short event, PollCallback *cb)
{
        int	index = this->index(cb);
        if (index == -1)
        {
                console::error << "PollSet::removeCallback: index is -1" << std::endl;
        }
        else
        {
                console::debug
                                << "Removing callback " << cb << " on fd " << cb->fd()
                                << " (event: " << PollEvents::event_to_string(event) << ")"
                                << std::endl;

                this->_callbacks.off(event, cb);
                if (this->no_callback_left(cb->fd(), event))
                {
                        short& events = this->_pollfdset.ptr()[index].events;
                        events &= ~event;
                        if (events == 0)
                                this->_pollfdset.remove(index);
                }
                console::debug
                                << "Remaining events we are listening to:"
                                << PollEvents::events_to_string(this->_pollfdset.ptr()[index].events)
                                << std::endl;
        }
}

void	PollSet::removeCallback(Callback cb)
{
        for (size_t i = 0; i < PollEvents::number_of_events; ++i)
        {
                short ev = PollEvents::array[i];
                this->removeCallback(ev, cb);
        }
}

void	PollSet::destroyCallback(Callback cb)
{
        this->removeCallback(cb);
        delete cb;
}

void	PollSet::removeCallbacks(int fd, short event)
{
        CallbackVec &cbvec = this->_callbacks[fd][event];
        for (CallbackVec::size_type i = 0; i < cbvec.size(); ++i)
        {
                this->removeCallback(event, this->_callbacks[fd][event][i]);
        }
}

#include <set>
void	PollSet::removeCallbacks()
{
        std::map<EventEmitter, CallbackMap>::iterator iter = this->_callbacks.begin();
        std::set<Callback>	clean_up_set;
        while (iter != this->_callbacks.end())
        {
                int fd = iter->first;
                for (size_t i = 0; i < PollEvents::number_of_events; ++i)
                {
                        short ev = PollEvents::array[i];
                        CallbackVec &cbvec = this->_callbacks[fd][ev];
                        for (CallbackVec::size_type i = 0; i < cbvec.size(); ++i)
                        {
                                Callback	cb = this->_callbacks[fd][ev][i];
                                this->removeCallback(ev, cb);
                                clean_up_set.insert(cb);
                        }
                        this->removeCallbacks(fd, ev);
                }
                iter++;
        }

        std::set<Callback>::iterator	cb;
        for (cb = clean_up_set.begin(); cb != clean_up_set.end(); ++cb)
                delete (*cb);
}
