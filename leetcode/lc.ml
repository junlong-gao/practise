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
  printer list_of_int print_int

let print_ss list_of_s =
  printer list_of_s print_string

let%expect_test "test_print_ss" =
  print_ss ["a"; "bb"; "ccc"];
  [%expect {|
[a; bb; ccc]
|}]

let%expect_test "test_print_int" =
  print_ints [1; 2; 3];
  [%expect {|
[1; 2; 3]
|}]

module Bst : sig
  type 'a bst_t =
    | Leaf
    | Node of 'a bst_t * 'a * 'a bst_t

  val insert : tree:'a bst_t -> to_insert:'a -> 'a bst_t
  val in_order : tree: 'a bst_t -> visitor: ('a -> unit) -> unit
end = struct
  (* in module implementation, this has to be repeated *)
  type 'a bst_t =
    | Leaf
    | Node of 'a bst_t * 'a * 'a bst_t

  let rec insert ~tree:t ~to_insert:v =
    match t with
    | Leaf -> Node(Leaf, v, Leaf)
    | Node (left, t, right) ->
      if v < t then Node(insert ~tree:left ~to_insert:v, t, right)
      else Node(left, t, insert ~tree:right ~to_insert:v)

  let rec in_order ~tree:t ~visitor:f =
    match t with
    | Leaf -> ()
    | Node (left, t, right) ->
      ignore(f t);
      ignore(in_order ~tree:left ~visitor:f);
      ignore(in_order ~tree:right ~visitor:f);
      ()
end

let%expect_test "bst" =
  let open Bst in
  let root = Leaf
  in
  let root = insert ~tree:root ~to_insert:1
  in
  let root = insert ~tree:root ~to_insert:2
  in
  in_order ~tree:root ~visitor:(fun v -> Printf.printf "%d " v);
  [%expect {| 1 2|}]
