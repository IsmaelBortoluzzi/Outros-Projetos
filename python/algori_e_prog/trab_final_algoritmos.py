# Classes, Funções e Variáveis Globais

usuarios = {}
user_id = 100


class Usuario:  # Classe para os usuários do sistema
    # Biblioteca para usar criptografias
    from passlib.hash import pbkdf2_sha256 as sha256  # pip install passlib

    def __init__(self, nome, cpf, senha, email):
        self.__nome = nome
        self.__cpf = cpf
        self.__senha = Usuario.sha256.hash(senha, rounds=3000, salt_size=16)  # encripta a senha
        self.__email = email
        self.carrinho = []
        self.limite = 1000  # saldo limite de compra

    def checa_cpf(self):
        return self.__cpf

    def mostra_nome(self):
        return self.__nome

    def checa_senha(self, senha_func):
        if Usuario.sha256.verify(senha_func, self.__senha):  # verifica a senha
            return True
        return False

    def mostra_email(self):
        return self.__email


def make_users(nome, cpf, senha, email):  # Função que cria um usuário novo
    user = Usuario(nome, cpf, senha, email)
    return user


def cadastro():  # Função que executa o cadastro com todos os filtros de um novo usuário
    global user_id
    global usuarios
    name = str(input("Digite o seu nome: "))
    cpf = input("Digite o cpf: ")

    if not cpf.isnumeric():
        print("CPF inválido!")
        return None

    if not validador_cpf(cpf):
        print("CPF inválido!\n")
        return None

    for k in usuarios.keys():
        if usuarios[k].checa_cpf() == cpf:
            print(f"Este usuário já existe!")
            return None

    email = str(input("Digite o seu e-mail: "))
    senha = str(input("Digite uma senha: (6 dígitos) "))
    verify_senha = input("Digite novamente a senha: ")

    while senha != verify_senha or len(senha) != 6:
        print("Senha inválida!")
        senha = str(input("Digite uma senha: (6 dígitos) "))
        verify_senha = input("Digite novamente a senha: ")

    usuarios["user_id_" + str(user_id)] = make_users(name, cpf, senha, email)  # Os usuários serão
    # salvos neste dicionário.
    print(f"\n\033[36mSeu ID é {user_id}\033[m\n")  # Cada qual com seu id gerado automaticamente.
    user_id += 1  # id update
    return None


def validador_cpf(cpf6):

    if len(cpf6) != 11:
        return False

    passo1 = cpf6[:9]

    contador = 10
    check = 0

    for i in passo1:
        check = check + (int(i) * contador)
        contador -= 1

    if check % 11 < 2:
        passo1 = passo1 + '0'
    else:
        passo1 = passo1 + str(11 - (check % 11))

    contador = 11
    check = 0

    for i in passo1:
        check = check + (int(i) * contador)
        contador -= 1

    if check % 11 < 2:
        passo1 = passo1 + '0'
    else:
        passo1 = passo1 + str(11 - (check % 11))

    if not passo1 == cpf6:
        return False

    return True


def leiaint(i=''):
    """
    É uma função idêntica ao input() porém trata a entrada
    para aceitar somente int

    :param i: É a string que apare pro usuário antes do input
    :return: um número int
    """
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


def real(i=0.0):
    try:
        return f'R${i:.2f}'.replace('.', ',')
    except:
        return 'O valor não pode ser convertido para formato moeda.'


def titulo(t):
    """
    :param t: Título a ser escrito
    :return: Título formatado bonito
    """
    print('-'*len(t))
    print(f'{t}')
    print('-'*len(t))


def saldo(user_id2):
    return real(usuarios["user_id_" + str(user_id2)].limite)


def comprar(userid1, senha):
    if not usuarios["user_id_" + str(userid1)].checa_senha(senha):
        print("Senha incorreta!")  # verifica a senha
        return None

    while True:  # inicia o loop para adição no carrinho
        print('')
        for i in lista_de_produtos:  # mostra a lista de produtos
            print(f"{i[0]:<27}   {real(i[1])}")
        print('')

        print(f'Seu saldo é de {saldo(userid1)}\n')  # mostra o saldo

        pro = leiaint("Qual produto deseja comprar? (insira o id do produto ou 22 para sair): ")

        if pro < 0 or pro > 20:
            return None

        quant = leiaint("Quantos destes itens? ")

        if usuarios["user_id_" + str(userid1)].limite - (lista_de_produtos[pro][1] * quant) <= 0:
            print(f"Saldo insuficiente. Pague para poder comprar mais!")
            return None

        for _ in range(quant):
            usuarios["user_id_" + str(userid1)].carrinho.append(lista_de_produtos[pro])  # coloca no carrinho
            usuarios["user_id_" + str(userid1)].limite -= lista_de_produtos[pro][1]  # atualiza o saldo


