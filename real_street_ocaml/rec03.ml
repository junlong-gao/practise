open Core

let l1 = [1;2;3;4;5]

let l2 = 1::2::3::4::5::[]

let l3 = [1]@[2;3;4]@[5]

let rec prod l = match l with
               | [] -> 1
               | x :: rs ->  x * (prod rs)

let rec concat ls = match ls with
                  | [] -> ""
                  | s :: rs -> s ^ (concat rs)

let patterns l =
  let check x y = (x = y) && (x = "bigred") in
  match l with
  | x::y::[] | x::y::_::_::[] -> check x y
  | _ -> false

let special l =
  match List.nth l 5 with
  | Some v -> v
  | None -> 0

let desort l =
  List.sort ~compare:(fun left right -> right - left) l

let%expect_test "revert sort" =
  let out = desort [1;2;3;4;5]
  in Printer.print_ints out;
  [%expect {| [5; 4; 3; 2; 1] |}]

let last l =
  List.hd (List.rev l)

let anyzero l =
  List.length (List.filter l ~f:(fun x -> x = 0)) > 0
