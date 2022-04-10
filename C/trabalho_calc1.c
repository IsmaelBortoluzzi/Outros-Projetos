#include <stdio.h>
#include <math.h>

//structs
typedef struct {
  int valido;
  float inicio;
  float fim;
}
Intervalo;

//Devolve o valor de Y de um determinado X
float calculaY(float x) {
  return powl(x, 2.0) - (2.0 * cbrtl(x)) - 2.0;
}

float arredondar(float x) {
  char str[50];
  gcvt(x, 3, str);
  sscanf(str, "%f", & x);
  return x;
}

void imprimeIntervalo(Intervalo intervalo) {
  printf("(%f, %f)\n", intervalo.inicio, intervalo.fim);
}

//Aplica o Teorema do valor Intermediário para descobrir se o valor 2 é existente em um determinado intervalo
int existeC(Intervalo intervalo) {
  if (calculaY(intervalo.inicio) < 0 && calculaY(intervalo.fim) < 0) {
    return 0;
  }
  return 1;
}

Intervalo calculaAproximacao(Intervalo intervalo) {

  Intervalo resposta, intervaloAux;

  intervaloAux = intervalo;
  if (intervalo.fim < intervalo.inicio) {
    intervalo.inicio = intervaloAux.fim;
    intervalo.fim = intervaloAux.inicio;
  }

  if (calculaY(intervalo.inicio) < 0 && calculaY(intervalo.fim) > 0) {
    for (float i = intervalo.inicio; i < intervalo.fim; i += 0.01) {

      if (calculaY(i) > 0) {

        resposta.valido = 1;
        resposta.inicio = i - 0.01;
        resposta.fim = i + 0.01;
        break;

      }

    }

  } else if (calculaY(intervalo.inicio) > 0 && calculaY(intervalo.fim) < 0) {
    for (float i = intervalo.fim; i > intervalo.inicio; i -= 0.01) {

      if (calculaY(i) > 0) {

        resposta.valido = 1;
        resposta.inicio = i + 0.01;
        resposta.fim = i - 0.01;
        break;

      }

    }

  } else if (calculaY(intervalo.inicio) > 0 && calculaY(intervalo.fim) > 0) {
      if ((intervalo.inicio < 0 && intervalo.fim > 0)) {
        intervalo.inicio /= 2.0;
        intervalo.fim /= 2.0;
        resposta = calculaAproximacao(intervalo);

      } else {

        if (abs(intervalo.inicio - intervalo.fim) > 0.1) {
          intervalo.inicio += abs(intervalo.inicio - intervalo.fim) / 2.0;
          resposta = calculaAproximacao(intervalo);
        } else {
          intervalo.valido = 0;
          return intervalo;
        }
    }

  } else if (calculaY(intervalo.inicio) < 0 && calculaY(intervalo.fim) < 0) {
    intervalo.inicio *= 2;
    resposta = calculaAproximacao(intervalo);
  }

  return resposta;
}

int main() {
    char MSG_NAO_EXISTE_SOLUCAO[] = "Não é possível afirmar que existe solução neste intervalo,  tente  outros  dois números";
    char MSG_EXISTE_SOLUCAO[] = "A equação tem pelo menos uma solução neste intervalo";
    Intervalo intervaloX, intervaloResposta;

    printf("APLICAÇÃO DO TEOREMA DO VALOR INTERMEDIÁRIO\n");

    printf("Digite o inicio do intervalo de x: ");
    scanf("%f", & intervaloX.inicio);

    printf("Digite o fim do intervalo de x: ");
    scanf("%f", & intervaloX.fim);

    intervaloX.inicio = arredondar(intervaloX.inicio);
    intervaloX.fim = arredondar(intervaloX.fim);

    intervaloX.valido = 1;

    if (!(existeC(intervaloX)) || calculaAproximacao(intervaloX).valido == 0) {
    printf("%s\n", MSG_NAO_EXISTE_SOLUCAO);
    } else {
    printf("%s\n", MSG_EXISTE_SOLUCAO);
    imprimeIntervalo(calculaAproximacao(intervaloX));
    }

    int i;
    scanf("DIGITE ENTER PARA SAIR%d\n", &i);

    return 0;
}