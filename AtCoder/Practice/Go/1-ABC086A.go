package main
import (
    . "fmt"
)

func main(){
    // Your code here!
    var a,b int64
    Scanf("%d %d", &a, &b)
    
    if a*b%2==0{
        Println("Even")
    }else{
        Println("Odd")
    }
}
