open Core
open Lexer
open Lexing
open Util

let parse_with_error lexbuf =
  let open Util in
  try Parser.prog Lexer.read lexbuf with
  | SyntaxError msg ->
    fprintf stderr "%a: syntax error: msg:%s\n" print_position lexbuf msg;
    exit(-1)
  | Parser.Error ->
    fprintf stderr "%a: parser error\n" print_position lexbuf;
    exit (-1)
  | Failure msg ->
    fprintf stderr "%a: exception:%s\n" print_position lexbuf msg;
    exit (-1)

let parse input =
  let lexbuf = Lexing.from_string input
  in (parse_with_error lexbuf )


module Git_diff = struct
  type new_lines =
    (string, (int, string) Core.Hashtbl.t) Core.Hashtbl.t

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

  let process_internal input =
    let parsed = parse input in
    let drop_first s = String.sub ~pos:1
        ~len:((String.length s) - 1) s
    in
    List.map parsed ~f:(fun (old_f, new_f, file_hunks) ->
        {
          old_filename = drop_first old_f;
          new_filename = drop_first new_f;
          chunk = (
            List.map file_hunks ~f:(fun (hunk_header, hunk_lines) ->
                let new_chunk_start_line =
                  Scanf.sscanf hunk_header "@@ %s %d%s @@" (fun _ start _ -> start;)
                in
                let get_diff_info hunk_line ref_start_line_num =
                  let content, line_type = match hunk_line with
                    | Util.Added_line content -> (content, Added)
                    | Util.Deleted_line content -> (content, Deleted)
                    | Util.Unchanged_line content -> (content,  Unchanged)
                  in
                  {
                    line = content;
                    state = line_type;
                    line_num = ref_start_line_num;
                  }
                in
                let rec calculate_diffs diff_lines start_line =
                  match diff_lines with
                  | [] -> []
                  | [single_line] -> [get_diff_info single_line start_line;]
                  | hd::tl -> let hd_rst = (get_diff_info hd start_line) in
                    let next_start_line =
                      (start_line + ( match hd_rst.state with | Deleted -> 0 | _ ->  + 1))
                    in
                    hd_rst :: calculate_diffs tl next_start_line
                in
                calculate_diffs hunk_lines new_chunk_start_line
              ) |> List.concat
          )
        }
      )

  let gen_new_lines (processed: diff_info list) =
    let rst = String.Table.create() in
    List.iter processed ~f:(fun file ->
        let filename = file.new_filename in
        let lines = Int.Table.create() in
        List.iter file.chunk ~f:(fun line ->
            if line.state = Added then
              Hashtbl.set lines ~key:line.line_num ~data:line.line
          );
        Hashtbl.set rst ~key:filename ~data:lines
      );
    rst

  let check_is_new_line new_line_table (filename: string) (line_num: int) =
    match Hashtbl.find new_line_table filename with
    | None ->   false
    | Some file_table ->
    match Hashtbl.find file_table line_num with
    | None ->   false
    | Some _ -> true

  let check_file_in_diff new_line_table (filename: string) =
    match Hashtbl.find new_line_table filename with
    | None ->   false
    | Some _ -> true

  let get_line new_line_table filename line_num =
    match Hashtbl.find new_line_table filename with
    | None -> failwith "The file is not an added file"
    | Some file_table ->
    match Hashtbl.find file_table line_num with
    | None -> failwith "The line is not an added line"
    | Some s -> s

  let process ch_in =
    process_internal (Util.string_of_line_stream ch_in)

end


(* tests *)
let%expect_test "git diff parse modify" =
  let input = String.concat ~sep:"\n"
      [
        "diff --git a/foo b/foo";
        "index 9daeafb..2bdc76e 100644";
        "--- a/foo";
        "+++ b/foo";
        "@@ -1 +1,2 @@ foo()";
        " test";
        "+bar";
        "";
      ]
  in
  ignore(dump (parse input))
  ;
  [%expect {|
     filename:
     old:a/foo
     new:b/foo
     		chunk header:@@ -1 +1,2 @@ foo()

     			unchanged line:test
     			added     line:bar

   |}]

let%expect_test "git diff parse add" =
  let input = String.concat ~sep: "\n"
      [
        "diff --git a/foo b/foo";
        "new file mode 100644";
        "index 0000000..9daeafb";
        "--- /dev/null";
        "+++ b/foo";
        "@@ -0,0 +1 @@ bar(int a)";
        "+test";
        "";
      ]
  in
  ignore(dump (parse input))
  ;
  [%expect {|
     filename:
     old:a/foo
     new:b/foo
     		chunk header:@@ -0,0 +1 @@ bar(int a)

     			added     line:test
   |}]

let%expect_test "git diff parse deleted" =
  let input = String.concat ~sep:"\n"
      [
        "diff --git a/bar b/bar";
        "deleted file mode 100644";
        "index 9daeafb..0000000";
        "--- a/bar";
        "+++ /dev/null";
        "@@ -1 +0,0 @@";
        "-test";
        "";
      ]
  in
  ignore(dump (parse input))
  ;
  [%expect {|
     filename:
     old:a/bar
     new:b/bar
     		chunk header:@@ -1 +0,0 @@

     			deleted   line:test
   |}]

