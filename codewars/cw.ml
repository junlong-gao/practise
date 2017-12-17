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

module Maximum_length_difference = struct
  let mxdiflg (a1: string array) (a2: string array): int option =
    if (Array.length a1 = 0) or (Array.length a2 = 0) then Some(-1)
    else
      let mapper = Array.map ~f:(fun (s: string) -> String.length s)
      in
      let a1_l = mapper a1
      in
      let a2_l = mapper a2
      in
      ignore(Array.sort ~cmp:Int.compare a1_l);
      ignore(Array.sort
               ~cmp: (fun l r ->
                   if l < r then -1 else if l > r then 1 else 0)
               a2_l);
      let abs x =
        if x > 0 then x
        else 0 - x
      in
      let t1 = abs (Array.get a1_l 0 - Array.last a2_l)
      in
      let t2 = abs (Array.get a2_l 0 - Array.last a1_l)
      in
      if t1 > t2 then Some(t1)
      else Some(t2)
  let%expect_test "max length diff" =
    List.iter ~f:(fun (a1, a2) ->
        Printf.printf "%d\n" (match (mxdiflg a1 a2) with |Some x->x |None -> -1)
      )[
      ([||], [||]);
      ([||], [|"b"; "bbbb"|]);
      ([|"aa"; "aaa"; "a"|], [|"b"; "bbbb"|]);
      ([|"aa"; "a"|], [|"bb"; "bb"|]);
    ];
    [%expect{|
      -1
      -1
      3
      1
      |}]
end

