# P1-Parte2
Esse código, em linguagem C, realiza uma verificação modular, utilizando conceitos de Matemática Discreta 2, como de congruência, primalidade, coprimalidade, Pequeno  Teorema de Fermat, Teorema de Euler e exponenciação modular eficiente.


Aqui estão algumas etapas desse código:

 1. Verifica se G e n são coprimos (MDC = 1);
 2. Calcula o inverso modular de G em Zn, usando o Algoritmo de Euclides;
 3. Calcula a base da potência a = H * G^-1 mod n;
 4. Verifica se a e n1 são coprimos;
 5. Verifica se n1 é primo;
 6. Aplica o Pequeno Teorema de Fermat (se n1 é primo) ou o Teorema de Euler (se não é);
 7. Reduz o expoente x utilizando φ(n1) ou n1−1;
 8. Decompõe o expoente x como x = x1 * q + r;
 9. Reescreve a expressão usando a congruência: a^x ≡ ((a^x1)^q * a^r) mod n1;
10. Calcula os valores intermediários da exponenciação modular;
11. Combina os resultados e imprime o valor final da congruência.

 - Pedro Barreto Cavalcante do Amaral
 - 232038433
 
