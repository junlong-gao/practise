open Core

let bound = 3

let rec find_kth l r k =
  if (List.length l) > (List.length r) then find_kth r l k
  else
  if (List.length l) = 0 then List.nth_exn r (k - 1)
  else
  if k < bound then
     let union = (List.take l k) @ (List.take r k)
     in let sorted = List.sort ~cmp:(fun l r -> l - r) union
     in List.nth_exn sorted (k - 1)
  else
     let first_left = min ((List.length l + 1) / 2) (k - 1)
     in let first_right = min (List.length r) (k - first_left)
     in let pivit_left = List.nth_exn l (first_left - 1)
     in let pivit_right = List.nth_exn r (first_right - 1)
     in if pivit_left < pivit_right then
           find_kth (List.drop l first_left) r (k - first_left)
        else
           find_kth l (List.drop r first_right) (k - first_right)

let%expect_test "simple kth" =
   let input_left = [1;2;3;4]
   in let input_right = [5;6;7;8]
   in let cases = [1;2;3;4;5;6;7;8]
   in List.iter cases ~f:(fun c ->
   find_kth input_left input_right c |> Printf.printf "ans:%d\n")
   ;
  [%expect {|
    ans:1
    ans:2
    ans:3
    ans:4
    ans:5
    ans:6
    ans:7
    ans:8 |}]

let%expect_test "overlapping ranges" =
   let input_left = [5;8;10;12]
   in let input_right = [1;7;11;20]
   in let cases = [1;2;3;4;5;6;7;8]
   in List.iter cases ~f:(fun c ->
   find_kth input_left input_right c |> Printf.printf "ans:%d\n")
   ;
  [%expect {|
    ans:1
    ans:5
    ans:7
    ans:8
    ans:10
    ans:11
    ans:12
    ans:20 |}]

let%expect_test "overlapping ranges" =
   let input_left = [0]
   in let input_right = [0; 1]
   in let cases = [1;2;3]
   in List.iter cases ~f:(fun c ->
   find_kth input_left input_right c |> Printf.printf "ans:%d\n");
  [%expect {|
    ans:0
    ans:0
    ans:1 |}]


let%expect_test "use quickcheck" =
   let test =
    QCheck.Test.make ~count:100 ~name:"use kth to reconstruct should equal to the original sorted"
     QCheck.(list small_nat)
     (fun total ->
       let sorted = List.sort ~compare:(fun l r -> l - r) total
       in let (l , r) = List.split_n sorted ((List.length sorted) / 2)
       in let sorted' = List.init (List.length sorted)
                         (fun idx -> find_kth l r (idx + 1))
       in (*Printf.printf "left:\n";
          ignore(Printer.print_ints l);
          Printf.printf "right:\n";
          ignore(Printer.print_ints r);
          Printf.printf "result:\n";
          ignore(Printer.print_ints sorted');
          *)
          sorted = sorted')
   in let () = QCheck.Test.check_exn test
   in print_endline "...Passed";
  [%expect {|
    ...Passed |}]
