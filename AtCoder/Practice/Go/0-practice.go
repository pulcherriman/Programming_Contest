package main
import (
    . "fmt"
)

func main(){
    // Your code here!
    var a,b,c int64
    var s string
    Scanf("%d\n%d %d\n%s", &a, &b, &c, &s)
    Printf("%d %s\n", a+b+c, s);
}
