/**
|-------------------------------------------------------------------------------------------|
|Autor: Willian Souza Vieira                                                                |
|Proprama: Um codigo que decrepta dados                                                     |
|ultilizando uma rede multi layer perceptron com 1 camada oculta                            |
|-------------------------------------------------------------------------------------------|
**/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define ENTRADAS        8
#define SAIDAS          1
#define NR_AMOSTRAS     26
#define NR_NEURON_O     6
#define EPOCAS          1000000
#define TX_APRENDIZADO  0.7


float cj_treinamento[NR_AMOSTRAS][ENTRADAS+SAIDAS] = {{0,1,0,0,0,0,0,0,65},//@-->A
                                                    {0,0,1,0,0,0,1,1,66},//#-->B
                                                    {0,0,1,0,0,1,0,0,67},//$-->C
                                                    {0,0,1,0,0,1,0,1,68},//%-->D
                                                    {0,0,1,0,0,1,1,0,69},//&-->E
                                                    {0,0,1,0,1,0,1,0,70},//*-->F
                                                    {0,0,1,1,0,0,0,1,71},//1-->G
                                                    {0,0,1,1,0,0,1,0,72},//2-->H
                                                    {0,0,1,1,0,0,1,1,73},//3-->I
                                                    {0,0,1,1,0,1,0,0,74},//4-->J
                                                    {0,0,1,1,0,1,0,1,75},//5-->K
                                                    {0,0,1,1,0,1,1,0,76},//6-->L
                                                    {0,0,1,1,0,1,1,1,77},//7-->M
                                                    {0,0,1,1,1,0,0,0,78},//8-->N
                                                    {0,0,1,1,1,0,0,1,79},//9-->O
                                                    {0,0,1,1,0,0,0,0,80},//0-->P
                                                    {0,1,1,0,0,0,0,1,81},//a-->Q
                                                    {0,1,1,0,0,0,1,0,82},//b-->R
                                                    {0,1,1,0,0,0,1,1,83},//c-->S
                                                    {0,1,1,0,0,1,0,0,84},//d-->T
                                                    {0,1,1,0,0,1,0,1,85},//e-->U
                                                    {0,1,1,0,0,1,1,0,86},//f-->V
                                                    {0,1,1,0,0,1,1,1,87},//g-->X
                                                    {0,1,1,0,1,0,0,0,88},//h-->W
                                                    {0,1,1,0,1,0,0,1,89},//i-->Y
                                                    {0,1,1,0,1,0,1,0,90}//j-->Z
};


double w_e_o[ENTRADAS+1][NR_NEURON_O];
double w_o_s[NR_NEURON_O+1][SAIDAS];
double saida_o[NR_NEURON_O];
double saida_s[SAIDAS];
double delta_saida[SAIDAS];
double gradiente_oculta[NR_NEURON_O];
double delta_oculta[NR_NEURON_O];


/*
Cabe�alho das fun��es auxiliares
*/
void inicializa_sinapses();
int gera_nr_aleatorios();
void mostrar_sinapses();
double f_sigmoid(double net);
void calcular_saidas(double entradas[ENTRADAS]);
void treinar_RNA();
double calcular_erro(double desejado, double saida);
void menu();
void calcular_delta_saida(double desejado);
void calcular_delta_oculta();
void calcular_gradiente_oculta();
void ajustar_pesos_sinapticos(double entradas[ENTRADAS]);


/*
Fun��o principal
*/
int main()
{
  srand(time(NULL));

  while (1) {

    menu();

  }

  return 0;
}

void inicializa_sinapses()
{
  int i, j;


  for (i = 0; i < ENTRADAS+1; i++)
    for (j =0; j < NR_NEURON_O; j++)
      w_e_o[i][j] = gera_nr_aleatorios();

  for (i = 0; i < NR_NEURON_O+1; i++)
    for (j =0; j < SAIDAS; j++)
      w_o_s[i][j] = gera_nr_aleatorios();


}

int gera_nr_aleatorios()
{
  int numeros[2] = {-1, 1};

  return (numeros[rand() % 2]);
}

void mostrar_sinapses()
{
  int i, j;


  for (i = 0; i < ENTRADAS+1; i++) {
    for (j =0; j < NR_NEURON_O; j++)
      printf("%lf ", w_e_o[i][j]);
    printf("\n");
  }


  for (i = 0; i < NR_NEURON_O+1; i++) {
    for (j =0; j < SAIDAS; j++)
      printf("%lf ", w_o_s[i][j]);
    printf("\n");
  }
}

double f_sigmoid(double net)
{
  return 1 / (1 + exp(-net));
}

