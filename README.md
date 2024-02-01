# Sistema de Cadastro de Clientes em C/C++ com Banco de Dados Access [Projeto integrador da faculdade FATEC]

<p align="center">
  <img src="https://github.com/Gigio42/ProjetoIntegradorInterfaceCadastro/blob/master/images/InterfacePiFoto.png" alt="Foto do menu da interface" width="450">
</p>

Este projeto consiste em uma interface desenvolvida em C/C++ para o cadastro de clientes na empresa iTracker, integrada a um banco de dados Microsoft Access. O sistema oferece funcionalidades como inserção, busca, atualização, exclusão e recuperação de dados de clientes de maneira dinâmica.

## Recursos extras

 - Máscara de input ao colocar o CPF.
 - Gerar um template quando um usuário é excluido.
 - Possibilitar a recuperação de um usuário.
 - Pulo para o próximo campo para facilitar e dinamizar o preenchimento de dados.
 - Formatação de dados.

## Pré-requisitos

Antes de iniciar, certifique-se de ter os seguintes componentes instalados em seu ambiente de desenvolvimento:

- Compilador C/C++ (ex: GCC, Visual Studio)
- Microsoft Access (Caso queira utilizar os recursos integrados com o banco)

## Configuração do Ambiente

1. Clone o repositório para o seu ambiente local:

    ```bash
    git clone https://github.com/seu-usuario/seu-repositorio.git
    ```

2. Dentro da pasta InterfaceDoPi há um executável porém compilar é mais desejável pois como o programa é feito em C/C++ sem nenhum ambiente virtual intermediário como em C# ou Java, compilar é mais garantido de funcionar em qualque máquina.

3. Se desejar usar a integração com o banco de dados, apenas tenha o MS Acess, não precisa criar um banco pois eles já estão dentro do repositório com dados fictícios de exemplo.

4. Caso haja alguma necessidade de debug dos dados, como intermédio eles são passados por arquivos texto como "clientes" e "excluidos" que podem ser alterados para gerar alguma condição para fazer algum teste no programa.

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues, propor melhorias ou enviar pull requests.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).

---


