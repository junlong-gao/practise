open Core
open Lexer
open Lexing

let print_position outx lexbuf =
  let pos = lexbuf.lex_curr_p in
  fprintf outx "%s:%d:%d" pos.pos_fname
    pos.pos_lnum (pos.pos_cnum - pos.pos_bol + 1)

let parse_with_error lexbuf =
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

let compile_p4diff_from_string input =
  let lexbuf = Lexing.from_string input
  in (parse_with_error lexbuf)

let%expect_test "p4 diff parse" =
  let repo = "/repo" in
  let branch = "/branch" in
  let source_tree = "//depot" ^ repo ^ branch in
  let input =
    String.concat ~sep:"\n" [

      "--- " ^ source_tree ^ "/old.cpp\\t" ^ source_tree ^ "/old.cpp#4";
      "+++ " ^ source_tree ^ "/new.cpp\\t3";
      "@@ -487,6 +487,35 @@ some function";
      "+ newline";
      "  \\tunchanged";
      "- deleted";
      "";
      "";
    ]
  in
  ignore(Util.dump (compile_p4diff_from_string input))
  ;
  [%expect {|
     filename:
     old:/repo/old.cpp
     new:/repo/new.cpp
     		chunk header:@@ -487,6 +487,35 @@ some function
     			added     line: newline
     			unchanged line: 	unchanged
     			deleted   line: deleted
   |}]
