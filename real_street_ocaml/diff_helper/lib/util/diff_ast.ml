open Core

type diff_line_type =
  | Added_line    of string
  | Deleted_line  of string
  | Unchanged_line of string

(*            old file  new_file  hunk_header   line     *)
type value = (string * string * (string * diff_line_type list) list) list


