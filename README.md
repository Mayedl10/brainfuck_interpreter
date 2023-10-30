# brainfuck_interpreter
A configurable brainfuck interpreter!

This is the default content of the `bfconfig` file:

memsize:32768
wrap-tape:1
allow-overflow:1
file-read-default-char:0
get-input-from-console:0
output-to-console:0
continue-on-error:1
ignore-invalid:1

- memsize: size of the memory tape
- wrap-tape: set memPtr to 0 if it exceeds the memory size and vice versa
- allow-overflow: do you want to have integer overflow?
- file-read-default-char: uses this char if the input-file has rached its end
- get-input-from-console: if false, it gets the input from `bfinput`. This also means, that the input can't be changed during runtime. Set to 1 if you want real-time input
- output-to-console: if false, outputs to the `bfout` file.
- continue-on-error: do you want to crash your program if you have an integer/memory index overflow?
- ignore-invalid: crash on invalid character if set to 0
