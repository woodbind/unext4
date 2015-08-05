#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef ENABLE_NLS
#include <libintl.h>
#include <locale.h>
#define _(a) (gettext (a))
#else
#define _(a) (a)
#endif

char *program_name;
char *device_name;

static void usage (char *prog)
{
        fprintf (stderr, _("Usage: %s [-d debug_flags] [-f] [-v] "
                           " device \n\n"), prog);

        exit (1);
}

int main (int argc, char ** argv)
{
	int c;
        int force = 0;
        int fd;

        if (argc && *argv)
                program_name = *argv;

        while ((c = getopt (argc, argv, "fv")) != EOF) {
                switch (c) {
                case 'f':
                        force++;
                        break;
                case 'v':
			break;
                default:
                        usage(program_name);
                }
        }

        if (optind > argc - 1)
                usage(program_name);

        device_name = argv[optind++];

	fd = open(device_name, O_RDONLY);	
	if (fd == -1) {		
		fprintf(stderr, _("%s:open %s failed\n"), program_name, device_name);
		exit(1);	
	}
	
	if (fd > 0)
        	close (fd);
        exit (0);
}
