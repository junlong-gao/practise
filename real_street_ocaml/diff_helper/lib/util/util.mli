(* builds a line stream from channel *)
val line_stream_of_channel : in_channel -> string Stream.t

(*
 * builds a long string from stream
 * escapes all the special characters within the line:
 *   foo
 *   baz"bar\n"
 *   t  ab
 *)
val string_of_line_stream : string Stream.t -> string

type diff_line_type =
  | Added_line    of string
  | Deleted_line  of string
  | Unchanged_line of string

(*            old file  new_file  hunk_header   line     *)
type value = (string * string * (string * diff_line_type list) list) list

(* dump the diff ast *)
val dump : value -> unit

(* String sanity *)

val list_at : 'a list -> int -> 'a

val drop_last : string -> string

val drop_first : string -> string

(*
 * Remove the both start and end char of string
 *)
val trim : string -> string

(*
 * Unescape the char in the string: \\t -> \t
 *)
val fix : string -> string

val print_position : out_channel -> Lexing.lexbuf -> unit
