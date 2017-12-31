open Core

(*            filename total_line hit_line (line_num count)) *)
type value = (string * int * int * ((int * int) list) ) list
