{
open Lexing
open Parser
open Core
open Util

exception SyntaxError of string
}

let digit = ['0'-'9']
let int = digit digit*
let mode = digit digit digit digit digit digit
let index_char = ['0'-'9' 'a'-'z']
let index =  index_char*
let no_new_line = [ ^'\n' ]*
let no_white = [ ^'\n' ' ' ]*
let space = ' '
let newline = '\n'

(* header *)
let git_header = "diff --git "
let a = "a/" no_white ' '
let b = "b/" no_white '\n'

(* rename *)
let rename = "similarity index 100%\nrename from " no_white "\nrename to " no_white "\n"

(* new *)
let newfile_source = "--- /dev/null\n"
let newfile = "new file mode " mode "\n" "index " index ".." index '\n'

(* deleted *)
let deletefile = "deleted file mode " mode "\n" "index " index ".." index '\n'
let deletefile_dest = "+++ /dev/null\n"

(* index *)
let index = "index " index ".." index " " mode "\n"

(* normal *)
let source = "--- a/" no_white '\n'
let dest = "+++ b/" no_white '\n'

(* diff hunk *)
let hunk_sig = int [',']* int*
let hunk_header = "@@ -" hunk_sig " +" hunk_sig " @@" ' '* no_new_line '\n'

(* diff line *)
let unchanged = ' ' no_new_line '\n'
let added     = '+' no_new_line '\n'
let deleted   = '-' no_new_line '\n'

(* eof *)

rule read =
  parse
  | git_header       { GIT_HEADER       (fix (Lexing.lexeme lexbuf)) }
  | a                { A                (fix (Lexing.lexeme lexbuf)) }
  | b                { B                (drop_last (fix (Lexing.lexeme lexbuf))) }
  | index            { INDEX }
  | rename           { RENAME_FILE       }
  | newfile          { ADDED_FILE    }
  | newfile_source   { ADDED_FILE_SRC }
  | deletefile       { DELETED_FILE    }
  | deletefile_dest  { DELETED_FILE_DEST  }
  | source           { SRC_FILE  }
  | dest             { DST_FILE }
  | hunk_header      { HUNK_HEADER    (fix (Lexing.lexeme lexbuf)) }
  | unchanged        { UNCHANGED_LINE (trim  (fix (Lexing.lexeme lexbuf))) }
  | added            { ADDED_LINE     (trim  (fix (Lexing.lexeme lexbuf))) }
  | deleted          { DELETED_LINE   (trim  (fix (Lexing.lexeme lexbuf))) }
  | _                { raise (SyntaxError ("Unexpected char: " ^ (Lexing.lexeme lexbuf))) }
  | eof              { EOF }


