#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


// Função que calcula a potência de um número
int mod_exp(int base, int expoente, int m) {
    int resultado = 1;
    base = base % m;

    while (expoente > 0) {
        if (expoente % 2 == 1) {
            resultado = (resultado * base) % m;
        }
        expoente = expoente / 2;
        base = (base * base) % m;
    }

    return resultado;
}

// Função que calcula a potência de um número
long long int mod_pow(long long int base, int expoente, int m) {
    long long int resultado = 1;
    base = base % m;

    while (expoente > 0) {
        if (expoente % 2 == 1) {
            resultado = (resultado * base) % m;
        }
        expoente = expoente / 2;
        base = (base * base) % m;
    }

    return resultado;
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
    printf("Digite dois números primos p e q: \n");
    scanf("%d", &p);
    scanf("%d", &q);
    while (!is_prime(p) || !is_prime(q)) {
        printf("Erro: p ou q não é primo.\n");
        printf("Digite dois números primos p e q: \n");
        scanf("%d", &p);
        scanf("%d", &q);
    }
    n = p * q;
    //a função totiente de Euler (p-1)(q-1)
    int phi = (p - 1) * (q - 1);
    printf("phi = %d\n", phi);
    printf("Digite um expoente e relativamente primo a phi = (p-1)(q-1): ");
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

void encriptar() 
{
    int n, e;
    printf("Digite os valores de n e e: \n");
    scanf("%d", &n);
    scanf("%d", &e);
    // Obter a mensagem a ser encriptada
    char mensagem[1000];
    printf("Digite a mensagem a ser encriptada: ");
    scanf(" %[^\n]", mensagem);

    // Converter a mensagem para um array de inteiros
    long long int mensagem_int[1000];
    int i;
    for (i = 0; mensagem[i] != '\0'; i++) {
        if (mensagem[i] == ' ') {
            mensagem_int[i] = 28;
        } else {
            mensagem_int[i] = mensagem[i] - 'A' + 2;
        }
    }
    // Encriptar a mensagem
    long long int mensagem_encriptada[1000];
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


void desencriptar() {
    // Abrir o arquivo com a mensagem encriptada
    FILE *arquivo_entrada = fopen("mensagem_encriptada.txt", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo mensagem_encriptada.txt\n");
        return;
    }

    // Ler a mensagem encriptada do arquivo
    int mensagem_encriptada[1000];
    int tamanho_mensagem = 0;
    int valor;
    while (fscanf(arquivo_entrada, "%d", &valor) == 1) {
        mensagem_encriptada[tamanho_mensagem] = valor;
        tamanho_mensagem++;
    }
    fclose(arquivo_entrada);

    // Obter a chave privada do usuário
    int p, q, n, e, d;
    printf("Digite dois números primos p e q: \n");
    scanf("%d", &p);
    scanf("%d", &q);
    while (!is_prime(p) || !is_prime(q)) {
        printf("Erro: p ou q não é primo.\n");
        printf("Digite dois números primos p e q: \n");
        scanf("%d", &p);
        scanf("%d", &q);
    }
    n = p * q;
    //a função totiente de Euler (p-1)(q-1)
    int phi = (p - 1) * (q - 1);
    printf("phi = %d\n", phi);
    printf("Digite um expoente e relativamente primo a phi = (p-1)(q-1): ");
    scanf("%d", &e);
    while (gcd(e, phi) != 1) {
        printf("Erro: o expoente não é relativamente primo a (p-1)(q-1).\n");
        printf("Digite outro valor para e: ");
        scanf("%d", &e);
    }
    d = mod_inverse(e, phi);
    // Desencriptar a mensagem
    int mensagem_desencriptada[1000];
    int i;
    for (i = 0; i < tamanho_mensagem; i++) {
        mensagem_desencriptada[i] = mod_pow(mensagem_encriptada[i], d, n);
    }

    // Converter a mensagem desencriptada para uma string
    char mensagem[1000];
    for (i = 0; i < tamanho_mensagem; i++) {
        if (mensagem_desencriptada[i] == 28) {
            mensagem[i] = ' ';
        } else {
            mensagem[i] = mensagem_desencriptada[i] + 'A' - 2;
        }
    }
    mensagem[i] = '\0';

    // Salvar a mensagem desencriptada em um arquivo
    FILE *arquivo_saida = fopen("mensagem_desencriptada.txt", "w");
    fprintf(arquivo_saida, "%s", mensagem);
    fclose(arquivo_saida);

    printf("Mensagem desencriptada e salva em mensagem_desencriptada.txt\n");
}



//Solicite que o usuário escolha entre 3 opções: 1 - Gerar chave pública, 2 - Encriptar, 3 - Desencriptar.

int main()
{
    int entrada;
    printf("Digite 1 - Gerar chave pública\n");
    printf("Digite 2 - Encriptar\n");
    printf("Digite 3 - Desencriptar\n");
    scanf("%d", &entrada);
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