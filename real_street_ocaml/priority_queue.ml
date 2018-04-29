module PrioQueue =
struct
  type priority = int
  type 'a queue = Empty
                | Node of priority * 'a * 'a queue * 'a queue
  let empty = Empty

(*
This will still result in a binary tree with minial height, because
we make sure every time |left| - |right| <= 1 (induction)
*)
  let rec insert queue prio elt =
    match queue with
    | Empty -> Node(prio, elt, Empty, Empty)
    | Node(p, e, left, right) ->
        if prio <= p
        then Node(prio, elt, insert right p e, left)
        else Node(p, e, insert right prio elt, left)

(*
remove the top of queue / extract max
this is inline of what binary heap does
*)
  exception Queue_is_empty
  let rec remove_top = function
    | Empty -> raise Queue_is_empty
    | Node(prio, elt, left, Empty) -> left
    | Node(prio, elt, Empty, right) -> right
    | Node(prio, elt, (Node(pl, el, _, _) as left),
                      (Node(pr, er, _, _) as right)) ->
          if pl < pr
          then Node(pl, el, remove_top left, right)
          else Node(pr, er, left, remove_top right)

  let extract = function
     | Empty -> raise Queue_is_empty
     | Node(prio, elt, _, _) as queue -> (prio, elt, remove_top queue)
end

let%expect_test "pp_module" =
  let open PrioQueue in
  let first = PrioQueue.insert PrioQueue.empty 1 "hello"
  in let (p, e, _) = PrioQueue.extract first
  in print_endline e;
  [%expect {| hello |}]
