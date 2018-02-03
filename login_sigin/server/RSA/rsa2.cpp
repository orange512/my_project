/*************************************************************************
	> File Name: rsa2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年01月28日 星期日 16时06分11秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include <cstdio>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <gmp.h>

#define KEY_LENGTH 2048  //公钥的长度
#define BASE 16    //输入输出的数字进制

using namespace std;

struct key_pair
{
        char * n;
        char * d;
        int e;

};
//生成两个大素数
mpz_t * gen_primes()
{
    gmp_randstate_t grt;
    gmp_randinit_default(grt);
    gmp_randseed_ui(grt, time(NULL));
    
    mpz_t key_p, key_q;
    mpz_init(key_p);
    mpz_init(key_q);

    mpz_urandomb(key_p, grt, KEY_LENGTH / 2);//KEY_LENGTH
    mpz_urandomb(key_q, grt, KEY_LENGTH / 2);//KEY_LENGTH//随机生成两个大整数

    mpz_t * result = new mpz_t[2];
    mpz_init(result[0]);
    mpz_init(result[1]);

    mpz_nextprime(result[0], key_p);  //使用GMP自带的素数生成函数
    mpz_nextprime(result[1], key_q);

    mpz_clear(key_p);
    mpz_clear(key_q);

    return result;
}
//生成密钥对
key_pair * gen_key_pair()
{
        mpz_t * primes = gen_primes();

        mpz_t key_n, key_e, key_f;
        mpz_init(key_n);
        mpz_init(key_f);
        mpz_init_set_ui(key_e, 65537);//设置e为65537

        mpz_mul(key_n, primes[0], primes[1]);//计算n=p*q
        mpz_sub_ui(primes[0], primes[0], 1);//p=p-1
        mpz_sub_ui(primes[1], primes[1], 1);//q=q-1
        mpz_mul(key_f, primes[0], primes[1]);//计算欧拉函数φ(n)=(p-1)*(q-1)

        mpz_t key_d;
        mpz_init(key_d);
        mpz_invert(key_d, key_e, key_f);   //计算数论倒数

        key_pair * result = new key_pair;

        char * buf_n = new char[KEY_LENGTH + 10];
        char * buf_d = new char[KEY_LENGTH + 10];

        mpz_get_str(buf_n, BASE, key_n);
        result->n = buf_n;
        mpz_get_str(buf_d, BASE, key_d);
        result->d = buf_d;
        result->e = 65537;

        mpz_clear(primes[0]);   //释放内存
        mpz_clear(primes[1]);
        mpz_clear(key_n);
        mpz_clear(key_d);
        mpz_clear(key_e);
        mpz_clear(key_f);
        delete []primes;

        return result;

}
//加密函数
char * encrypt(const char * plain_text, const char * key_n, int key_e)  
{
        mpz_t M, C, n;
        mpz_init_set_str(M, plain_text, BASE); 
        mpz_init_set_str(n, key_n, BASE);
        mpz_init_set_ui(C, 0);

        mpz_powm_ui(C, M, key_e, n);    //使用GMP中模幂计算函数

        char * result = new char[KEY_LENGTH + 10];
        mpz_get_str(result, BASE, C);

        return result;

}
//解密函数
char * decrypt(const char * cipher_text, const char * key_n, const char * key_d)  
{
        mpz_t M, C, n, d;
        mpz_init_set_str(C, cipher_text, BASE); 
        mpz_init_set_str(n, key_n, BASE);
        mpz_init_set_str(d, key_d, BASE);
        mpz_init(M);

        mpz_powm(M, C, d, n);   //使用GMP中的模幂计算函数

        char * result = new char[KEY_LENGTH + 10];
        mpz_get_str(result, BASE, M);

        return result;

}
int main()
{
    key_pair * p = gen_key_pair();

    cout<<"n = "<<p->n<<endl;
    cout<<"d = "<<p->d<<endl;
    cout<<"e = "<<p->e<<endl;

    char buf[KEY_LENGTH + 10];
    cout<<"请输入要加密的数字，二进制长度不超过"<<KEY_LENGTH<<endl;
    cin>>buf;

    char * cipher_text = encrypt(buf, p->n, p->e);
    cout<<"密文为："<<cipher_text<<endl;
    char * plain_text = decrypt(cipher_text, p->n, p->d);
    cout<<"明文为："<<plain_text<<endl;
    
    if(strcmp(buf, plain_text) != 0)
        cout<<"无法解密"<<endl;
    else
        cout<<"解密成功"<<endl;

    return 0;
}

