/*
#include <stdio.h>
int main(void){
    char p=0,i=0,c;
    do{
        c=getchar();
        if(p!=c){
            if(p!=0){
                printf("%c%d",p,i);
            }
            if(c==10){
                break;
            }
            i=1;
        }else{
            i++;
        }
        p=c;
    }while(1);
    printf("\n");
}
*/
#include <stdio.h>
int main(){
    char pre=getchar(),c;
    int i,count=1;
    while(1){
        c=getchar();
        if(c=='\n'){
            break;
        }
        if(pre!=c){
            printf("%c%d",pre,count);
            pre=c;
            count=1;
        }else{
            count++;
        }
    }
    printf("%c%d\n",pre,count);
    return 0;
}


