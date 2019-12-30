package main
import (
    . "fmt"
)

func main(){
    // Your code here!
    var n, v, ans = 0, 0, 0
    Scanf("%d", &n)
    
    for i:=0;i<n;i++{
        t:=0
        Scanf("%d", &t);
        v|=t
    }
    for ;v%2==0;{
        v/=2
        ans++
    }
    
    Println(ans)
}
