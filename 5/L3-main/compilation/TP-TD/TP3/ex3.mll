{
    let file = Sys.argv.(1)
    let file_out = open_out (file ^ "_transformed.c")
    let print s = Printf.fprintf file_out s 
    let niveau = ref 0
    let line_begin = ref true
    let rec print_niveau () =
        print "\n";
        line_begin := false;
        for _ = 1 to !niveau do
            print "\t";
        done
}

let maj = ['A'-'Z']
let nombre = ['1'-'9'](['0'-'9'])+
let incr = ['{' '(' '[']
let dec = ['}' ')' ']']

rule pattern = parse
| '\n' {
    line_begin := true;
    pattern lexbuf
}
| incr as c {
    (if !line_begin then
        print_niveau ();
    );
    niveau := !niveau + 1;
    print "%c" c;
    pattern lexbuf
}
| dec as c {
    niveau := !niveau - 1;
    (if !line_begin then
        print_niveau ();
    );
    print "%c" c;
    pattern lexbuf
}
| ['"' '\"'] as c{
    print "%c" c;
    pattern_in_string lexbuf
}
| [^ '\n' '\t'] as c {
    match c with
    | ' ' when !line_begin -> pattern lexbuf
    | _ ->
        if !line_begin then(
            print_niveau ();
        );
        print "%c" c;
        pattern lexbuf
}
| _ {
    pattern lexbuf
}
| eof {}
and pattern_in_string = parse
| ['"' '\"'] as c{
    print "%c" c;
    pattern lexbuf
}
| _ as c {
    print "%c" c;
    pattern_in_string lexbuf;
}

{
    let () = pattern (Lexing.from_channel (open_in file)); 
        close_out file_out
}