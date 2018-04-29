open Core

let printer list_of_a print_fun=
  ignore(print_string "[");
  let rec intern_p l =
    match l with
    | [] -> ()
    | [hd] -> print_fun hd
    | hd::tl -> ignore(print_fun hd); print_string "; "; intern_p tl
  in
  intern_p list_of_a; ignore(print_string "]\n")

let print_ints list_of_int =
  printer list_of_int (Printf.printf "%d")

let print_ss list_of_s =
  printer list_of_s print_string

let%expect_test "test_print_ss" =
  print_ss ["a"; "bb"; "cccc"];
  [%expect {|
[a; bb; cccc]
|}]

let%expect_test "test_print_int" =
  print_ints [1; 2; 3];
  [%expect {|
[1; 2; 3]
|}]
