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

#include "Process.hpp"

void	Process::_fork()
{
        errno = 0;
        this->pid = ::fork();
        if (this->pid > 0)
                console::info << "Created process " << this->pid << std::endl;
        else
        {
                //console::info.off();
                //console::debug.off();
                //console::error.off();
        }
        int e = errno;
        if (this->pid == -1)
                throw e;
};
