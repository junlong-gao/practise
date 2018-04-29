A somewhat random collection of OCaml stuff

with new dune and ocaml 4.06:
https://blog.janestreet.com/repeatable-exploratory-programming/

Ask utop to load the package for you
and then utop
# #use "rec02.ml"

The final step in the exercise above (exit the toplevel) is exceedingly
important. The best workflow when using the toplevel to test functions is:

- Edit some code in a file.
- Load the code in the toplevel with #use.
- Interactively test the code.
- Exit the toplevel.

Suppose you wanted to fix a bug in your code: it's tempting to not exit the
toplevel, edit the file, and re-issue the #use directive into the same toplevel
session. Resist that temptation. The "stale code" that was loaded from an
earlier #use directive in the same session can cause surprising things to
happen—surprising when you're first learning the language, anyway. So always
exit the toplevel before re-using a file.

Build and Run Tests:
Take a look at sum.ml and sum_test.ml
```
ocamlbuild -package oUnit sum_test.byte
```
