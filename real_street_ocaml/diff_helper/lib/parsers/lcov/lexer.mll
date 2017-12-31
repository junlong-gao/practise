{
open Lexing
open Parser

exception SyntaxError of string
let next_line lexbuf =
  let pos = lexbuf.lex_curr_p in
  lexbuf.lex_curr_p <-
    { pos with pos_bol = lexbuf.lex_curr_pos;
               pos_lnum = pos.pos_lnum + 1
    }
}

let digit = ['0'-'9']
let int = digit digit*
let no_new_line = [ ^'\n' ]*
let no_white = [ ^'\n' ' ' ]*
let space = ' '
let newline = '\n'
let comma = ","


(* header *)
let tn = "TN:"
let filename = "SF:"[ ^'\n' ]+

(* skip function section *)
let fn = "FN:" no_new_line 
let fnda = "FNDA:" no_new_line
let fnf = "FNF:" int 
let fnh = "FNH:" int

(* skip branch section *)
let brda = "BRDA:" int "," int "," int "," int
let brf  = "BRF:" int
let brh  = "BRH:" int

let checksum = "," int
let da = "DA:"
let lh = "LH:"
let lf = "LF:"

let end_of_section = "end_of_record\n"

rule read =
  parse
  | newline          { next_line lexbuf; read lexbuf }
  | tn               { TN         }
  | filename         { FILENAME (
                          let open Core in
                          let s = Lexing.lexeme lexbuf in
                          let escaped = Scanf.unescaped s in
                           String.sub ~pos:3 ~len:(String.length escaped - 3) escaped
                     )}
  | fn               { FN }
  | fnda             { FNDA }
  | fnf              { FNF }
  | fnh              { FNH }
  | lf               { LF }
  | lh               { LH }
  | da               { DA }
  | int              { INT (int_of_string (Lexing.lexeme lexbuf))}
  | comma            { COMMA }
  | end_of_section   { END_OF_SECTION }
  | _                { raise (SyntaxError ("Unexpected char: " ^ Lexing.lexeme lexbuf)) }
  | eof              { EOF }
