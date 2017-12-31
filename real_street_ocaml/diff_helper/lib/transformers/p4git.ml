open Core
open Core_extended
open Parsers

type file_type = |Added|Deleted|Normal

let check_file chunk type_to_check =
  if not (phys_equal (List.length chunk)  1) then false
  else let header, first_chunk = List.hd_exn chunk in
    let total_change = List.length first_chunk in
    let filtered = List.filter first_chunk ~f:(fun line_type ->
        match line_type with
        |Util.Added_line   s    -> phys_equal type_to_check Added
        |Util.Deleted_line s    -> phys_equal type_to_check Deleted
        |Util.Unchanged_line s  -> false
      )
    in
    List.length filtered = total_change

let patch_file file_chunk old_filename new_filename file_diff_type =
  let git_header = ("diff --git "^"a"^old_filename^" "^"b"^new_filename^"\n") in
  let new_header =
    List.append [git_header] (match file_diff_type with
        | Added ->
          [
            "new file mode 100664\n";
            "index 0000000..0000000\n";
            "--- /dev/null\n";
            "+++ b" ^ new_filename^"\n";
          ]
        | Deleted ->
          [
            "deleted file mode 100644\n";
            "index 0000000..0000000\n";
            "--- a" ^ old_filename^"\n";
            "+++ /dev/null\n";
          ]
        | Normal ->
          [
            "index 0000000..0000000 100644\n";
            "--- a" ^ old_filename ^"\n";
            "+++ b" ^ new_filename ^"\n";
          ]
      )
  in
  let diff_data = List.fold_left file_chunk ~init:[] ~f:(fun acc (hunk_header, lines) ->
      let rest = List.map lines ~f:(fun s ->
          let modified = match s with
            | Util.Unchanged_line s -> " " ^ s
            | Util.Added_line s     -> "+" ^ s
            | Util.Deleted_line s   -> "-" ^ s
          in (modified^"\n"))
      in
      List.append acc (List.append [hunk_header ^ "\n"] rest)
    )
  in
  List.append new_header diff_data

let fix_and_print input =
  Diffp4.compile_p4diff_from_string input
  |> List.map ~f:(fun (oldf, newf, fchunk) ->
      let fchunk_type =
        if check_file fchunk Added then  Added
        else if check_file fchunk Deleted then  Deleted
        else Normal
      in
      patch_file fchunk oldf newf fchunk_type
    )
  |> List.concat
  |> List.iter ~f:print_string

let format_p4_to_git () =
  Util.string_of_line_stream (Util.line_stream_of_channel In_channel.stdin)
  |> fix_and_print

let%expect_test "p4 diff to git" =
  ((String.concat ~sep:"\n" [
       "--- //depot/repo/branch/old.cpp\\t//depot/repo/branch/old.cpp#4";
       "+++ //depot/repo/branch/new.cpp\\t3";
       "@@ -487,6 +487,35 @@ some function";
       "+ newline";
       "  unchanged";
       "- deleted";
       "";
       "";
     ]) |> fix_and_print)
  ;
  [%expect {|
    diff --git a/repo/old.cpp b/repo/new.cpp
    index 0000000..0000000 100644
    --- a/repo/old.cpp
    +++ b/repo/new.cpp
    @@ -487,6 +487,35 @@ some function
    + newline
      unchanged
    - deleted
  |}]

let%expect_test "p4 diff to git regression" =
  ((String.concat ~sep:"\n" [
       "--- //depot/repo/branch/a.h\\t//depot/repo/branch/a.h#5";
       "+++ //depot/repo/branch/a.h\\t2017-12-21 00:00:00";
       "@@ -109,13 +109,14 @@ SuperCoolFuncion:";
       "    unchanged";
       "+   added;";
       " ";
       "-   deleted;";
       "+   added;";
       " ";
       "    unchanged;";
       "    unchanged;";
       "";
       "";
     ]) |> fix_and_print)
  ;
  [%expect {|
    diff --git a/repo/a.h b/repo/a.h
    index 0000000..0000000 100644
    --- a/repo/a.h
    +++ b/repo/a.h
    @@ -109,13 +109,14 @@ SuperCoolFuncion:
        unchanged
    +   added;

    -   deleted;
    +   added;

        unchanged;
        unchanged;
  |}]
