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

std::string	PollEvents::events_to_string(short events)
{
        std::string	str;

        str += '[';
        for (size_t e = 0; e < PollEvents::number_of_events; e++)
        {
                int event = PollEvents::array[e];
                if (events & event)
                {
                        str += event_to_string(event);
                        str += ',';
                }
        }

        if (str[str.size() - 1] == ',')
                str[str.size() - 1] = ']';
        else
                str += ']';
        return str;
}
