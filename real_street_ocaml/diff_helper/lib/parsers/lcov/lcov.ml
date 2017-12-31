open Core
open Lexer
open Lexing

type value = (string * int * int * ((int * int) list) ) list

let parse_with_error lexbuf =
  let open Util in
  try Parser.prog Lexer.read lexbuf with
  | SyntaxError msg ->
    fprintf stderr "%a: syntax error: msg:%s\n" print_position lexbuf msg;
    exit (-1)
  | Parser.Error ->
    fprintf stderr "%a: parser error\n" print_position lexbuf;
    exit (-1)
  | Failure msg ->
    fprintf stderr "%a: exception:%s\n" print_position lexbuf msg;
    exit (-1)

let compile_from_ch_into_list ch_in =
  let lexbuf = Lexing.from_string (Util.string_of_line_stream ch_in) in
  parse_with_error lexbuf

(* tests *)
