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

#ifndef XPOLLFD_HPP
# define XPOLLFD_HPP

/**
 * @brief Extend `struct pollfd` with methods
 * and operators.
 *
 * Important: `sizeof(xpollfd)` is equal to `sizeof(pollfd)`
 *
 * */

struct xpollfd: public pollfd
{

        xpollfd(void);
        xpollfd(int fd, short events = 0);
        bool	operator==(const xpollfd &rhs) const;
        xpollfd&	operator=(const pollfd &pfd);
        void	listen(short event);
        void	unlisten_to(short event);
        void	listen_all(void);
        void	unlisten_all(void);
        pollfd&	unwrap(void);

};

#endif
