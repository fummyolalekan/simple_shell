#include "shell.h"

<<<<<<< HEAD
/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
=======
int main(int argc __attribute__((unused)), char **argv)
{
	appData_t *appData = NULL;
	int cLoop;
	void (*func)(appData_t *);

	appData = _initData(argv);

	do {
		signal(SIGINT, _ctrlC);
		_prompt();

		_getline(appData);

		appData->history = _strtow(appData->buffer, COMMAND_SEPARATOR, ESCAPE_SEPARATOR);

		if (appData->history == NULL)
		{
			_freeAppData(appData);
			free(appData);
			continue;
		}

		for (cLoop = 0; appData->history[cLoop] != NULL; cLoop++)
		{
			appData->arguments = _strtow(appData->history[cLoop], SEPARATORS, ESCAPE_SEPARATOR);

			if (appData->arguments == NULL)
			{
				_freeAppData(appData);
				_freeEnvList(appData->env);
				appData->env = NULL;
				free(appData);
				appData = NULL;
				break;
			}

			appData->commandName = _strdup(appData->arguments[0]);

			if (appData->commandName != NULL)
			{
				func = _getCustomFunction(appData->commandName);
				if (func != NULL)
					func(appData);
				else
					_execCommand(appData);
			}
			_freeCharDoublePointer(appData->arguments);
			appData->arguments = NULL;
			free(appData->commandName);
			appData->commandName = NULL;
		}

		_freeAppData(appData);
	} while (1);
>>>>>>> fd96628629d7c08bdf3105882fef90c2c4f873fd
	return (EXIT_SUCCESS);
}
