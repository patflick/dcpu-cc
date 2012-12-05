typedef const int unsigned const  const * foobar,(*hahaha)(void* x);

typedef int foobar;

struct test {
    char **p;
    /*,b[2];*/
    int y;
    /*har x,*(*((*)(void*))(void*)),*(*buhuu)(int hallo);*/
    char x;
    
};

foobar x;
foobar * y;

typedef foobar ******* x1;

struct test3
{
    int x[3];
};

struct test2
{
    int x,y,z;
    struct test3 t;
};



struct test3 initStruct3()
{
    struct test3 a;
    a.x[0] = 1;
    a.x[1] = 2;
    a.x[2] = 3;
    return a;
}

struct test2 initStruct2()
{
    struct test2 a;
    a.x = 1;
    a.y = 2;
    a.z = 3;
    a.t = initStruct3();
    return a;
}


/* only warnings: */
/*int i = {{1,2,},}; /* still valid*/


int tralala(void * [10][2]);

int test23 = 0, test24 = 1, test25 = 2, *ptest = &test23;

int typedef (*whatami(int))(struct {void* (*a)();} * const , int);

int foo(void)
{
    int x,y;
    int z;
    struct test3 a;
    x = 2, y = 5;
    
    
    x = 3,
    y = 4,
    a = initStruct3();
}

int main(){
    int * p, x, h[10], blah[1];
    int * y = h;
    struct test bar;
    
    int blubbx[9];
    int gg = {1};
    struct test2 a = initStruct2();
    foo(blubbx);
    
    
    bar.x = 'x';
    
    /*
     *   struct test a;
     *   struct test b;
     *   char str1[10] = {'h', 'i','\0'};
     *   a.b[0] = 'h';
     *   a.b[1] = '\0';
     *   b = a;
     *   b.b[0] = 'x';
     *   
     *   printf("ausgabe: a %s\n", a.b);
     *   printf("ausgabe: b %s\n", b.b);
     */
    printf("size of struct: %u\n", gg);
    
    
    printf("a.x = %i\n", a.x);
    printf("a.y = %i\n", a.y);
    printf("a.z = %i\n", a.z);
    printf("a.t[0] = %i\n", a.t.x[0]);
    printf("a.t[1] = %i\n", a.t.x[1]);
    printf("a.t[2] = %i\n", a.t.x[2]);
    
}