{
    let file = Sys.argv.(1)
    let file_out = open_out (file ^ "_transformed.c")
    let print s = Printf.fprintf file_out s 
    let macro = Hashtbl.create 64
}

let maj = ['A'-'Z']
let nombre = ['1'-'9'](['0'-'9'])+

rule pattern = parse
| "#define " (maj+ as define) ' ' ([^ '\n']+ as code) {
    print "#define %s %s" define code;
    let code = rec_define "" (Lexing.from_string code) in
    Hashtbl.replace macro define code;
    pattern lexbuf
}
| "#undef " (maj+ as define) {
    Hashtbl.remove macro define;
    pattern lexbuf 
}
| maj+ as define { 
    match Hashtbl.find_opt macro define with
    | None -> print "%s" define; pattern lexbuf
    | Some s -> print "%s" s; pattern lexbuf
}
| _ as c {print "%c" c; pattern lexbuf }
| eof { }
and rec_define buff = parse
| maj+ as define {
    match Hashtbl.find_opt macro define with
    | None -> rec_define (buff ^ define) lexbuf
    | Some s -> rec_define (buff ^ s) lexbuf
}
| _ as c {rec_define (buff ^ (String.make 1 c)) lexbuf }
|eof { buff } 


{
    let () = pattern (Lexing.from_channel (open_in file)); 
        close_out file_out
}