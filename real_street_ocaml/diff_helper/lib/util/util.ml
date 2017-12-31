include Diff_ast
open Lexing
open Core

let print_position outx lexbuf =
  let pos = lexbuf.lex_curr_p in
  fprintf outx "%s:line:%d:col %d to col %d" pos.pos_fname
    pos.pos_lnum pos.pos_bol pos.pos_cnum

let list_at l n = match Core.List.nth l n with
  |Some s -> s
  |None -> failwith (Printf.sprintf "invalid format %d" n)

let drop_last s = Core.String.sub ~pos:0 ~len:((Core.String.length s) - 1) s
let drop_first s = Core.String.sub ~pos:1 ~len:((Core.String.length s) - 1) s
let trim s = (drop_first (drop_last s))
let fix s = Scanf.unescaped s

let line_stream_of_channel channel =
  Stream.from
    (fun _ ->
       try Some (input_line channel) with End_of_file -> None);;

let string_of_line_stream ss =
  let open Core in
  let acc = ref [] in
  ignore(
    Stream.iter (fun s ->
        acc := ((String.escaped s) ^ "\n") :: !acc) ss
  );
  let l = List.rev !acc in
  String.concat l


let get_top =
  let open Core in
  let open Core_extended.Std in
  match Shell.run_one "git" [
      "rev-parse";
      "--show-toplevel"
    ] with
  | Some v -> v
  | None   -> failwith "Failed to get git top level, are you running in git repo?"


let get_toplevel = get_top

let print cmd_args env=
  Core.Printf.printf "+Running:\n+%s\n" (
    (Core.String.concat ~sep:" " env) ^ " " ^
    (Core.String.concat ~sep:" " cmd_args)
  )

let run cmd args verbose =
  let open Core in
  let open Core_extended.Std in
  if verbose then (print ([cmd]@args) []);
  let env = ((Array.to_list (Unix.environment ()))) in
  let env = List.map env ~f:(fun single_env ->
      let splitted = Str.split (Str.regexp "=") single_env in
      let k = List.nth_exn splitted 0 in
      let v = List.nth_exn splitted 1 in
      ignore (if verbose then print_string (k^":"^v^"\n"));
      (k, v)
    ) in
  let out = (Shell.run_full cmd args ~env:(`Replace env) ~verbose:verbose) in
  ignore(if verbose then print_string out );
  out

let git git_args verbose =
  let open Core in
  let cmd = "git" in
  let top_level = get_top in
  let args = (List.append [
      "--no-pager";
      "-C";
      top_level;
    ] git_args) in
  run cmd args verbose

let dump l =
  let open Core in
  List.iter l ~f:(fun (s, e, l) ->
      printf "filename: \nold:%s \nnew:%s\n" s e;
      List.iter l ~f:(fun (hunk, l) ->
          printf "\t\tchunk header:%s\n" hunk;
          List.iter l ~f:(fun line ->
              match line with
              | Unchanged_line  s -> printf "\t\t\tunchanged line:%s\n" s
              | Added_line      s -> printf "\t\t\tadded     line:%s\n" s
              | Deleted_line    s -> printf "\t\t\tdeleted   line:%s\n" s
            )
        )
    );

