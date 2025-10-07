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

void	Process::_create_channels(void)
{

        int	infd[2];
        int	outfd[2];
        int	errfd[2];

        ::pipe(infd);
        ::pipe(outfd);
        ::pipe(errfd);

        this->stdio.push_back(infd[0]);
        this->stdio.push_back(outfd[1]);
        this->stdio.push_back(errfd[1]);

        this->real_stdio.push_back(infd[1]);
        this->real_stdio.push_back(outfd[0]);
        this->real_stdio.push_back(errfd[0]);

}
