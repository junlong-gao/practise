open Core
open Core_bench

let rec qs l =
   match l with
   | []      -> []
   | p :: rs -> let    left  = qs (List.filter rs ~f:(fun x -> x <= p))
                in let right = qs (List.filter rs ~f:(fun x -> x > p))
                in let left' = List.rev left
                in List.rev_append left' (p :: right)

let rec qs_slow l =
   match l with
   | []      -> []
   | p :: rs -> let    left  = qs_slow (List.filter rs ~f:(fun x -> x <= p))
                in let right = qs_slow (List.filter rs ~f:(fun x -> x > p))
                in left @ [p] @ right

let rec make_array_rev n ~l:l =
   match n with
   | 0 -> l
   | k -> make_array_rev (k - 1) ~l:(k :: l)

let () =
  let dataset     = [100;1000;5000]
  in let data     = List.map dataset ~f: (make_array_rev ~l:[])
  in let commands = List.map data ~f:(fun input ->
      [ Bench.Test.create ~name:"sort tail rec"
        (fun () -> ignore (qs input));
        Bench.Test.create ~name:"sort non tail rec"
        (fun () -> ignore (qs_slow input));
        Bench.Test.create ~name:"standard sort"
        (fun () -> ignore (List.sort ~cmp:(fun l r -> l - r) input));
      ]
     )
  in let commands' = List.concat commands
  in Command.run (Bench.make_command commands')
