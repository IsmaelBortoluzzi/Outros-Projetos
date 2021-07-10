from math import factorial
resul = 0


def leiaint(i=''):
    while True:
        try:
            entrada = int(input(i))
        except KeyboardInterrupt:
            print('O usuário preferiu não informar o valor')
            return 0
        except:
            print('Você não digitou um número inteiro!\n')
            continue
        else:
            return entrada


def leiafloat(i=''):
    while True:
        try:
            entrada = float(input(i))
        except KeyboardInterrupt:
            print('O usuário preferiu não informar o valor')
            return 0
        except:
            print('Você não digitou um número real!\n')
            continue
        else:
            return entrada


print("\nInforme \033[34mTODOS\033[m os valores em formato decimal. EX: n=10 x=5 p=0.05\n\n")

n = leiaint("Digite a quantidade de itens observados (n): ")
x = leiaint("Digite a quantidade de sucessos desejada (x): ")
p = leiafloat("Digite a probabilidade de sucesso: ")

while True:
    print("\nDigite \033[36m1\033[m para Probabilidade Binomial Individual  EX: [P (x = y)]")
    print("Digite \033[32m2\033[m para Probabilidade Binomial Acumulada decrescente  EX: [P (x >= y)]")
    print("Digite \033[31m3\033[m para Probabilidade Binomial Acumulada crescente  EX: [P (x <= y)]")
    opcao = input("Opção: ")
    print()

    if opcao == "1":

        analiCombi = factorial(n) / ((factorial((n-x)) * factorial(x)))

        resul = analiCombi * (p ** x) * ((1-p) ** (n-x))

        break

    elif opcao == "2":

        for i in range(x, n+1):
            analiCombi = factorial(n) / ((factorial((n - i)) * factorial(i)))

            resul += analiCombi * (p ** i) * ((1 - p) ** (n - i))
        break

    elif opcao == "3":

        for i in range(0, x+1):
            analiCombi = factorial(n) / ((factorial((n - i)) * factorial(i)))

            resul += analiCombi * (p ** i) * ((1 - p) ** (n - i))
        break

    else:
        print("\033[31mOpção inválida!\033[m")
        continue

print(f'A probabilidade é de {resul*100:.4f}%')
