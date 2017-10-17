## Binary Search Tree

A simple Binary Search Tree implementation that uses `void *` as both key as
well as value. Issue with that is that the user has to define a comparison
function and pass it to most of the calls defined in the header file.

If a new node is added but the key already exists, the existing node is
updated with the new value provided.

An additional constraint is that if a `value` with
value of `NULL` is added, behaviour of the binary search tree is undefined.