let%expect_test "git diff parse rename" =
  let input = String.concat ~sep:"\n"
      [
        "diff --git a/foo b/bar";
        "similarity index 100%";
        "rename from foo";
        "rename to bar";
        "";
      ]
  in
  ignore(dump (parse input))
  ;
  [%expect {|
   filename:
   old:a/foo
   new:b/bar
   |}]

let%expect_test "git diff parse long index with escape" =
  let input = String.concat ~sep:"\n"
      [
        "diff --git a/bar b/bar";
        "deleted file mode 100644";
        "index 9daeafb88..000000099";
        "--- a/bar";
        "+++ /dev/null";
        "@@ -1 +0,0 @@";
        "-\\ttest";
        "";
      ]
  in
  ignore(dump (parse input))
  ;
  [%expect {|
     filename:
     old:a/bar
     new:b/bar
     		chunk header:@@ -1 +0,0 @@

     			deleted   line:	test
   |}]

let%expect_test "diff_parse" =
  String.concat ~sep:"\n"
    [
      "diff --git a/test/foo.c b/test/foo.c";
      "index 9daeafb..0000000 100644";
      "--- a/test/foo.c";
      "+++ b/test/foo.c";
      "@@ -11,8 +21,8 @@ Foo::foo()";
      " #ifndef a";
      "-#define b";
      "+#define c";
      "@@ -11,8 +31,8 @@ Bar::bar()";
      " #ifndef d";
      "+#define e";
      "-#define f";
      "";
    ]
  |>
  Git_diff.process_internal
  |> List.iter ~f:(fun c->
      Printf.printf "old_filename:%s, new_filename:%s\n" c.old_filename c.new_filename;
      List.iter ~f:(fun r->
          Printf.printf "\tline:%s\n\tline_num:%d\n" r.line r.line_num;
          Printf.printf
            (match r.state with
             | Added -> "\tAdded\n"
             | Deleted -> "\tDeleted\n"
             | _ -> "\tUnchanged\n"
            );
          ()
        ) c.chunk
    );
  [%expect {|
    old_filename:/test/foo.c , new_filename:/test/foo.c
    	line:#ifndef a
    	line_num:21
    	Unchanged
    	line:#define b
    	line_num:22
    	Deleted
    	line:#define c
    	line_num:22
    	Added
    	line:#ifndef d
    	line_num:31
    	Unchanged
    	line:#define e
    	line_num:32
    	Added
    	line:#define f
    	line_num:33
    	Deleted
  |}]

let%expect_test "gen newlines" =
  let added_diff = String.concat ~sep:"\n"
    [
      "diff --git a/test/foo.c b/test/foo.c";
      "index 9daeafb..0000000 100644";
      "--- a/test/foo.c";
      "+++ b/test/foo.c";
      "@@ -11,1 +31,2 @@ Bar::bar()";
      "+#ifndef d";
      "+#define e";
      "-#define f";
      "diff --git a/test/bar.c b/test/bar.c";
      "new file mode 100644";
      "index 0000000..9daeafb";
      "--- /dev/null";
      "+++ b/test/bar";
      "@@ -0,0 +1,2 @@ bar(int a)";
      "+ test";
      "+ test2";
      "diff --git a/test/baz.c b/test/baz.c";
      "deleted file mode 100644";
      "index 9daeafb..0000000";
      "--- a/test/baz.c";
      "+++ /dev/null";
      "@@ -1 +0,0 @@";
      "- test";
      "";
    ]
  |> Git_diff.process_internal
  in
  let new_lines = Git_diff.gen_new_lines added_diff
  in
  List.iter ~f:(fun (name, line) ->
    Printf.printf "%b\n" (Git_diff.check_is_new_line new_lines name line)
  )
  [
    ("/test/foo.c", 31);
    ("/test/foo.c", 32);
    ("/test/foo.c", 33); (* out of bound *)
    ("/test/bar.c", 1);
    ("/test/bar.c", 2);
    ("/test/baz.c", 2); (* out of bound *)
  ];
  List.iter ~f:(fun name ->
    Printf.printf "%b\n" (Git_diff.check_file_in_diff new_lines name)
  )
  [
    "/test/foo.c";
    "/test/bar.c";
    "/test/baz.c"; (* out of bound *)
  ];
  List.iter ~f:(fun (name, line) ->
    Printf.printf "%s\n" (Git_diff.get_line new_lines name line)
  )
  [
    ("/test/foo.c", 31);
    ("/test/foo.c", 32);
    ("/test/bar.c", 1);
    ("/test/bar.c", 2);
  ];
  print_endline "end test";
  [%expect {|
    true
    true
    false
    true
    true
    false
    true
    true
    true
    #ifndef d
    #define e
     test
     test2
    end test
  |}]
