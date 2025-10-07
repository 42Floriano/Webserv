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

#ifndef POLLABLEREADABLE_HP
# define POLLABLEREADABLE_HP

# include <unistd.h>
# include <cerrno>
# include "PollableFile.hpp"

class	PollableReadable: public PollableFile
{

public :
        size_t	bytesread;
        virtual	void	on_data_callback(void);
        virtual	void	on_eof_callback(void);
        virtual	void	on_error_callback(int e);

private:
        virtual ssize_t	_read(char *buf, size_t buflen);

public:
        PollableReadable(int fd, std::streambuf *buff);

protected:
        void	_onPOLLIN(void);
};

#endif
