# mateinfoUB-2024

## `CPREP`

This uses `cprep`, writen with love by Bicsi.
However, with less love, he did not include the ability to use checkers.

I implemented checker support on [this fork](https://github.com/theodormoroianu/cprep), which you need to clone and build:

```Bash
git clone https://github.com/theodormoroianu/cprep
cd cprep
pip3 install .
```

## Structure

 * `sol.cpp` is the main intended solution.
 * Any other source file starting with `sol_` will be considered alternative solution.
 * `gen.cpp` generates testcases.

## Creating The Tests

Run:
```Bash
$ cprep generate
```

## Checking The Tests

Run:
```Bash
$ cprep evaluate
```