void calcular_saidas(double entradas[ENTRADAS])
{
  int i, j;


  for (i = 0; i < NR_NEURON_O; i++) {
    saida_o[i] = 0.0;
    saida_o[i] += w_e_o[0][i] * 1;

    for (j =1; j < ENTRADAS+1; j++)
     saida_o[i] += w_e_o[j][i] * entradas[j-1];

    saida_o[i] = f_sigmoid(saida_o[i]);
  }

  for (i = 0; i < SAIDAS; i++) {
    saida_s[i] = 0.0;
    saida_s[i] += w_o_s[0][i] * 1;

    for (j = 1; j < NR_NEURON_O+1; j++)
      saida_s[i] += w_o_s[j][i] * saida_o[j-1];

    saida_s[i] = f_sigmoid(saida_s[i]);
  }

}

void treinar_RNA()
{
  int i, j;
  double entradas[ENTRADAS];
  double media_erro = 0.0;

  for (i = 1; i <= EPOCAS; i++) {

    for (j = 0; j < NR_AMOSTRAS; j++) {
      entradas[0] = cj_treinamento[j][0];
      entradas[1] = cj_treinamento[j][1];
      entradas[2] = cj_treinamento[j][2];
      entradas[3] = cj_treinamento[j][3];
      entradas[4] = cj_treinamento[j][4];
      entradas[5] = cj_treinamento[j][5];
      entradas[6] = cj_treinamento[j][6];
      entradas[7] = cj_treinamento[j][7];

      calcular_saidas(entradas);


      calcular_delta_saida(cj_treinamento[j][8]/100);

      calcular_gradiente_oculta();
      calcular_delta_oculta();
      ajustar_pesos_sinapticos(entradas);
    }

  }

  printf("RNA TREINADA - Media dos erros: %lf\n", media_erro);
}

double calcular_erro(double desejado, double saida)
{
  return desejado - saida;
}

void menu()
{
  int opcao;
  double entradas[ENTRADAS];

  printf("Rede Neural Perceptron de Multiplas Camadas\n");
  printf("Problema Alfabeto Braille\n");
  printf("*******************************************\n");
  printf("1.Treinar a rede\n");
  printf("2.Usar a rede\n");
  printf("3.Ver pesos sinpaticos\n");
  printf("4.Sair\n");
  printf("Opcao? ");
  scanf("%d", &opcao);

  switch (opcao) {

    case 1: inicializa_sinapses();
            treinar_RNA();
            break;

    case 2: printf("Entrada 1: ");
            scanf("%lf", &entradas[0]);
    	    printf("Entrada 2: ");
            scanf("%lf", &entradas[1]);
    	    printf("Entrada 3: ");
            scanf("%lf", &entradas[2]);
    	    printf("Entrada 4: ");
            scanf("%lf", &entradas[3]);
    	    printf("Entrada 5: ");
            scanf("%lf", &entradas[4]);
    	    printf("Entrada 6: ");
            scanf("%lf", &entradas[5]);
            printf("Entrada 7: ");
            scanf("%lf", &entradas[6]);
            printf("Entrada 8: ");
            scanf("%lf", &entradas[7]);

            calcular_saidas(entradas);
            printf("Resposta da RNA: %lf\n", saida_s[0]*100);
            char x = saida_s[0]*100;
            printf("Resposta da RNA: %c\n", x);
            break;

    case 3: mostrar_sinapses();
            break;

    case 4: exit(0);

  }
}

void calcular_delta_saida(double desejado)
{
  int i;
  for (i = 0; i < SAIDAS; i++)

    delta_saida[i] = calcular_erro(desejado, saida_s[i]) * (1 - saida_s[i] * saida_s[i]);
}

void calcular_gradiente_oculta()
{
  int i, j;

  for (i = 0; i < SAIDAS; i++){
    for (j = 1; j < NR_NEURON_O+1; j++){

      gradiente_oculta[j-1] = delta_saida[i] * w_o_s[j][i];
      }
    }
}

void calcular_delta_oculta()
{
  int i;
  for (i = 0; i < NR_NEURON_O; i++)

    delta_oculta[i] = gradiente_oculta[i] * saida_o[i] * (1 - saida_o[i]);
}

void ajustar_pesos_sinapticos(double entradas[ENTRADAS])
{
  int i, j;


  for (i = 0; i < SAIDAS; i++) {
    w_o_s[0][i] = w_o_s[0][i] + TX_APRENDIZADO * delta_saida[i] * 1;

    for (j = 1; j < NR_NEURON_O+1; j++){
      w_o_s[j][i] = w_o_s[j][i] + TX_APRENDIZADO * delta_saida[i] * saida_o[j-1];
     }

  }

  for (i = 0; i < NR_NEURON_O; i++) {
    w_e_o[0][i] = w_e_o[0][i] + TX_APRENDIZADO * delta_oculta[0] * 1;

    for (j = 1; j < ENTRADAS+1; j++){
     w_e_o[j][i] = w_e_o[j][i] + TX_APRENDIZADO * delta_oculta[i] * entradas[j-1];
     }


  }

}