def mostrar_carrinho(user_id3):
    total = 0

    opc = str(input("\nDeseja ver os itens do carrinho? S/N "))
    if opc in ("S", "s"):
        for produtos in usuarios["user_id_" + str(user_id3)].carrinho:
            print(f"{produtos[0]:<27} {real(produtos[1])}")
            total += produtos[1]
    else:
        for produtos in usuarios["user_id_" + str(user_id3)].carrinho:
            total += produtos[1]

    print(f"\nO total é {real(total)}\n")
    return None


def consulta_cliente(cpf_func):
    for k in usuarios.keys():
        if usuarios[k].checa_cpf() == cpf_func:
            print(f"Nome: {usuarios[k].mostra_nome()}")
            print(f"E-mail: {usuarios[k].mostra_email()}")
            return None
    print("Não existe nenhum usuário com este CPF!")
    return None


def pagar(id4, senha4, cpf4):
    if not usuarios["user_id_" + str(id4)].checa_senha(senha4):
        print("Senha incorreta!")  # verifica a senha
        return None
    if usuarios["user_id_" + str(id4)].checa_cpf() != cpf4:
        print("CPF incorreto!")  # verifica o CPF
        return None

    print(f"\nO valor a ser pago é de {real(1000 - usuarios['user_id_' + str(id4)].limite)}")
    cont = str(input("Deseja continuar com a transação? (S/N) "))
    if cont not in ("s", "S"):
        print("\nTransação cancelada.")
        return None

    usuarios['user_id_' + str(id4)].limite = 1000
    print("\nTransação finalizada com sucesso.")
    print("Agora você pode comprar mais coisas na loja!")
    return None


lista_de_produtos = (
    ("0. arroz 5kg", 10.99), ("1. feijão 1kg", 7.99),
    ("2. açucar 5kg", 8.99), ("3. farinha de milho 1kg", 6.99),
    ("4. farinha de trigo 5kg", 12.99), ("5. erva mate 1kg", 7.99),
    ("6. centeio 1kg", 7.99), ("7. pinhão 1kg", 11.99),
    ("8. laranja 1kg", 2.99), ("9. espaguete 500g", 7.99),
    ("10. maçãs 1kg", 4.99), ("11. sal marinho 1kg", 3.99),
    ("12. cerveja Eisenbahn 355ml", 4.20), ("13. mamão 1kg", 2.99),
    ("14. vinho 950ml", 10.99), ("15. coca-cola 2L", 6.99),
    ("16. leite 1L", 1.99), ("17. doritos 300g", 9.99),
    ("18. vodka 1L", 15.99), ("19. café 200g", 8.99),
    ("20. carne bovina 900g", 39.99), ("21. sabão 1kg", 5.99),
)


opcao = -1

while True:

    titulo('MENU PRINCIPAL')
    print("""
1 -> Cadastro
2 -> Comprar
3 -> Mostrar carrinho
4 -> Pagar conta
5 -> Consultar cliente
6 -> Mostrar produtos
0 -> Sair""")
    opcao = leiaint("\nOpção: ")

    if opcao == 0:
        print("\nSaindo...\n")
        break

    elif opcao == 1:
        print("Opção selecionada: Cadastro\n")
        cadastro()

    elif opcao == 2:
        print("Opção selecionada: Comprar\n")

        tent = 0
        id5 = 0
        while tent < 3:
            id5 = leiaint("Digite o seu ID: ")

            if id5 < 100 or id5 > (user_id - 1):
                print("ID inválido!")
                tent += 1
                print(f"Tem mais {3 - tent} tentativas.")
            else:
                break
        if tent == 3:
            continue
        senha = str(input("Digite a senha: "))
        comprar(id5, senha)

    elif opcao == 3:
        print("Opção selecionada: Mostrar carrinho\n")

        tent = 0
        id5 = 0
        while tent < 3:
            id5 = leiaint("Digite o seu ID: ")

            if id5 < 100 or id5 > (user_id - 1):
                print("ID inválido!")
                tent += 1
                print(f"Tem mais {3 - tent} tentativas.")
            else:
                break
        if tent == 3:
            continue

        mostrar_carrinho(id5)

    elif opcao == 4:
        print("Opção selecionada: Pagar conta\n")

        tent = 0
        id5 = 0
        while tent < 3:
            id5 = leiaint("Digite o seu ID: ")

            if id5 < 100 or id5 > (user_id - 1):
                print("ID inválido!")
                tent += 1
                print(f"Tem mais {3 - tent} tentativas.")
            else:
                break
        if tent == 3:
            continue

        senha = str(input("Digite a senha: "))
        cpf5 = input("Digite o CPF: ")

        pagar(id5, senha, cpf5)

    elif opcao == 5:
        print("Opção selecionada: Consultar cliente\n")

        cpf5 = input("Digite o CPF: ")

        consulta_cliente(cpf5)

    elif opcao == 6:
        print('')
        titulo("LISTA DE PRODUTOS")
        print('')

        for i in lista_de_produtos:
            print(f"{i[0]:<27}  {real(i[1])}")

    else:
        print("Opção inválida! Tente novamente.")
