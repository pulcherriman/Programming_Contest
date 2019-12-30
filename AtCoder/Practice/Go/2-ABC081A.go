package main
import (
    . "fmt"
)

func main(){
    // Your code here!
    var s string
    Scanf("%s", &s)
    ans := 0
    for i:=0;i<3;i++{
        if s[i]=='1'{
            ans+=1
        }
    }
    Println(ans)
}
