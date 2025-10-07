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

public:
        PollSet(void);
        ~PollSet(void);

        // Inserts callback `cb` in the underlying map for the given
        // `fd` and `event`
        void			registerCallback(int fd, short event, PollCallback *cb);

        // Inserts callback `cb` on `event` and deduces the `fd`
        // directly from `cb`
        void			registerCallback(short event, PollCallback *cb);

        // Inserts callback `cb` on all events and deduces the `fd`
        // directly from `cb`.
        void			registerCallback(PollCallback *cb);

        // Removes callback `cb`, on `event` for the given `fd`.
        void			removeCallback(int fd, short event, PollCallback *cb);

        // Removes callback `cb`, on `event`, deduces the fd from cb
        void			removeCallback(short event, PollCallback *cb);

        // Removes callback `cb`, on all events, deduce the fd from cb`
        void			removeCallback(PollCallback *cb);

        // Like removeCallback(cb) but it also destroies the callback.
        void			destroyCallback(PollCallback *cb);

        // Removes all callbacks on `event` on `fd`
        void			removeCallbacks(int fd, short event);

        // Removes all callbacks on all events on `fd`;
        void			removeCallbacks(int fd);

        // Removes all callbacks on all events on `fd`;
        void                    removeCallbacks(void);

        // Like removeCallbacks but also destroies all callback objects
        void			destroyCallbacks(int fd);

        // Like `destoryCallbacks` but also closes the `fd`.
        void			close(int fd);

        // Like `close` but deduces the `fd` from `cb`.
        void			disconnect(PollCallback *cb);

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
};

#endif
