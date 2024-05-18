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

## CMS Checker

We have to upload a staticly linked checker to CMS. To do this, we need to compile the checker with the following command:
```Bash
g++ -O2 -static CMS_checker.cpp -lstdc++ -lm -lc -std=c++20 -s -o checker
```

Use `prajitura-cu-mujdei/CMS_checker.cpp` as example.
The documentation is [here](https://cms.readthedocs.io/en/v1.4/Task%20types.html#tasktypes-checker).