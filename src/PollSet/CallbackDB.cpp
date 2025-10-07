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
#include "PollEvents.hpp"
#include "CallbackDB.hpp"

#include <iostream>
#include <cstddef>

int	CallbackDB::on(Event event, Callback cb)
{

        (*this)[cb->fd()][event].push_back(cb);

        return (0);
}

int	CallbackDB::off(Event event, Callback cb)
{
        CallbackVec::iterator it = (*this)[cb->fd()][event].begin();
        CallbackVec::const_iterator end = (*this)[cb->fd()][event].end();

        for (; it != end; ++it)
        {
                if (*it == cb) /* comparing pointers (not PollCallbacks) */
                {
                        (*this)[cb->fd()][event].erase(it);
                        break;
                }
        }
        return (0);
}

void	CallbackDB::execute(EventEmitter fd, Event event)
{
        console::debug
                        << "Executing " << PollEvents::event_to_string(event)
                        << " callback on fd " << fd
                        << std::endl;
        ++console::debug;

        CallbackVec::size_type i;
        for (i = 0; i < (*this)[fd][event].size(); i++)
        {
                if ((*this)[fd][event][i] != NULL)
                        ((*this)[fd][event][i]->on)(event);
                else
                        throw std::runtime_error("WTF: exec a NULL callback ???");
        }

        --console::debug;
        console::debug
                        << "Done executing: " << PollEvents::event_to_string(event)
                        << " callback on fd " << fd
                        << std::endl;
}
