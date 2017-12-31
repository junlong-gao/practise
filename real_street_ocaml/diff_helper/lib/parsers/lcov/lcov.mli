open Core

type value = (string * int * int * ((int * int) list) ) list

val compile_from_ch_into_list : string Stream.t -> value
