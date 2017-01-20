# smlr
Truncates stdin to a maximum fixed size, abbreviating the output if over the specified length.

#### Usage
`[source] | smlr [-s SIZE] [-a ALIGNMENT]`
* `-s`: Size of output. If equal or greater than input, input is relayed to s unchanged"). Default value is 5.
* `-a`: Alignment of output. Can be either `left` or `right`. Default value is middle.

#### Examples
Bring your git branch down to a fixed-size
```
> git rev-parse --abbrev-ref HEAD | smlr -s 10
> feat...-13
```
Deal with too many letters
```
> echo "abcdefghijkl" | smlr -s 10 -a right
> ...fghijkl
```
A date string that's just too long
```
> date | smlr -s 10
> Thu ...017
```
Repeat the string if it turns out to be equal, or smaller than, the size given
```
> echo "abc" | smlr -s 5
> abc
```

#### Installation
Just run a `make` to build it. If everything works out, you'll have a binary in `build/rel/smlr`. Symlink or copy that sucker to a path directory, such as `/usr/bin`.
