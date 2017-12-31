%token TN
%token DA
%token FN
%token FNDA
%token FNF
%token FNH
%token LF
%token LH
%token END_OF_SECTION
%token <string>FILENAME
%token <int>INT 
%token COMMA
%token EOF

%start <Ast.value> prog

%%
prog:
  | v = list_of_section; EOF { v }
  | EOF { [] }
  ;

list_of_section :
   sections = rev_list_of_sections { (List.rev sections) };

rev_list_of_sections:
  | (* empty *) { [] }
  | sections = rev_list_of_sections;
    TN;
    name = FILENAME;
    fn;
    fnda;
    FNF;
    FNH
    coverage = section;
    LF; total_count = INT; 
    LH; hit_count   = INT;
    END_OF_SECTION
    { (name, total_count, hit_count, coverage) :: sections }
  ;

fn:
  |       {}
  | FN fn {}

fnda:
  |       {}
  | FNDA fnda {}

section :
   lines = rev_list_of_line_data { List.rev lines }
   ;

rev_list_of_line_data:
  | (* empty *) { [] }
  | lines = rev_list_of_line_data;
    DA; line_number = INT; COMMA; hit_count = INT; check_sum;
    { (line_number, hit_count) :: lines }
  ;

check_sum:
   | (* none *) { }
   | COMMA INT  { }

