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

#ifndef CALLBACKDB_HPP
# define CALLBACKDB_HPP

#include "PollCallback.hpp"
#include <map>
#include <vector>

// Ideas for templating this scam:
typedef int								EventEmitter; /* fd */
typedef short							Event; /* poll event */
typedef PollCallback					*Callback;
typedef std::vector<Callback>			CallbackVec;
typedef std::map<Event, CallbackVec>	CallbackMap;

// template<EventEmitter, Event, Callback>
struct	CallbackDB: public std::map<EventEmitter, CallbackMap>
{

        // Should be like this, but well...
        //int		on(Event event, EventEmitter emitter, Callback cb);
        //int		off(Event event, EventEmitter emitter, Callback cb);

        int		on(Event event, Callback cb);
        int		off(Event event, Callback cb);
        void	execute(EventEmitter emitter, Event event);
};

#endif
