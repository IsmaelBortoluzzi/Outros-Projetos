import funcoes_desaf115

li = funcoes_desaf115.cor('limpo')
az = funcoes_desaf115.cor('azul')
an = funcoes_desaf115.cor('anil')
am = funcoes_desaf115.cor('amarelo')
ve = funcoes_desaf115.cor('vermelho')
vd = funcoes_desaf115.cor('verde')
rx = funcoes_desaf115.cor('roxo')
br = funcoes_desaf115.cor('branco')


while True:
    funcoes_desaf115.titulo(f'{az}      Menu pricipal    {li}')

    print(f'{am}1 -{li} {an}Ver pessoas cadastradas:')
    print(f'{am}2 -{li} {an}Cadastrar pessoa:')
    print(f'{am}3 -{li} {an}Sair do Sistema.{li}')
    print('-'*31)

    opcao = funcoes_desaf115.leiaint(f'{vd}Sua opção: {li}')
    while opcao > 3 or opcao <= 0:
        print(f'{ve}Por favor digite uma opção válida!{li}')
        opcao = funcoes_desaf115.leiaint(f'{vd}Sua opção: {li}')

    print('-'*31)

    if opcao == 1:
        print(f'{rx}{"----- CADASTRO DE PESSOAS -----"}{li}')
        print('-'*31)
        funcoes_desaf115.mostracadastro()
    if opcao == 2:
        nome = str(input('Nome: '))
        idade = str(input('idade: '))
        funcoes_desaf115.cadastro(nome, idade)
    if opcao == 3:
        break
 
