#include "../include/minishell.h"


typedef struct	s_testcase {
	const char	*input;
	int			expected_argc;
	char		**expected_argv;
} t_testcase;


#define CREATE_TESTCASE(input, ...) ({									\
	const char *words[] = {__VA_ARGS__};								\
	create_testcase(input, sizeof(words) / sizeof(words[0]), words);	\
})


t_testcase	create_testcase(const char *input, int count, const char *words[])
{
	t_testcase	testcase;

	testcase.input = input;
	testcase.expected_argc = count;
	testcase.expected_argv = malloc(count * sizeof(char *));
	for (int i = 0; i < count; i++)
		testcase.expected_argv[i] = strdup(words[i]);
	return (testcase);
}
void	free_testcase(t_testcase *testcase)
{
	for (int i = 0; i < testcase->expected_argc; i++)
		free(testcase->expected_argv[i]);
	free(testcase->expected_argv);
}


void	run_test(const char *line, int ex_argc, char **ex_argv)
{
	static int		test_n = 1;
	ssize_t			argc;
	char			**argv;
	unsigned char	test_passed;
	t_hashmap		env;


	hm_init(&env);
	env.set(&env, "TEST", "123", 0);

	argc = calculate_argc((char *)line);
	argv = args_parse((char *)line, &env);

	printf("--------TEST %d--------\n", test_n++);
	if (argc != ex_argc)
		printf("argc: ["BRED"FAIL"CRESET"]\n"RED"%ld"CRESET"\n"GRN"%d"CRESET"\n", argc, ex_argc);
	else
		printf("argc: ["GRN"PASS"CRESET"]\n");

	test_passed = 1;
	for (int i = 0; i < ex_argc; i++)
	{
		if (ft_strcmp(argv[i], ex_argv[i]))
		{
			test_passed = 0;
			printf("argv: ["RED"FAIL"CRESET"]:\n\n");
			printf("\"%s\"\n", line);
			for (int j = 0; argv[j]; j++)
				printf("\""RED"%s"CRESET"\", ", argv[j]);
			printf("\n");
			for (int j = 0; j < ex_argc; j++)
				printf("\""GRN"%s"CRESET"\", ", ex_argv[j]);
			printf("\n");
			break;
		}
	}
	if (test_passed)
		printf("argv: ["GRN"PASS"CRESET"]\n");

	hm_free(&env);
}


int	main(void)
{
	t_testcase	testcases[] = {

		CREATE_TESTCASE("sbhfe dgiurt ifjroe firoje fior", "sbhfe", "dgiurt", "ifjroe", "firoje", "fior"),

		// Spaces
		CREATE_TESTCASE("ls         -lap", "ls", "-lap"),
		CREATE_TESTCASE("  ls         -lap    ", "ls", "-lap"),
		CREATE_TESTCASE("  ls         -lap", "ls", "-lap"),
		CREATE_TESTCASE("   ls-lap", "ls-lap"),
		CREATE_TESTCASE("   ls-lap   ", "ls-lap"),
		CREATE_TESTCASE("ls-lap   ", "ls-lap"),
		CREATE_TESTCASE("\t\tls  -lap   ", "ls", "-lap"),

		// Quotes
		CREATE_TESTCASE(" ABC  '123'  ''   ", "ABC", "123", ""),
		CREATE_TESTCASE(" ABC  \"'123'  ''  \"   ", "ABC", "'123'  ''  "),
		CREATE_TESTCASE("echo \"Text with 'single' quotes\"", "echo", "Text with 'single' quotes"),
		CREATE_TESTCASE("echo 'Text with \"double\" quotes'", "echo", "Text with \"double\" quotes"),

		CREATE_TESTCASE("grep 'main' file.c", "grep", "main", "file.c"),
		CREATE_TESTCASE("cat file1.txt file2.txt", "cat", "file1.txt", "file2.txt"),
		CREATE_TESTCASE("find . -name '*.c'", "find", ".", "-name", "*.c"),

		CREATE_TESTCASE("echo $TEST", "echo", "123"),
		CREATE_TESTCASE("echo ~", "echo", "~"),

		// Pipes
		CREATE_TESTCASE("WWWD < AAAA", "WWWD", "<", "AAAA"),
		CREATE_TESTCASE("WWWD | AAAA", "WWWD", "|", "AAAA"),
		CREATE_TESTCASE("dDKIWu | dDKIWu >> 33te", "dDKIWu", "|", "dDKIWu", ">>", "33te"),
		CREATE_TESTCASE("dDKIWu ||| dDKIWu << 33te", "dDKIWu", "|", "|", "|", "dDKIWu", "<<", "33te"),

		CREATE_TESTCASE("WWWD|AAAA", "WWWD", "|", "AAAA"),
		CREATE_TESTCASE("WWWD|||AAAA", "WWWD", "|", "|", "|", "AAAA"),
		CREATE_TESTCASE("dDKIWu>>dDKIWu|||", "dDKIWu", ">>", "dDKIWu", "|", "|", "|"),
		CREATE_TESTCASE("|||dDKIWu<<dDKIWu|||", "|", "|", "|", "dDKIWu", "<<", "dDKIWu", "|", "|", "|"),
		CREATE_TESTCASE("|TEST|||", "|", "TEST", "|", "|", "|"),
	};
	const size_t	testnum = sizeof(testcases) / sizeof(t_testcase);


	for (size_t i = 0; i < testnum; i++)
	{
		run_test(
			testcases[i].input,
			testcases[i].expected_argc,
			testcases[i].expected_argv
		);
	}
	for (size_t i = 0; i < testnum; i++)
		free_testcase(&testcases[i]);
	return (0);
}
