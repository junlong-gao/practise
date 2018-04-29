open Core

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
