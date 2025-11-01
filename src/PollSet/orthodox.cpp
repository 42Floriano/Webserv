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

#include "cstdlib"
#include "PollSet.hpp"
#include "PollEvents.hpp"

// Default constructor

PollSet::PollSet(void)
{

}

// Deconstructor
typedef PollCallback *Callback;
typedef std::vector<PollCallback *> CallbackQueue;
typedef short Event;
typedef std::map<Event, CallbackQueue> CallbackMap;
typedef int EventEmitter;

PollSet::~PollSet(void)
{
        CallbackDB::iterator it = this->_callbacks.begin();
        CallbackDB::iterator it_end = this->_callbacks.end();

        for (; it != it_end; it++)
        {
                EventEmitter fd = it->first;
                console::error << "fd: " << fd << std::endl;
                CallbackMap::iterator jt = it->second.begin();
                CallbackMap::iterator jt_end = it->second.end();

                for (; jt != jt_end; jt++)
                {
                        Event event = jt->first;
                        console::error << "event: " << PollEvents::event_to_string(event) << std::endl;
                        CallbackQueue::iterator kt = jt->second.begin();
                        CallbackQueue::iterator kt_end = jt->second.end();

                        for (; kt != kt_end; ++kt)
                        {
                                Callback cb = *kt;
                                if (cb->fd != fd)
                                {
                                        throw std::runtime_error("callback fd is not the same as event emitter fd");
                                }
                                delete_callback(cb);
                        }
                }
        }
        cleanup_garbage();
}
