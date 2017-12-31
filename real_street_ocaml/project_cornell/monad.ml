open Core

module Maybe = struct
  type 'a t = None | Some of 'a
  let return (x : 'a) = Some x
  let bind (m : 'a t) (f : 'a -> 'b t) =
    match m with
    | Some x -> f x
    | None -> None
  let (>>=) = bind
  let fmap (m : 'a) (f : 'a -> 'b) =
    Some (f m)
  let (>>|) = fmap

  let join (x: 'a t t) =
    match x with
    | Some x -> x
    | None -> None

  let bind' (m : 'a t) (f : 'b -> 'c) =
    join (fmap m f)
end

let%expect_test "1" =
(*
 * Computes the sum of two optional values.
 * If both x and y are of the form Some p, [add x y] should be Some(px + py)
 * If either x or y are None, [add x y] should be None
 *)

  let open Maybe in
  let add (x: int t) (y : int t) =
    x >>= fun x' ->
    y >>= fun y' ->
    return (x' + y')
  in
  let p v =
    match v with
    | Some s -> Printf.printf "Some %d\n" s
    | None -> Printf.printf "None\n"
  in
  p (add (Some 1) (Some 2));
  p (add (None ) (Some 2));
  p (add (None ) (None ));
  ;
  [%expect {|
   Some 3
   None
   None
   |}]

(*
Exercise: cleanup [✭✭]

The following code uses some functions that produce optional values,
but whoever wrote it clearly missed last week's lecture on Monads.
Rewrite it more elegantly with bind and return.
*)

let%expect_test "2" =
  let l () =
    let open Maybe in
    let foo () = Some 1 in
    let bar x = Some "bar" in
    let zardoz () = Some "zardoz" in
    let print_option s = match s with
      | Some s -> print_string (s ^ "\n")
      | None -> print_string  "None\n"
    in
    match ((foo ()) >>= bar, (zardoz ())) with
    | Some x, Some y -> print_option (Some (x^y))
    | _ -> print_string "None"
  in l ()
  ;
  [%expect {| barzardoz |}]

(*
 * Lists and Nondeterminism
 *)
module ListMonad : sig
  type 'a t = 'a list

  val return : 'a -> 'a t

  val bind   : 'a t -> ('a -> 'b t) -> 'b t

  val (>>=)  : 'a t -> ('a -> 'b t) -> 'b t

  val fmap   : 'a t -> ('a -> 'b) -> 'b t

  val (>>|)  : 'a t -> ('a -> 'b) -> 'b t

  val join   : 'a t t -> 'a t

  val bind'  : 'a t -> ('a -> 'b t) -> 'b t

end = struct
  type 'a t = 'a list
  (* 'a -> 'a list *)
  let return x = [x]
  (* 'a t -> ('a -> 'b t) -> 'b t *)
  let bind m l =
    List.map m ~f:(fun x ->
        l x
      ) |> List.concat

  let (>>=) = bind

  (* 'a t -> ('a -> 'b) -> 'b t *)
  let fmap m l =
    List.map m ~f:(fun x ->
        l x
      )

  let (>>|) = fmap

  (* 'a t t -> 'a t *)
  let join m =
    List.concat m

  (* 'a t -> ('a -> 'b t) -> 'b t *)
  let bind' m l =
    join (fmap m l)

end

let%expect_test "list monad" =
  let open ListMonad in
  let roll () = [1;2;3;4] in
  let outcome1 = roll() in
  let outcome2 = roll() in
  let result = outcome1 >>= fun x ->
    outcome2 >>= fun y ->
    return (x + y)
  in
  List.iter result ~f:(fun s ->
      Printf.printf "%d;" s
    )
  ;
  [%expect {| 2;3;4;5;3;4;5;6;4;5;6;7;5;6;7;8; |}]

module type State = sig
  type t
  val empty : t
end

(*
Exercise: state monad [✭✭✭]

Not all functional languages have imperative features like OCaml does.
In pure languages like Haskell, computations that affect a state are
modeled using the State monad.

Complete the following definition for the State monad. Notice how it is a
functor: how state is represented changes based on the use case,
so we allow it to take the module representing State as an argument.
*)
module StateMonad (S : State) = struct
  type 'a t = S.t -> ('a * S.t)

  let return a = fun (s : S.t) -> (a, s)
  let bind (m : 'a t) (f : 'a -> 'b t) =
    (*Your implementation here*)
    f (fst (m S.empty))
  let (>>=) = bind

  let join (m : 'a t t) =
    (*Your implementation here*)
    m S.empty

  let fmap (m : 'a t) (f : 'a -> 'b) =
    (*Your implementation here*)
    fun (s : S.t) -> (f (fst (m S.empty)), s)

  let get_state m = snd (m S.empty)
end


