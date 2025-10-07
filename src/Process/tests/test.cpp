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

#include <iomanip>
#include <cstdlib>
#include <signal.h>
#include "FdReader.hpp"
#include "Process.hpp"

class	MyReader: public FdReader
{
public:
        MyReader(int fd, PollSet &pset, std::streambuf *buf): FdReader(fd, pset, buf) {}

        void	on_data_callback(void)
        {
                console::debug << this->_buffer.rdbuf() << std::endl;
        }

        void	_onPOLLHUP(void)
        {
                console::debug << "Poll Hang up received" << std::endl;
        }
};

int	main(int ac, char **av)
{
//		(void) ac;
//		(void) av;

//		char buffer[4096];

//		Process p("/bin/ls -l");
//		p.spawn();
//		while (!p.is_done())
//			continue ;
//		ssize_t readlen = read(p.stdout(), buffer, 4096);
//		buffer[readlen] = 0;
//		std::cout << "Readlen: " << readlen << std::endl;
//		std::cout << "Buffer:" << buffer << std::endl;



        signal(SIGPIPE, SIG_IGN);

        PollSet	pset;

        if (ac > 1)
        {
                std::stringbuf	buf;
                Process	p(av[1]);
                MyReader *cb = new MyReader(p.stdout(), pset, &buf);
                pset.registerCallback(POLLIN, cb);
                pset.registerCallback(POLLHUP, cb);
                p.spawn();
        }


        while (1)
                pset.poll(1000);
        return (0);
}
