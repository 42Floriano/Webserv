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
        this->_callbacks.off(event, cb);
}

void	PollSet::removeCallback(Callback cb)
{
        for (size_t i = 0; i < PollEvents::number_of_events; ++i)
        {
                short ev = PollEvents::array[i];
                this->removeCallback(ev, cb);
        }
}
