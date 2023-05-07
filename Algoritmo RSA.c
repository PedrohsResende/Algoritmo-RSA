#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Função que calcula a potência de um número
int mod_pow(int base, int exponent, int modulus)
{
    int result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

//calcula o inverso multiplicativo de a mod m
int mod_inverse(int a, int m) 
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1) {
        return 0;
    }
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) {
        x1 += m0;
    }
    return x1;
}

//calcula o maior divisor comum
int gcd(int a, int b) 
{
    if (b == 0) 
    {
        return a;
    }
    return gcd(b, a % b);
}

// Função que verifica se um número é primo
int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Função que gera um número primo aleatório
int rand_prime() {
    int n = rand() % 1000;
    while (!is_prime(n)) {
        n = rand() % 1000;
    }
    return n;
}
void g_chave() 
{
    int p, q, n, e, d;
    printf("Digite dois números primos p e q: ");
    scanf("%d", &p);
    scanf("%d", &q);
    n = p * q;
    int phi = (p - 1) * (q - 1);
    printf("Digite um expoente e relativamente primo a (p-1)(q-1): ");
    scanf("%d", &e);
    while (gcd(e, phi) != 1) {
        printf("Erro: o expoente não é relativamente primo a (p-1)(q-1).\n");
        printf("Digite outro valor para e: ");
        scanf("%d", &e);
    }
    d = mod_inverse(e, phi);
    FILE *fp = fopen("public_key.txt", "w");
    fprintf(fp, "%d %d", n, e);
    fclose(fp);
    printf("Chave pública gerada com sucesso.\n");
}

void encriptar() {
    int p, q, n, e;
    printf("Digite dois números primos p e q: ");
    scanf("%d", &p);
    scanf("%d", &q);
    n = p * q;
    int phi = (p - 1) * (q - 1);
    printf("Digite um expoente e relativamente primo a (p-1)(q-1): ");
    scanf("%d", &e);
    while (gcd(e, phi) != 1) {
        printf("Erro: o expoente não é relativamente primo a (p-1)(q-1).\n");
        printf("Digite outro valor para e: ");
        scanf("%d", &e);
    }

    // Obter a mensagem a ser encriptada
    char mensagem[100];
    printf("Digite a mensagem a ser encriptada: ");
    scanf(" %[^\n]", mensagem);

    // Converter a mensagem para um array de inteiros
    int mensagem_int[100];
    int i;
    for (i = 0; mensagem[i] != '\0'; i++) {
        if (mensagem[i] == ' ') {
            mensagem_int[i] = 28;
        } else {
            mensagem_int[i] = mensagem[i] - 'A' + 2;
        }
    }

    // Encriptar a mensagem
    int mensagem_encriptada[100];
    for (i = 0; mensagem[i] != '\0'; i++) {
        mensagem_encriptada[i] = mod_pow(mensagem_int[i], e, n);
    }

    // Salvar a mensagem encriptada em um arquivo
    FILE *arquivo_saida = fopen("mensagem_encriptada.txt", "w");
    for (i = 0; mensagem[i] != '\0'; i++) {
        fprintf(arquivo_saida, "%d ", mensagem_encriptada[i]);
    }
    fclose(arquivo_saida);

    printf("Mensagem encriptada e salva em mensagem_encriptada.txt\n");
}


int desencriptar()
{

}

//Solicite que o usuário escolha entre 3 opções: 1 - Gerar chave pública, 2 - Encriptar, 3 - Desencriptar.

int main()
{
    int entrada;
    printf("Digite 1 - Gerar chave pública\n");
    printf("Digite 2 - Encriptar\n");
    printf("Digite 3 - Desencriptar\n");
    scanf("%d\n", &entrada);
    if (entrada == 1)
        {
            g_chave();
        }
    else if (entrada == 2)
    {
        encriptar();
    }
    else if (entrada == 3)
    {
        desencriptar();
    }
}