open Core

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

let%expect_test "quicksort test" =
  qs [5;4;3;2;1] |>
    List.fold_left ~f:(fun acc x -> acc ^ " " ^ (string_of_int x)) ~init:""
    |> print_endline;
  [%expect {| 1 2 3 4 5 |}]

