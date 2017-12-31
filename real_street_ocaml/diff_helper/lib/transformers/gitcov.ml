open Core
open Core_extended

let check_coverage info_file_in git_diff_in toplevel v prefix=
  let open Parsers in
  let open Git_diff in
  let new_lines_in_diff = gen_new_lines (process git_diff_in) in
  let parsed_coverage = compile_from_ch_into_list info_file_in in
  List.iter parsed_coverage ~f:(fun (filename,_,_,lines) ->
      let filename =
        String.sub ~pos:(String.length toplevel)
          ~len:((String.length filename) - (String.length toplevel)) filename
      in
      if not (String.is_prefix filename prefix) then
        if v then Printf.printf "Skipping file %s as it does not start with %s\n" filename prefix
        else ()
      else (
        ignore(if v then Printf.printf "Checking file %s\n" filename else ());
        if not (check_file_in_diff new_lines_in_diff filename) then
          if v then Printf.printf "Skipping file %s as it is not in diff\n" filename
          else ()
        else (
          List.iter lines ~f:(fun (line,hitcount)->
              if hitcount > 0 then ()
              else if check_is_new_line new_lines_in_diff filename line
              then (
                Printf.printf "@@@ Missing coverage in File:%s of line:%d\n" filename line  ;
                Printf.printf "\nXXX -->\t%s\n\n" (get_line new_lines_in_diff filename line)
              )
              else ()
            );
        )
      )
    )

let check_coverage_from_file
    info_file_name toplevel verbose filter =
  let ch = In_channel.create info_file_name in
  check_coverage (Util.line_stream_of_channel ch)
    (Util.line_stream_of_channel In_channel.stdin)
    toplevel
    verbose
    filter

let%expect_test "check cov" =
  check_coverage
    (Stream.of_list [
        "TN:";
        "SF:/home/foo/repo/alpha/bar.cpp";
        "FN:40,FuncBaz";
        "FNDA:32,FuncBaz";
        "FNF:17";
        "FNH:16";
        "DA:3653,145";
        "DA:3654,0";
        "DA:3655,145";
        "DA:4653,0";
        "DA:4654,1";
        "DA:5654,1";
        "LF:94";
        "LH:71";
        "end_of_record";
        "TN:";
        "SF:/home/foo/repo/alpha/bar.cpp";
        "FN:40,FuncBaz";
        "FNDA:32,FuncBaz";
        "FNF:17";
        "FNH:16";
        "DA:3653,145";
        "DA:3654,0";
        "DA:3655,145";
        "DA:4653,0";
        "DA:4654,1";
        "DA:5654,1";
        "LF:94";
        "LH:71";
        "end_of_record";
        "TN:";
        "SF:/home/foo/repo/beta/bar.cpp";
        "FN:40,FuncBaz";
        "FNDA:32,FuncBaz";
        "FNF:17";
        "FNH:16";
        "DA:3653,145";
        "DA:3654,0";
        "DA:3655,145";
        "DA:4653,0";
        "DA:4654,1";
        "DA:5654,1";
        "LF:94";
        "LH:71";
        "end_of_record";
      ])
    (Stream.of_list [
        "diff --git a/alpha/bar.cpp b/alpha/bar.cpp";
        "index 9daeafb..0000000 100644";
        "--- a/alpha/bar.cpp";
        "+++ b/alpha/bar.cpp";
        "@@ -3653 +3653,3 @@ some cool function";
        "+      for(";
        "+      for (){";
        "+      if(";
        "@@ -4653 +4653,2 @@ another cool function";
        "-      for(";
        "+      for (){";
        "+      if(";
        "@@ -5653,2 +5653,3 @@ final cool function";
        "       for(";
        "+      for (){";
        "       if(";
        "diff --git a/beta/bar.cpp b/beta/bar.cpp";
        "index 9daeafb..0000000 100644";
        "--- a/beta/bar.cpp";
        "+++ b/beta/bar.cpp";
        "@@ -3653 +3653,3 @@ some cool function";
        "+      for(";
        "+      for (){";
        "+      if(";
        "@@ -4653 +4653,2 @@ another cool function";
        "-      for(";
        "+      for (){";
        "+      if(";
        "@@ -5653,2 +5653,3 @@ final cool function";
        "       for(";
        "+      for (){";
        "       if(";
      ])
    "/home/foo/repo"
    true
    "/alpha"
  ;
  [%expect {|
    Checking file /alpha/bar.cpp
    @@@ Missing coverage in File:/alpha/bar.cpp of line:3654

    XXX -->	      for (){

    @@@ Missing coverage in File:/alpha/bar.cpp of line:4653

    XXX -->	      for (){

    Checking file /alpha/bar.cpp
    @@@ Missing coverage in File:/alpha/bar.cpp of line:3654

    XXX -->	      for (){

    @@@ Missing coverage in File:/alpha/bar.cpp of line:4653

    XXX -->	      for (){

    Skipping file /beta/bar.cpp as it does not start with /alpha
   |}]

