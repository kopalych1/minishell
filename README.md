
# Minishell 42

A small recreation of Bash.




## Documentation

The project must be cloned with --recursive flag:
```bash
git clone --recursive https://github.com/kopalych1/minishell.git
```
If wasn't cloned recursively, submodules can be pulled after cloning with:
```bash
git submodule update --init --recursive
```


## Running Tests

To run minishell, run the following command

```bash
make run
```
or
```bash
make; ./minishell
```

#### Running with valgrind

```bash
make vrun
```

will run minishell with valgrind using necessary valgrind flags
