#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Função para verificar se um numero é primo
bool eh_primo(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Função para calcular o MDC usando o algoritmo de Euclides 
int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para verificar se dois numeros são coprimos, ou seja, se o MDC deles é 1
bool sao_coprimos(int a, int b) {
    return mdc(a, b) == 1;
}

// Função para calcular o inverso modular usando novamente o algoritmo  de Euclides
int inverso_modular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    
    if (m == 1) return 0;
    
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0) x1 += m0;
    
    return x1;
}

// Função para calcular usando Euler 
int totiente_euler(int n) {
    if (n == 1) return 1;
    
    int resultado = n;
    
    // Verifica divisibilidade por 2
    if (n % 2 == 0) {
        resultado -= resultado / 2;
        while (n % 2 == 0) n /= 2;
    }
    
    // Verifica divisibilidade por numeros ímpares
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            resultado -= resultado / i;
            while (n % i == 0) n /= i;
        }
    }
    
    // Se n for um numero primo maior que 2
    if (n > 1) {
        resultado -= resultado / n;
    }
    
    return resultado;
}

// Função para exponenciação modular eficiente
int potencia_modular(int base, int expoente, int mod) {
    if (mod == 1) return 0;
    
    int resultado = 1;
    base = base % mod;
    
    while (expoente > 0) {
        if (expoente % 2 == 1) {
            resultado = (resultado * base) % mod;
        }
        expoente = expoente >> 1;
        base = (base * base) % mod;
    }
    
    return resultado;
}

int main() {
    int H, G, n, x, n1;
    
    printf("=== Verificacao Modular ===\n");
    printf("Digite o valor de H: ");
    scanf("%d", &H);
    printf("Digite o valor de G: ");
    scanf("%d", &G);
    printf("Digite o valor de n: ");
    scanf("%d", &n);
    printf("Digite o expoente x: ");
    scanf("%d", &x);
    printf("Digite o modulo n1: ");
    scanf("%d", &n1);
    
    printf("\n=== Passo 1: Verificar se G e n sao coprimos ===\n");
    if (!sao_coprimos(G, n)) {
        printf("G (%d) e n (%d) nao sao coprimos (MDC = %d). Infelizmente divisao modular nao e possivel ;-;. Tente novamente\n", G, n, mdc(G, n));
        return 1;
    }
    printf("G (%d) e n (%d) sao coprimos (MDC = 1). Podemos prosseguir.\n", G, n);
    
    printf("\n=== Passo 2: Calcular o inverso de G em Zn ===\n");
    int G_inv = inverso_modular(G, n);
    printf("O inverso de G (%d) em Z%d e: %d\n", G, n, G_inv);
    
    printf("\n=== Passo 3: Calcular a base a = H/G mod n ===\n");
    int a = (H * G_inv) % n;
    printf("a = (H * G^-1) mod n = (%d * %d) mod %d = %d\n", H, G_inv, n, a);
    
    printf("\n=== Passo 4: Verificar se a e n1 sao coprimos ===\n");
    if (!sao_coprimos(a, n1)) {
        printf("a (%d) e n1 (%d) nao sao coprimos (MDC = %d).\n", a, n1, mdc(a, n1));
    } else {
        printf("a (%d) e n1 (%d) sao coprimos (MDC = 1).\n", a, n1);
    }
    
    printf("\n=== Passo 5: Verificar se n1 e primo ===\n");
    bool n1_primo = eh_primo(n1);
    if (n1_primo) {
        printf("n1 (%d) e primo.\n", n1);
    } else {
        printf("n1 (%d) nao e primo.\n", n1);
    }
    
    printf("\n=== Passo 6 e 7: Ajustar o expoente x ===\n");
    int novo_x;
    if (n1_primo) {
        novo_x = x % (n1 - 1);
        printf("Como n1 e primo, aplicamos o Pequeno Teorema de Fermat.\n");
        printf("x = x mod (n1-1) = %d mod %d = %d\n", x, n1 - 1, novo_x);
    } else {
        int phi = totiente_euler(n1);
        novo_x = x % phi;
        printf("Como n1 nao e primo, aplicamos o Teorema de Euler.\n");
        printf("φ(n1) = %d\n", phi);
        printf("x = x mod φ(n1) = %d mod %d = %d\n", x, phi, novo_x);
    }
    x = novo_x;
    
    printf("\n=== Passo 8: Decompor o expoente x ===\n");
    int q, r;
    if (n1_primo) {
        q = n1 - 1;
    } else {
        q = totiente_euler(n1);
    }
    r = x % q;
    printf("x = %d = %d * %d + %d\n", x, x / q, q, r);
    
    printf("\n=== Passo 9/10: Calcular os valores intermediarios ===\n");
    int x2 = potencia_modular(a, x, n1);
    printf("a^x mod n1 = %d^%d mod %d = %d\n", a, x, n1, x2);
    
    int x2_pow_q = potencia_modular(x2, q, n1);
    printf("x2^q mod n1 = %d^%d mod %d = %d\n", x2, q, n1, x2_pow_q);
    
    int a_pow_r = potencia_modular(a, r, n1);
    printf("a^r mod n1 = %d^%d mod %d = %d\n", a, r, n1, a_pow_r);
    
    printf("\n=== Passo 11: Combinar os resultados ===\n");
    int resultado_final = (x2_pow_q * a_pow_r) % n1;
    printf("Resultado final: ((%d * %d) mod %d) = %d\n", x2_pow_q, a_pow_r, n1, resultado_final);
    
    printf("\n=== Resumo Final ===\n");
    printf("%d^%d mod %d == %d\n", a, x, n1, resultado_final);
    
    return 0;
}