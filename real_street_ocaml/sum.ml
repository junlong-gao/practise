let rec sum = function
  | [] -> 0
  | x::xs -> x + (sum xs)

let%expect_test "sum test" =
  print_int (sum [1;2;3])
  ;
  [%expect {| 6 |}]
