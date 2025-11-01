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

#ifndef POLLSET_HPP
# define POLLSET_HPP

#include "Console.hpp"
#include "SimpleSet.hpp"
#include "CallbackDB.hpp"

#include <cstring>
#include <cerrno>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include <set>
#include <sys/types.h>
#include <poll.h>

/*
 *	Core of the callback engine.
 *
 *	Manages `PollCallbacks` and a `pollfd` array (the one passed to `poll`).
 *
 *	A PollCallback is the data of a fd and some (virtual) functions to be
 *	called when an event occur on a fd.
 *
 *	Each PollSet manages a map:
 *
 *		fd -> event name -> callback vector
 *
 *	as well as a `pollfd` (dynamic) array implemented as `SimpleSet`.
 *
 * */

class	PollSet
{
private:
        CallbackDB				_callbacks; /* fd->ev->cbvec */
        SimpleSet<pollfd, 4096> _pollfdset;
        std::set<Callback>		_garbage;

public:
        PollSet(void);
        ~PollSet(void);

        // Inserts callback `cb` on `event` and deduces the `fd`
        // directly from `cb`
        void			registerCallback(short event, PollCallback *cb);

        // Removes callback `cb`, on `event`, deduces the fd from cb
        void			removeCallback(short event, PollCallback *cb);

        // Removes callback `cb`, on all events, deduce the fd from cb`
        void			removeCallback(PollCallback *cb);

        // Polls the events on the fds and triggers the callbacks
        void			poll(int timeout);

        // the logic of the poll function above is split in:
        void			onPollError(int errnum);
        void			onPollTimeout(int timeout_ms);
        void			onPollSuccess(int n);

        // utils for querying the managed containers
        ssize_t			index(int fd) const;
        ssize_t			index(PollCallback *cb) const;
        void			print_events(std::ostream &os);
        int				fd(ssize_t index) const;
        bool			no_callback_left(int fd, short event) const;
        void			populate_pollset(void);
        void			empty_pollset(void);
        void			delete_callback(Callback cb);
        void			cleanup_garbage(void);
};

#endif
