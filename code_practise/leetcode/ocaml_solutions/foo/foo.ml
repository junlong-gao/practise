open Core

module Fib = struct
let fib_helper n =
 (* note an array is created outside of the rec call scope *)
  let dp = Array.create (n + 1) (-1) in
  let rec fib n =
    (* dp table lookup *)
    match dp.(n) with
    (* is it kind of awkward that the actual induction logic
     * is in the indentation? *)
    | -1 -> let ret = match n with
                      | 0 -> 0
                      | 1 -> 1
                      | _ -> (fib (n - 1)) + (fib (n-2))
            (* dp table fillin *)
            in dp.(n) <- ret; ret
    | _  -> dp.(n)
  in fib n

let%expect_test "fib dp" =
(* begin test cases *)
List.iter
  ~f:(fun x -> print_int (fib_helper x); print_endline "")
  [0;1;2;3;4;5;];
[%expect {|
  0
  1
  1
  2
  3
  5
|}]
end

module Fib_no_dp = struct
let rec fib n =
  match n with
  | 0 -> 0
  | 1 -> 1
  | _ -> (fib (n - 1)) + (fib (n-2))

let%expect_test "fib no dp" =
(* begin test cases *)
List.iter
  ~f:(fun x -> print_int (fib x); print_endline "")
  [0;1;2;3;4;5;];
[%expect {|
  0
  1
  1
  2
  3
  5
|}]
end
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

  let%expect_test "bst" =
    let root = Leaf
    in
    let root = insert ~tree:root ~to_insert:1
    in
    let root = insert ~tree:root ~to_insert:2
    in
    in_order ~tree:root ~visitor:(fun v -> Printf.printf "%d " v);
    [%expect {|1 2|}]
end

module PolyVariant = struct
  type basic_color =
    [`Black | `Blue | `White]

  type color =
    [ `Basic of basic_color * [`Bold | `Regular]
    | `Gray  of int
    | `RGB   of int * int * int]

  let basic_color_to_int = function
    | `Black -> 0
    | `Blue  -> 1
    | `White -> 2

  let color_to_int = function
    | `Basic (c, w) ->
      let w_name = match w with
        | `Bold -> 100
        | `Regular -> 200
      in
      w_name + (basic_color_to_int c)
    | `Gray (v) -> v
    | `RGB (x, y, z) -> 16 + z + y * 6 + x * 36

  type extended_color =
    [ color
    | `RGBA of int * int * int * int]

  let extended_color_to_int = function
    | `RGBA (r, g, b, a) -> 256 * a + b * 6 + g * 36 + r * 216
    (* narrowring *)
    | (`Basic _ | `RGB _ | `Gray _) as color -> color_to_int color

  let%expect_test "colors" =
    ignore(
      ignore(print_string "\nbasic color to int \n");
      List.iter ~f:(fun c ->
          Printf.printf "%d " (basic_color_to_int c)
        ) [`Black; `Blue; `Blue];

      ignore(print_string "\ncolor to int \n");
      List.iter ~f:(fun c ->
          Printf.printf "%d " (color_to_int c)
        ) [`Basic(`Black, `Bold);
           `Basic(`Blue, `Regular);];
      ignore(print_string "\nextended color to int \n");
      List.iter ~f:(fun c ->
          Printf.printf "%d " (extended_color_to_int c)
        ) [`RGBA(1, 2, 3, 4);
           `Basic(`Blue, `Regular);];
    );
    [%expect {|
      basic color to int
      0 1 1
      color to int
      100 201
      extended color to int
      1330 201
   |}]
end

module Preorder = struct

   let rec search (preorder_list:int array) (lower:int) (upper:int) s e =
      if   e == s then 0
      else let r = preorder_list.(s) in
           let valid_bst = (r < upper) && (r >= lower)
           in
           if   not valid_bst then 0
           else let mid = (search preorder_list lower r (s + 1) e ) in
                    1 + (mid + (search preorder_list (r + 1) upper (s + 1 + mid) e))

    let is_valid_preorder preorder_list =
       let n = (Array.length preorder_list)
       in
       n = (search preorder_list Int.min_value Int.max_value 0 n)

    let%expect_test "preorder bst" =
       ignore(
          List.iter ~f:(fun c ->
             Printf.printf "%B\n"
             (is_valid_preorder c)
          )
          [
             [||];
             [|1|];
             [|1; 2|];
             [|2; 1; 3|];
             [|3; 1; 2|];
             [|3; 4; 5; 1|];
             [|1; 4; 5; 6|];
             [|1; 0; 4; -1|];
          ];
       );
    [%expect
    {|
      true
      true
      true
      true
      true
      false
      true
      false

     |}]
end
