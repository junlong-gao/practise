open Core
open Core_bench.Std
open Foo

let () =
  Command.run (Bench.make_command [
    Bench.Test.create ~name:"Fib" 
      (fun () -> ignore (Fib.fib_helper 10));
    Bench.Test.create ~name:"Fib no dp" 
      (fun () -> ignore (Fib_no_dp.fib  10));
  ])
