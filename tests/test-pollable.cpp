#include <fcntl.h>
#include "PollCallback/FdReader.hpp"
#include "PollCallback/FdWriter.hpp"

int	main(int ac, char **av)
{
        PollSet	pset;

        if (ac == 5)
        {
                std::stringbuf	buff;

                char				*infile = av[1];
                int					in_fd = open(infile, O_RDONLY);
                FdReader			readable_callback(in_fd, pset, &buff);

                char				*outfile = av[2];
                int					out_fd = open(outfile, O_WRONLY | O_CREAT, 0644);
                FdWriter			writable_callback(out_fd, pset, &buff);


                std::stringbuf	buff2;

                char				*infile2 = av[3];
                int					in_fd2 = open(infile2, O_RDONLY);
                FdReader			readable_callback2(in_fd2, pset, &buff2);

                char				*outfile2 = av[4];
                int					out_fd2 = open(outfile2, O_WRONLY | O_CREAT, 0644);
                FdWriter			writable_callback2(out_fd2, pset, &buff2);
                while (1)
                {
                        pset.poll(1000);
                        if (readable_callback.done && writable_callback.nothing_to_write
                                        && readable_callback2.done && writable_callback2.nothing_to_write)
                        {
                                pset.removeCallback(POLLOUT, &writable_callback);
                                pset.removeCallback(POLLOUT, &writable_callback2);
                                break;
                        }
                }
                return (0);
        }
        return (1);
}
