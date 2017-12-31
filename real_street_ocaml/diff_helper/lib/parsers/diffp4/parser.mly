%token <string> OLD_FILE
%token <string> NEW_FILE
%token <string> HUNK_HEADER
%token <string> UNCHANGED_LINE
%token <string> ADDED_LINE
%token <string> DELETED_LINE
%token BLANK
%token EOF

%start <Util.value> prog

%%
prog:
  | v = list_of_files; BLANK { v }
  | EOF { [] }
  ;

list_of_files :
   files = rev_list_of_files { (List.rev files) };

rev_list_of_files:
  | (* empty *) { [] }
  | files = rev_list_of_files; old_name = OLD_FILE; new_name = NEW_FILE; diff_content = single_file
    { (old_name, new_name, diff_content) :: files }
  ;

single_file :
   file = rev_list_of_hunk { List.rev file };

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

