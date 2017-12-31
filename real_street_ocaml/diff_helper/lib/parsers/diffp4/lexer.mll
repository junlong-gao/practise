{
open Lexing
open Parser
open Core
open Util

exception SyntaxError of string

let source_tree = "//depot"
let fix_fname l =
 let intermediate = (list_at (Str.split (Str.regexp (" " ^ source_tree)) l) 1)
 in let raw = (list_at (Str.split (Str.regexp "[' ' '\t']+") intermediate) 0)
 in "/" ^ (String.concat ~sep:"/" (List.filteri (Str.split (Str.regexp ("/")) raw) ~f:(fun i _ -> not (phys_equal i 1))))
}

let source_tree = "//depot"
let digit = ['0'-'9']
let int = digit digit*
let version = '#' int

let oldfile = "--- " source_tree [ ^'\n' ]* "\\t"* source_tree [ ^'\n' ]* version '\n'
let newfile = "+++ " source_tree [ ^'\n' ]* '\n'

let hunk_header = "@@ -" int ',' int " +" int ',' int " @@" [ ^'\n' ]* '\n'

let unchanged = ' ' [ ^'\n' ]* '\n'
let added     = '+' [ ^'\n' ]* '\n'
let deleted   = '-' [ ^'\n' ]* '\n'
let blank = '\n' eof

rule read =
  parse
  | oldfile      { OLD_FILE       (fix_fname (fix (Lexing.lexeme lexbuf))) }
  | newfile      { NEW_FILE       (fix_fname (fix (Lexing.lexeme lexbuf))) }
  | hunk_header  { HUNK_HEADER    (drop_last (fix (Lexing.lexeme lexbuf))) }
  | unchanged    { UNCHANGED_LINE (trim (fix (Lexing.lexeme lexbuf))) }
  | added        { ADDED_LINE     (trim (fix (Lexing.lexeme lexbuf))) }
  | deleted      { DELETED_LINE   (trim (fix (Lexing.lexeme lexbuf))) }
  | _ { raise (SyntaxError ("Unexpected char: " ^ Lexing.lexeme lexbuf)) }
  | blank           {BLANK}
  | eof             {EOF}


