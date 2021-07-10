cores = {'limpo': '\033[m',
         'azul': '\033[34m',
         'anil': '\033[36m',
         'vermelho': '\033[31m',
         'amarelo': '\033[33m',
         'verde': '\033[32m',
         'roxo': '\033[35m',
         'branco': '\033[30m'}


def leiaint(i=''):
    while True:
        try:
            entrada = int(input(i))
        except KeyboardInterrupt:
            print('O usuário preferiu não informar o valor')
            return 0
        except:
            print('Você não digitou um número inteiro!')
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
            print('O valor informado não foi um numero REAL')
            continue
        else:
            return entrada


def titulo_person(t, tam=0):
    print('-'*tam)
    print(f'{t}')
    print('-'*tam)


def titulo(t):
    print('-'*len(t))
    print(f'{t}')
    print('-'*len(t))


def cor(a='limpo'):
    return cores[a]


def cadastro(nome, idade):
    try:
        with open('pessoas_cadastradas.txt', 'a') as cadastrando1:
            try:
                cadastrando1.write(f'{nome: <24}')
                cadastrando1.write(f'{idade}' + ' anos\n')
            except:
                print('Você não digitou um dado válido')
    except:
        print('Digite somente strings!')


def mostracadastro():
    with open('pessoas_cadastradas.txt', 'r') as cadastrando2:
        print(cadastrando2.read())

