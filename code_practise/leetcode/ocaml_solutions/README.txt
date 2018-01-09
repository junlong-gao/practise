Building simple algorithm solutions in OCaml.

1. Usual Suspects
 1.1. DP
  Looks like it is very straight forward. OCaml features a mutable array which
  works like C++ STL vector.
  Recursion and match arms works nicely.

2. Testing
 Expect test works. Using jbuild and standard ppx for inline tests.

3. Running Benchmark
 Note the core.bench usage. It would be great to have some diagram against
 input size. OCaml should have very straightforward performance
 characteristics(excluding gc)
 It would be better to have commandline specifying which function to run.

