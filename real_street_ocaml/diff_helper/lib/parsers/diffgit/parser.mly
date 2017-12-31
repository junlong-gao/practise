%token <string> GIT_HEADER
%token <string> A
%token <string> B
%token  RENAME_FILE
%token  ADDED_FILE
%token  ADDED_FILE_SRC
%token  DELETED_FILE
%token  DELETED_FILE_DEST
%token  INDEX
%token  SRC_FILE
%token  DST_FILE
%token <string> HUNK_HEADER
%token <string> UNCHANGED_LINE
%token <string> ADDED_LINE
%token <string> DELETED_LINE
%token EOF

%start <Util.value> prog

%%
prog:
  | v = list_of_files; EOF { v }
  | EOF { [] }
  ;

list_of_files :
   files = rev_list_of_files { (List.rev files) };

rev_list_of_files:
  | (* empty *) { [] }
  | files = rev_list_of_files;
    header = GIT_HEADER; a = A; b = B;
    diff_content = single_file
    { (a, b, diff_content) :: files }
  ;

single_file :
   | INDEX; SRC_FILE; DST_FILE;                          file = rev_list_of_hunk
      { List.rev file }
   | ADDED_FILE;   ADDED_FILE_SRC; DST_FILE;      file = rev_list_of_hunk
      { List.rev file }
   | DELETED_FILE; SRC_FILE;   DELETED_FILE_DEST; file = rev_list_of_hunk
      { List.rev file }
   | RENAME_FILE
      { [] }
   ;

rev_list_of_hunk:
  | (* empty *) { [] }
  | hunks = rev_list_of_hunk; hunk_header = HUNK_HEADER; changed_lines = single_hunk
    { (hunk_header, changed_lines) :: hunks }
  ;

single_hunk : hunk = rev_list_of_lines { List.rev hunk };

rev_list_of_lines:
  | (* empty *) { [] }
  | lines = rev_list_of_lines; signle_line = change
    { signle_line :: lines }
  ;

change:
  | s = UNCHANGED_LINE  { Util.Unchanged_line    s }
  | s = ADDED_LINE      { Util.Added_line        s }
  | s = DELETED_LINE    { Util.Deleted_line      s }
  ;

