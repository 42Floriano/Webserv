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

#ifndef POLLCALLBACK_HPP
# define POLLCALLBACK_HPP

# include "Console.hpp"

class PollSet;

class	PollCallback
{

public:
        PollSet&			pset;
        int				fd;
        bool			is_closed;

        PollCallback(PollSet &pset, int fd);
        virtual ~PollCallback(void);

        void			on(short pollevent);
        int				close(void);
        void			unregister(void);

protected:
        virtual void	_onPOLLIN(void);
        virtual void	_onPOLLPRI(void);
        virtual void	_onPOLLOUT(void);
        virtual void	_onPOLLRDHUP(void);
        virtual void	_onPOLLHUP(void);
        virtual void	_onPOLLERR(void);
        virtual void	_onPOLLNVAL(void);
};

#endif
