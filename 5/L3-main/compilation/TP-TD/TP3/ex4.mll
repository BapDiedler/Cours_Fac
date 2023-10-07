{
    let file = Sys.argv.(1)
    let parse_error (c:char) (lexbuf:Lexing.lexbuf) =
        Printf.printf "L %d,col %d: Parse error '%c'\n"
                    (lexbuf.lex_curr_p.pos_lnum)
                    (lexbuf.lex_curr_p.pos_cnum)
                    c
    type lex = 
        | Id of string
        | Int of int
        | Fun
        | Fleche
        | Plus
        | ParO
        | ParF

    let rec print_prog = function
        | [] -> print_newline ()
        | Id s :: l     -> Printf.printf "Id(%s) " s;
                           print_prog l
        | Int i :: l    -> Printf.printf "Int(%d) " i;
                           print_prog l
        | Fun :: l      -> Printf.printf "Fun ";
                             print_prog l
        | Fleche :: l   -> Printf.printf "Fleche ";
                             print_prog l
        | Plus :: l     -> Printf.printf "Plus ";
                             print_prog l
        | ParO :: l     -> Printf.printf "ParO ";
                             print_prog l
        | ParF :: l     -> Printf.printf "ParF ";
                             print_prog l
}

let maj = ['A'-'Z']
let min = ['a'-'z']
let maj_or_min = maj | min
let id = (min | '_') (maj_or_min | '_')*
let chiffres = ['1'-'9']
let nombre = ['1'-'9']chiffres+
let new_line = '\n'
let space = [' ' '\t' '\r']

let commentaire_s = "(*"
let commentaire_f = "*)"

rule pattern = parse
| "fun" {
    Fun :: pattern lexbuf
}
| "->" {
    Fleche :: pattern lexbuf
}
| '+' {
    Plus :: pattern lexbuf
}
| '(' {
    ParO :: pattern lexbuf
}
| ')' {
    ParF :: pattern lexbuf
}
| nombre as s{
    Int (int_of_string s) :: pattern lexbuf
}
| id as var{
    Id var :: pattern lexbuf
}
| new_line {
    Lexing.new_line lexbuf;
    pattern lexbuf
}
| space {
    pattern lexbuf
}
| commentaire_s {
    commentaire 1 lexbuf;
    pattern lexbuf
}
| eof {
    []
}
| _ as c{
    parse_error c lexbuf;
    exit 1;
}
and commentaire n = parse
| commentaire_s {
    commentaire (n + 1) lexbuf
}
| commentaire_f {
    if n = 1 then
        ()
    else
        commentaire (n - 1) lexbuf
}
| eof {
    print_string "Commentaire non fermé !!!\n";
    exit 1;
}
| new_line {
    Lexing.new_line lexbuf;
    commentaire n lexbuf
}
| _ {
    commentaire n lexbuf
}

{
    let () =
        let prog = 
            pattern (Lexing.from_channel (open_in file))
        in
        print_prog prog
    
}