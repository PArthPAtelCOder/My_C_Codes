// Name : Patel Parth Pragneshkumar
// Roll No : 111501019
// This code finds GCD of given two number ( suppose a & b )
// and also return values of alpha & bita such that (alpha)*a + (bita)*b = GCD


#include <stdio.h>

void gcd( int ans[], int a, int b ) ;

int main(void)
{
    int a, b;
    printf("Enter those two positive integers whose gcd you want to find :");
    scanf("%d %d",&a,&b);

    if ( a<b )
    {   // swapping them
        int t = a ;
        a = b ;
        b = t ;
    }

    // array in which alpha, bita , gcd will be saved in same order
    int ans[3] ;

    gcd( ans, a, b );

    printf("\n\n { alpha, bita, gcd } is = { %d, %d, %d }\n",ans[0], ans[1], ans[2] );
    return 0;
}

// this function find the gcd of 'a' and 'b'  ( a must be >= b ) & alpha, bita
// it saves output in "ans" aaray ( first argument ) in this order : alpha, bita, gcd
void gcd( int ans[], int a, int b )
{
    if(a%b == 0)
    {   ans[0] = 0 ;
        ans[1] = 1 ;
        ans[2] = b ;
    }

    else
    {
        gcd( ans, b, a%b );

        int tmp = ans[1] ;  // temporarily saving value of bita

        ans[1] = ans[0] - ( (a/b)*ans[1] ) ;   // new bita = oldAlpha - (a/b)* oldBita
        ans[0] = tmp ;  // new alpha = old bita
    }
}


