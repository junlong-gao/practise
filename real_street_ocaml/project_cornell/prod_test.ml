open OUnit2
open Rec03

let tests = "simple test for prod" >::: [
   "empty" >:: (fun _ -> assert_equal 1 (prod []));
   "one"   >:: (fun _ -> assert_equal 1 (prod [1]));
   "more"  >:: (fun _ -> assert_equal 6 (prod [1; 3; 2]));
   "pattern" >:: (fun _ -> assert_equal true (patterns ["bigred";"bigred"]));
   "pattern" >:: (fun _ -> assert_equal false (patterns ["bigred";"bigred"; "bigred"]));
]

let _ = run_test_tt_main tests