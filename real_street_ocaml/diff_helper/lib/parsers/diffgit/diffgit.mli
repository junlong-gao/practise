module Git_diff : sig
  type new_lines = (string, (int, string) Core.Hashtbl.t) Core.Hashtbl.t

  type state_type = Added|Deleted|Unchanged

  type line_type = {
    line: string;
    state: state_type;
    line_num: int;
  }

  type diff_info = {
    old_filename : string;
    new_filename : string;
    chunk:  line_type list
  }

  val process : string Stream.t -> diff_info list

  val gen_new_lines : diff_info list -> new_lines

  val check_is_new_line : new_lines -> string -> int -> bool

  val get_line : new_lines -> string -> int -> string

  val check_file_in_diff : new_lines -> string -> bool
end
